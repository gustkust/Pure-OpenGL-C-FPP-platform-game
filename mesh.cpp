#include "mesh.h"


Mesh::Mesh(vector<Vertex> vertices, vector<int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // setting VAO, VBO & EBO using Vertex struct
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // setting vertex attributes
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals (offsetof to bypass first values representing vertex position)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}


void Mesh::Draw(Shader& shader) {
    // binding textures
    // current number of diffuse textures and shining (specular) textures
    int diffuse = 0;
    int shining = 0;
    for (int i = 0; i < textures.size(); i++) {
        // activating current texture
        glActiveTexture(GL_TEXTURE0 + i);
        string index;
        string type = textures[i].type;
        // checking for type
        if (type == "texture_diffuse") {
            diffuse++;
            index = std::to_string(diffuse);
        }
        else if (type == "texture_specular") {
            shining++;
            index = std::to_string(shining);
        }
        // sending info to shader
        glUniform1i(glGetUniformLocation(shader.ID, (type + index).c_str()), i);
        // binding texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // setting texture back to default
    glActiveTexture(GL_TEXTURE0);

    // drawing
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
