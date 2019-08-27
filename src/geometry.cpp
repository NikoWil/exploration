//
// Created by niko on 8/27/19.
//
#include <vector>
#include <glm/glm.hpp>

#include "geometry.h"
#include "triangleSoup.h"

TriangleSoup geom::generate_plane(unsigned x_count_quad, unsigned z_count_quad, float width, float depth) {
  assert(x_count_quad >= 2);
  assert(z_count_quad >= 2);

  std::srand(time(nullptr));

  unsigned x_count_vertex = x_count_quad + 1;
  unsigned z_count_vertex = z_count_quad + 1;

  std::vector<glm::vec3> points(x_count_vertex * z_count_vertex);

  // used to center plane around (0, 0)
  float width_offset = 0.5f * width;
  float depth_offset = 0.5f * depth;

  // Count to _resolution + 1, to get the proper number of indices per dimension
  for (unsigned z = 0; z < z_count_vertex; z++) {
    for (unsigned x = 0; x < x_count_vertex; x++) {
      unsigned index = z * x_count_vertex + x;

      float width_proportion = x / static_cast<float>(x_count_quad);
      float depth_proportion = z / static_cast<float>(z_count_quad);

      float x_pos = width_proportion * width - width_offset;
      float z_pos = depth_proportion * depth - depth_offset;

      glm::vec3 position(x_pos, 5 * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)), z_pos);

      points.at(index) = position;
    }
  }

  // 2 indices per quad, 3 indices per triangle
  std::vector<glm::uvec3> indices(x_count_quad * z_count_quad * 2);
  for (unsigned z = 0; z < z_count_quad; z++) {
    for (unsigned x = 0; x < x_count_quad; x++) {
      unsigned index = (z * x_count_quad + x) * 2;

      unsigned top_left = z * (x_count_vertex) + x;
      unsigned bot_left = (z + 1) * (x_count_vertex) + x;

      glm::ivec3 quad_1(top_left, bot_left + 1, top_left + 1);
      glm::ivec3 quad_2(top_left, bot_left, bot_left + 1);

      indices.at(index) = quad_1;
      indices.at(index + 1) = quad_2;
    }
  }

  return TriangleSoup{points, indices};
}