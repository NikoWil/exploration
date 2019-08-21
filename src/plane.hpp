//
// Created by Niko on 14/07/2019.
//

#ifndef EXPLORATION_PLANE_HPP
#define EXPLORATION_PLANE_HPP

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "simplemesh.hpp"

class Plane {
public:
    Plane(unsigned x_count_quad, unsigned z_count_quad, float width = 1.f, float depth = 1.f):
        m_z_count_quad(x_count_quad), m_x_count_quad(z_count_quad) {
        assert(m_x_count_quad >= 2);
        assert(m_z_count_quad >= 2);

        unsigned x_count_vertex = m_x_count_quad + 1;
        unsigned z_count_vertex = m_z_count_quad + 1;

        points.resize(x_count_vertex * z_count_vertex);

        float width_offset = 0.5f * width;
        float depth_offset = 0.5f * depth;

        // Count to _resolution + 1, to get the proper number of triangles per dimension
        for (unsigned z = 0; z < z_count_vertex; z++) {
            for (unsigned x = 0; x < x_count_vertex; x++) {
                unsigned index = z * x_count_vertex + x;

                float width_proportion = x / static_cast<float>(m_x_count_quad);
                float depth_proportion = z / static_cast<float>(m_z_count_quad);

                float x_pos = width_proportion * width - width_offset;
                float z_pos = depth_proportion * depth - depth_offset;

                glm::vec3 position(x_pos, 0.f, z_pos);

                points.at(index) = position;
            }
        }

        // 2 triangles per quad, 3 indices per triangle
        indices.resize(m_x_count_quad * m_z_count_quad * 2);
        for (unsigned z = 0; z < m_z_count_quad; z++) {
            for (unsigned x = 0; x < m_x_count_quad; x++) {
                unsigned index = (z * m_x_count_quad + x) * 2;

                unsigned top_left = z * (x_count_vertex) + x;
                unsigned bot_left = (z + 1) * (x_count_vertex) + x;

                glm::ivec3 quad_1(top_left, bot_left + 1, top_left + 1);
                glm::ivec3 quad_2(top_left, bot_left, bot_left + 1);

                indices.at(index) = quad_1;
                indices.at(index + 1) = quad_2;
            }
        }
    }

private:
    const unsigned m_x_count_quad;
    const unsigned m_z_count_quad;
    std::vector<glm::vec3> points;
    std::vector<glm::uvec3> indices;
};

#endif //EXPLORATION_PLANE_HPP
