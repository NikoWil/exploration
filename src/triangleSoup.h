//
// Created by Niko on 18/07/2019.
//

#ifndef EXPLORATION_TRIANGLESOUP_H
#define EXPLORATION_TRIANGLESOUP_H

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

#include "simplemesh.hpp"

class TriangleSoup {
public:
    TriangleSoup(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices) :
        vertices{std::move(vertices)}, indices{std::move(indices)}
    {}

    SimpleMesh generate_mesh(glm::vec3 color) {
      std::vector<glm::vec3> new_vertices{};
      std::vector<glm::uvec3> new_indices{};
      std::vector<glm::vec3> normals{};

      // I - Calculate Triangle Normals
      std::vector<glm::vec3> triangle_normals(indices.size());
      for (size_t i = 0; i < indices.size(); i++) {
        glm::uvec3& triangle = indices.at(i);

        glm::vec3& v1 = vertices.at(triangle[0]);
        glm::vec3& v2 = vertices.at(triangle[1]);
        glm::vec3& v3 = vertices.at(triangle[2]);

        auto normal = glm::cross(v2 - v1, v3 - v1);

        new_vertices.push_back(v1);
        new_vertices.push_back(v2);
        new_vertices.push_back(v3);

        new_indices.emplace_back(glm::uvec3(3 * i, 3 * i + 1, 3 * i + 2));

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
      }

      return SimpleMesh{new_vertices, normals, std::vector<glm::vec3>{new_vertices.size(), color}, new_indices};
    }

private:

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
};


#endif //EXPLORATION_TRIANGLESOUP_H
