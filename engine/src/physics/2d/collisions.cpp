#include "hx3d/physics/2d/collisions.hpp"

#include "hx3d/math/vector_utils.hpp"

namespace hx3d {
namespace physics2d {

  bool gt(float a, float b) {
    return a >= b * 0.95f + a * 0.01f;
  }

  float findAxisLeastPenetration(unsigned int& face, Ptr<Polygon>& a, Ptr<Polygon>& b) {
    float bestDistance = -FLT_MAX;
    unsigned int bestIndex = 0;

    for (unsigned int i = 0; i < a->vertexCount; ++i) {
      glm::vec2 nw = a->u * a->normals[i];

      glm::mat2 buT = glm::transpose(b->u);
      glm::vec2 n = buT * nw;
      glm::vec2 s = b->getSupport(-n);
      glm::vec2 v = buT * (a->u * a->vertices[i] + a->position - b->position);

      float d = glm::dot(n, s - v);
      if (d > bestDistance) {
        bestDistance = d;
        bestIndex = i;
      }
    }

    face = bestIndex;
    return bestDistance;
  }

  void findIncidentFace(std::vector<glm::vec2>& v, Ptr<Polygon> ref, Ptr<Polygon> inc, int refIndex) {
    glm::vec2 refNormal = ref->normals[refIndex];
    refNormal = ref->u * refNormal;
    refNormal = glm::transpose(inc->u) * refNormal;

    unsigned int incidentFace = 0;
    float minDot = FLT_MAX;
    for (unsigned int i = 0; i < inc->vertexCount; ++i) {
      float dot = glm::dot(refNormal, inc->normals[i]);
      if (dot < minDot) {
        minDot = dot;
        incidentFace = i;
      }
    }

    v[0] = inc->u * inc->vertices[incidentFace] + inc->position;

    incidentFace = ((incidentFace + 1) >= inc->vertexCount) ? 0 : incidentFace + 1;
    v[1] = inc->u * inc->vertices[incidentFace] + inc->position;
  }

  int clip(const glm::vec2 n, const float c, std::vector<glm::vec2>& face) {
    unsigned int sp = 0;
    std::vector<glm::vec2> out = {face[0], face[1]};

    float d1 = glm::dot(n, face[0]) - c;
    float d2 = glm::dot(n, face[1]) - c;

    if (d1 <= 0.f) out[sp++] = face[0];
    if (d2 <= 0.f) out[sp++] = face[1];

    if (d1 * d2 < 0.f) {
      float alpha = d1 / (d1 - d2);
      out[sp++] = (face[1] - face[0]) * alpha + face[0];
    }

    face[0] = out[0];
    face[1] = out[1];

    return sp;
  }

  //////////

  bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Polygon> b) {

    m.contacts.clear();

    unsigned int faceA = 0;
    float penetrationA = findAxisLeastPenetration(faceA, a, b);
    if (penetrationA >= 0.f)
      return false;

    unsigned int faceB = 0;
    float penetrationB = findAxisLeastPenetration(faceB, b, a);
    if (penetrationB >= 0.f)
      return false;

    unsigned int refIndex = 0;
    bool flip = false;

    Ptr<Polygon> ref;
    Ptr<Polygon> inc;

    if (gt(penetrationA, penetrationB)) {
      ref = a;
      inc = b;
      refIndex = faceA;
      flip = false;
    }

    else {
      ref = b;
      inc = a;
      refIndex = faceB;
      flip = true;
    }

    std::vector<glm::vec2> incidentFace(2);
    findIncidentFace(incidentFace, ref, inc, refIndex);

    glm::vec2 v1 = ref->vertices[refIndex];

    refIndex = (refIndex + 1 == ref->vertexCount) ? 0 : refIndex + 1;
    glm::vec2 v2 = ref->vertices[refIndex];

    v1 = ref->u * v1 + ref->position;
    v2 = ref->u * v2 + ref->position;

    glm::vec2 sidePlaneNormal = glm::normalize(v2 - v1);
    glm::vec2 refFaceNormal = {sidePlaneNormal.y, -sidePlaneNormal.x};

    float refC = glm::dot(refFaceNormal, v1);
    float negSide = -glm::dot(sidePlaneNormal, v1);
    float posSide = glm::dot(sidePlaneNormal, v2);

    if (clip(-sidePlaneNormal, negSide, incidentFace) < 2)
      return false;

    if (clip(sidePlaneNormal, posSide, incidentFace) < 2)
      return false;

    m.normal = refFaceNormal;
    if (flip) {
      m.normal *= -1;
    }

    unsigned int cp = 0;
    float separation = glm::dot(refFaceNormal, incidentFace[0]) - refC;
    if (separation <= 0.f) {
      m.contacts.push_back(incidentFace[0]);
      cp++;

      m.penetration = -separation;
    }
    else {
      m.penetration = 0;
    }

    separation = glm::dot(refFaceNormal, incidentFace[1]) - refC;

    if (separation <= 0.f) {
      m.contacts.push_back(incidentFace[1]);
      cp++;

      m.penetration += -separation;
      m.penetration /= cp;
    }

    return true;
  }

  bool checkCollisions(Manifold& m, Ptr<Circle> a, Ptr<Circle> b) {

    glm::vec2 normal = b->position - a->position;
    float squareLength = math::squareLength(normal);
    float radius = (a->radius + b->radius) / 2;

    if (squareLength >= radius*radius) {
      m.contacts.clear();
      return false;
    }

    //////

    float distance = std::sqrt(squareLength);
    if (distance == 0.f) {
      m.penetration = a->radius;
      m.normal = glm::vec2(1, 0);
      m.contacts.push_back(a->position);
    }

    else {
      m.penetration = radius - distance;
      m.normal = normal / distance;
      m.contacts.push_back(m.normal * a->radius + a->position);
    }

    return true;
  }

  bool checkCollisions(Manifold& m, Ptr<Polygon> a, Ptr<Circle> b) {
    return false;
  }

} /* physics2d */
} /* hx3d */