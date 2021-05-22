#ifndef MODEL_H
#define MODEL_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <mesh.h>
#include <Shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


class Model {
public:
    Model();
    // all textures already loaded
    vector<Texture> textures_loaded;

    vector<Mesh> meshes;
    string directory;

    Model(string const& path);
    void Draw(Shader& shader);
private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};


#endif