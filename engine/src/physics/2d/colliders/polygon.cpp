#include "hx3d/physics/2d/colliders/polygon.hpp"

#include "hx3d/math/vector_utils.hpp"

namespace hx3d {
namespace physics2d {
namespace colliders {

Polygon::Polygon(const Type colliderType):
  Collider(Shape::Polygon, colliderType),
  box(true)
  {}

void Polygon::setPoints(const std::vector<glm::vec2>& points) {
  unsigned int rightMost = 0;
  float highestXCoord = points[0].x;
  for (unsigned int i = 1; i < points.size(); ++i) {
    float x = points[i].x;

    if (x > highestXCoord) {
      highestXCoord = x;
      rightMost = i;
    }

    else if (x == highestXCoord) {
      if (points[i].y < points[rightMost].y) {
        rightMost = i;
      }
    }
  }

  std::vector<unsigned int> hull;
  unsigned int outCount = 0;
  unsigned int indexHull = rightMost;

  for (;;) {
    hull[outCount] = indexHull;

    unsigned int nextHullIndex = 0;
    for (unsigned int i = 1; i < points.size(); ++i) {
      if (nextHullIndex == indexHull) {
        nextHullIndex = i;
        continue;
      }

      glm::vec2 e1 = points[nextHullIndex] - points[hull[outCount]];
      glm::vec2 e2 = points[i] - points[hull[outCount]];
      float c = math::cross(e1, e2);
      if (c < 0.f) {
        nextHullIndex = i;
      }

      if (c == 0.f && math::squareLength(e2) > math::squareLength(e1)) {
        nextHullIndex = i;
      }
    }

    ++outCount;
    indexHull = nextHullIndex;

    if (nextHullIndex == rightMost) {
      vertexCount = outCount;
      break;
    }
  }

  for (unsigned int i = 0; i < vertexCount; ++i) {
    vertices.push_back(points[hull[i]]);
  }

  for (unsigned int i = 0; i < vertexCount; ++i) {
    glm::vec2 face = vertices[(i+1) % vertexCount] - vertices[i];

    normals.push_back(glm::normalize(glm::vec2({face.y, -face.x})));
  }

  setDensity(1.f);
}

glm::vec2 Polygon::getSupport(glm::vec2 dir) {
  float bestProjection = -FLT_MAX;
  glm::vec2 bestVertex;

  for (unsigned int i = 0; i < vertexCount; ++i) {
    glm::vec2 v = vertices[i];
    float projection = glm::dot(v, dir);

    if (projection > bestProjection) {
      bestVertex = v;
      bestProjection = projection;
    }
  }

  return bestVertex;
}

void Polygon::setAsBox(const float width, const float height) {
  vertexCount = 4;

  float hw = width / 2;
  float hh = height / 2;

  vertices.push_back(glm::vec2(-hw, -hh));
  vertices.push_back(glm::vec2(hw, -hh));
  vertices.push_back(glm::vec2(hw, hh));
  vertices.push_back(glm::vec2(-hw, hh));
  normals.push_back(glm::vec2(0.f, -1.f));
  normals.push_back(glm::vec2(1.f, 0.f));
  normals.push_back(glm::vec2(0.f, 1.f));
  normals.push_back(glm::vec2(-1.f, 0.f));

  setDensity(1.f);
}

void Polygon::setOrientation(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);

  u[0][0] = c;
  u[1][0] = -s;
  u[0][1] = s;
  u[1][1] = c;
}

void Polygon::computeMass(float density) {

  // if (box) {
  //   massData.setMass(density);
  //   massData.setInertia(density/2.f);
  //   return;
  // }

  glm::vec2 centroid = {0.f, 0.f};
  float area = 0.f;
  float I = 0.f;
  float inv3 = 1.f / 3.f;

  for (unsigned int i = 0; i < vertexCount; ++i) {
    unsigned int j = i + 1 < vertexCount ? i + 1 : 0;
    glm::vec2 p1 = vertices[i];
    glm::vec2 p2 = vertices[j];

    float D = math::cross(p1, p2);
    float triangleArea = 0.5f * D;

    area += triangleArea;

    centroid += triangleArea * inv3 * (p1 + p2);

    float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
    float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;

    I += (0.25f * inv3 * D) * (intx2 + inty2);
  }

  centroid *= 1.f / area;

  for (unsigned int i = 0; i < vertexCount; ++i) {
    vertices[i] -= centroid;
  }

  massData.setMass(density * area);
  massData.setInertia(I * density);
}

}
}
} /* hx3d */
