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
    TriangleSoup(const std::vector<glm::vec3>& vertices, const std::vector<glm::uvec3>& triangles) :
        vertices{vertices}, triangles{triangles}, normals()
    {
    }

    SimpleMesh generate_mesh() {
        this->generate_normals();
        return SimpleMesh(vertices, triangles);//, normals);
    }

private:
    void generate_normals() {
        normals.resize(vertices.size());

        // I - Calculate Triangle Normals
        std::vector<glm::vec3> triangle_normals(triangles.size());
        for (unsigned i = 0; i < triangles.size(); i++) {
            glm::uvec3& triangle = triangles.at(i);

            glm::vec3& v1 = vertices.at(triangle[0]);
            glm::vec3& v2 = vertices.at(triangle[1]);
            glm::vec3& v3 = vertices.at(triangle[2]);

            triangle_normals.at(i) = glm::cross(v2 - v1, v3 - v1);
        }

        // II - Calculate Vertex Normals
        for (unsigned i = 0; i < vertices.size(); i++) {
            // get indices of all triangles adjacent to vertex i
            std::vector<unsigned> adjacent_triangles;
            auto iter = triangles.begin();
            while(iter != triangles.end()) {
                iter = std::find_if(iter, triangles.end(), [=](glm::uvec3& triangle) {
                   return triangle[0] == i || triangle[1] == i || triangle[2] == i;
                });

                if (iter != triangles.end()) {
                    adjacent_triangles.push_back(std::distance(triangles.begin(), iter));
                }
            }

            // calculate normal, normalize for later use
            glm::vec3 normal(0.);
            for (const auto index : adjacent_triangles) {
                normal += triangle_normals.at(index);
            }
            normal = glm::normalize(normal);
            normals.at(i) = normal;
        }
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> triangles;
    std::vector<glm::vec3> normals;
};


#endif //EXPLORATION_TRIANGLESOUP_H
