//
// Created by Niko on 15/07/2019.
//

#ifndef EXPLORATION_SIMPLEMESH_HPP
#define EXPLORATION_SIMPLEMESH_HPP

#include <glm/glm.hpp>
#include <vector>

#include "shader.hpp"

class SimpleMesh {
public:
    SimpleMesh(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices) :
    m_vertices(vertices), m_indices(indices)
    {
        setupMesh();
    }

    void draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const {
        shader.use();

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size() * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::uvec3> m_indices;

    unsigned VAO, VBO, EBO;

    void setupMesh() {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3), m_indices.data(), GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glBindVertexArray(0);
    }
};


#endif //EXPLORATION_SIMPLEMESH_HPP
