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
    explicit SimpleMesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec3> color, std::vector<glm::uvec3> indices) :
    m_vertices{std::move(vertices)}, m_normals{std::move(normals)}, m_color{std::move(color)}, m_indices{std::move(indices)}
    {
      // create buffers/arrays
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &NBO);
      glGenBuffers(1, &CBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      // load data into vertex buffers
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);

      // set the vertex attribute pointers
      // vertex Positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

      //vertex normals
      glBindBuffer(GL_ARRAY_BUFFER, NBO);
      glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

      // vertex color
      glBindBuffer(GL_ARRAY_BUFFER, CBO);
      glBufferData(GL_ARRAY_BUFFER, m_color.size() * sizeof(glm::vec3), m_color.data(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3), m_indices.data(), GL_STATIC_DRAW);

      glBindVertexArray(0);
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
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_color;
    std::vector<glm::uvec3> m_indices;

    // VAO: vertex array object
    // VBO: vertex buffer object
    // NBO: normal buffer object
    // CBO: color buffer object
    unsigned VAO, VBO, NBO, CBO, EBO;
};


#endif //EXPLORATION_SIMPLEMESH_HPP
