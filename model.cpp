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

    // transforming aiMeshes into mesh objects and pushing them to the vector
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        Mesh tmp = processMesh(mesh, scene);
        meshes.push_back(tmp);
    }
}

// drawing mesh by mesh
void Model::Draw(Shader shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
}


// transforming aiMesh to Mesh class
Mesh Model::processMesh(aiMesh* aiM, const aiScene* scene) {
    // mesh parameters
    vector<Vertex> vertices;
    vector<int> indices;
    vector<Texture> textures;

    // putting vertices, normals and texCoords into vertex type struct
    for (int i = 0; i < aiM->mNumVertices; i++) {
        Vertex vertex;
        // vertices
        vertex.Position = aiM->mVertices[i];
        // normals
        if (aiM->HasNormals()) {
            vertex.Normal = aiM->mNormals[i];
        }
        // texCoords
        vertex.TexCoords = aiM->mTextureCoords[0][i];

        vertices.push_back(vertex);
    }

    // getting indices
    for (int i = 0; i < aiM->mNumFaces; i++) {
        aiFace face = aiM->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            int tmp = face.mIndices[j];
            indices.push_back(tmp);
        }
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

// geting textures informations (we are looking for specular or/and diffusal textures
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

Model::Model(){}
