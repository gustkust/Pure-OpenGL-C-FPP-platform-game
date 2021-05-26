#include "model.h"


// basic texture loading function
int loadTexture(string textureName) {
    unsigned int ID;
    glGenTextures(1, &ID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &nrComponents, 0);

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return ID;
};


Model::Model(string const& path) {
    // assimp importer object
    Assimp::Importer importer;
    // importer reads file to aiScene object with specified parameters:
    // aiProcess_Triangulate - tranforms every non triangle object to triangle
    // aiProcess_FlipUVs - filps vertical axes to match opengl
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // reading directory (used later to load textures)
    directory = path.substr(0, path.find_last_of('/'));

    // transforming aiMeshes into mesh objects and pushing them to the vector
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        Mesh tmp = transformMesh(mesh, scene);
        meshes.push_back(tmp);
    }
}

// drawing mesh by mesh
void Model::Draw(Shader shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
}


// transforming aiMesh to Mesh class
Mesh Model::transformMesh(aiMesh* aiM, const aiScene* scene) {
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

    // loading textures into vector (we are only looking for diffuse or/and specular textures)
    vector<Texture> diffuseTextures = loadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    // insert because diffuseTextures is a vector
    textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

    vector<Texture> specularTextures = loadTextures(material, aiTextureType_SPECULAR, "texture_specular");
    // insert because specularTextures is a vector
    textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

    return Mesh(vertices, indices, textures);
}



vector<Texture> Model::loadTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    // stores all unique, loaded textures
    vector<Texture> loadedTetures;
    bool alreadyLoaded;
    for (int i = 0; i < mat->GetTextureCount(type); i++) {
        // aiString variable to store current texture directory
        aiString tmp;
        // getting current texture
        mat->GetTexture(type, i, &tmp);

        // check if texture is already loaded by comparing all directories from loadedTetures to tmp
        alreadyLoaded = false;
        for (int j = 0; j < loadedTetures.size(); j++) {
            if (std::strcmp(loadedTetures[j].path.data(), tmp.C_Str()) == 0) {
                // if its already loaded push it to the textures vector insted of loading it again and then pushing (we can do it because mesh identifies textures by index in textures vector)
                textures.push_back(loadedTetures[j]);
                alreadyLoaded = true;
                break;
            }
        }
        if (!alreadyLoaded) {
            // if its not loaded load it and then push it to the textures vector
            Texture texture;
            string textureName = this->directory + '/' + string(tmp.C_Str());
            texture.id = loadTexture(textureName);
            texture.path = tmp.C_Str();
            textures.push_back(texture);
            loadedTetures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

Model::Model() {}
