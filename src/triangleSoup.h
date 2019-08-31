//
// Created by Niko on 18/07/2019.
//

#ifndef EXPLORATION_TRIANGLESOUP_H
#define EXPLORATION_TRIANGLESOUP_H

#include <algorithm>
#include <vector>

#include <functional>
#include <glm/glm.hpp>
#include <map>

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

    TriangleSoup* subdivide(unsigned times) {
      // TODO: have param times do sth
      std::vector<glm::vec3> new_vertices{vertices};
      std::vector<glm::uvec3> new_triangles{};
      // TODO: swap with type used in glm::uvec3 ! (own vector class?)
      std::map<std::pair<size_t, size_t>, size_t> midpoints{};

      for (const auto& triangle : indices) {
        const auto& v1 = triangle[0];
        const auto& v2 = triangle[1];
        const auto& v3 = triangle[2];

        const auto& v_1_2 = midpoint_index(v1, v2, new_vertices, midpoints);
        const auto& v_2_3 = midpoint_index(v2, v3, new_vertices, midpoints);
        const auto& v_3_1 = midpoint_index(v3, v1, new_vertices, midpoints);

        new_triangles.push_back(glm::uvec3{v1, v_1_2, v_3_1});
        new_triangles.push_back(glm::uvec3{v2, v_2_3, v_1_2});
        new_triangles.push_back(glm::uvec3{v3, v_3_1, v_2_3});
        new_triangles.push_back(glm::uvec3{v_1_2, v_2_3, v_3_1});
      }

      std::swap(vertices, new_vertices);
      std::swap(indices, new_triangles);

      return this;
    }

    TriangleSoup* transform_vertices(const std::function<glm::vec3(const glm::vec3&)>& f) {
      for (auto& v : vertices) {
        v = f(v);
      }

      return this;
    }

private:
  std::vector<glm::vec3> vertices;
  std::vector<glm::uvec3> indices;

  size_t midpoint_index(size_t v1, size_t v2, std::vector<glm::vec3>& curr_vertices,
      std::map<std::pair<size_t, size_t>, size_t>& midpoints) {
    assert(v1 < vertices.size() && "Trianglesoup.midpoint_index: legal indices have to fit into the old vertices");
    assert(v2 < vertices.size() && "Trianglesoup.midpoint_index: legal indices have to fit into the old vertices");

    if (v1 > v2) {
      std::swap(v1, v2);
    }

    const auto new_key = std::make_pair(v1, v2);
    if (midpoints.find(new_key) != std::end(midpoints)) {
      return midpoints.find(new_key)->second;
    } else {
      const auto midpoint_vertex = 0.5f * (vertices.at(v1) + vertices.at(v2));
      curr_vertices.push_back(midpoint_vertex);
      const auto index = curr_vertices.size() - 1;
      midpoints.insert(std::make_pair(new_key, index));
      return index;
    }
  }
};

#endif //EXPLORATION_TRIANGLESOUP_H
