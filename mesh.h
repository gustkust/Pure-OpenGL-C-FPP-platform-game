#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.h>
#include <string>
#include <vector>
using namespace std;


// vertex representatnion
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


// texture representation
struct Texture {
    unsigned int id;
    string type;
    string path;
};


class Mesh {
public:
    // mesh data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    unsigned int VAO;

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    // drawing
    void Draw(Shader& shader);

private:
    // render data 
    unsigned int VBO, EBO;

};
#endif