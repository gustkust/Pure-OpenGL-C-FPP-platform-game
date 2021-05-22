#include "model.h"


// basic texture loading function
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false) {
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureID;
};


Model::Model(string const& path) {
    // assimp importer object
    Assimp::Importer importer;
    // importer reads file to aiScene object with specified parameters:
    // aiProcess_Triangulate - tranforms every non triangle object to triangle
    // aiProcess_FlipUVs - filps vertical axes to match opengl
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // reading directory
    directory = path.substr(0, path.find_last_of('/'));

    // processing nodes starting from root node
    processNode(scene->mRootNode, scene);
}

// drawing mesh by mesh
void Model::Draw(Shader& shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
}


// processes every node (recursively) mesh by mesh
void Model::processNode(aiNode* node, const aiScene* scene) {
    // each node consists of some number of meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // getting mesh from scene
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        // transforming aimesh into mesh and putting it in the meshes vector
        meshes.push_back(processMesh(mesh, scene));
    }
    // processing children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }

}


// transforming aiMesh to Mesh class
Mesh Model::processMesh(aiMesh* aiM, const aiScene* scene) {
    //Mesh parameters
    vector<Vertex> vertices;
    vector<int> indices;
    vector<Texture> textures;

    // putting vertex, normals and texCoords into vectors
    for (int i = 0; i < aiM->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 tmp1;
        tmp1.x = aiM->mVertices[i].x;
        tmp1.y = aiM->mVertices[i].y;
        tmp1.z = aiM->mVertices[i].z;
        vertex.Position = tmp1;
        
        if (aiM->HasNormals()) {
            tmp1.x = aiM->mNormals[i].x;
            tmp1.y = aiM->mNormals[i].y;
            tmp1.z = aiM->mNormals[i].z;
            vertex.Normal = tmp1;
        }

        glm::vec2 tmp2;
        tmp2.x = aiM->mTextureCoords[0][i].x;
        tmp2.y = aiM->mTextureCoords[0][i].y;
        vertex.TexCoords = tmp2;

        vertices.push_back(vertex);
    }

    // getting indices face by face
    for (int i = 0; i < aiM->mNumFaces; i++) {
        aiFace face = aiM->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
    }

    // aiMaterial object to store scene material list (which is at the mMaterialIndex index)
    aiMaterial* material = scene->mMaterials[aiM->mMaterialIndex];
    
    // name convention in shaders
    // diffuse: texture_diffuseN
    // specular: texture_specularN

    // loading textures into vector
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Mesh(vertices, indices, textures);
}

// gets textures info
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}

Model::Model(){}
