#ifndef MESH_H
#define MESH_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Shader.h>
#include <string>
#include <vector>

using namespace std;


// each vertex consists of position, normal and texcoords vector
struct Vertex {
    aiVector3D Position;
    aiVector3D Normal;
    aiVector3D TexCoords;
};


// each texture consists of id, type (used in lighting - diffuse, specularetc.) and path to it
struct Texture {
    unsigned int id;
    string type;
    string path;
};


class Mesh {
public:
    // mesh data
    vector<Vertex>       vertices;
    vector<int>          indices;
    vector<Texture>      textures;

    // constructor
    Mesh(vector<Vertex> vertices, vector<int> indices, vector<Texture> textures);

    void Draw(Shader shader);
private:
    unsigned int VAO;
};


#endif