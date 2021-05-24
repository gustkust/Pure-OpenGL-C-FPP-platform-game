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
    

    vector<Mesh> meshes;
    string directory;

    Model(string const& path);
    void Draw(Shader shader);
private:
    Mesh transformMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, string typeName);
};


#endif