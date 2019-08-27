//
// Created by Niko on 14/07/2019.
//

#ifndef EXPLORATION_GEOMETRY_H
#define EXPLORATION_GEOMETRY_H

#include "triangleSoup.h"

namespace geom {
  TriangleSoup generate_plane(unsigned x_count_quad, unsigned z_count_quad, float width = 1.f, float depth = 1.f);

  TriangleSoup generate_cube(float width = 1.f);

  TriangleSoup generate_box(float width = 1.f, float height = 1.f, float depth = 1.f);
}

#endif // EXPLORATION_GEOMETRY_H
