#ifndef MESH_H
#define MESH_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.h>
#include <string>
#include <vector>

using namespace std;


// each vertex consists of position, normal and texcoords vector
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


// each texture consists of id, type (used in lighting - diffuse, specularetc.) and path to it
struct Texture {
    unsigned int id;
    string type;
    string path;
};


// mesh is a submodel of the big model
class Mesh {
public:
    // mesh data
    vector<Vertex>       vertices;
    vector<int> indices;
    vector<Texture>      textures;
    // constructor
    Mesh(vector<Vertex> vertices, vector<int> indices, vector<Texture> textures);
    // drawing
    void Draw(Shader& shader);
private:
    unsigned int VAO;
};


#endif