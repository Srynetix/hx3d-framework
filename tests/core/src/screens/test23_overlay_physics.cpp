// #include "tests/screens/test23_overlay_physics.hpp"
//
// #include "hx3d/core/core.hpp"
// #include "hx3d/window/application.hpp"
// #include "hx3d/utils/assets.hpp"
// #include "hx3d/math/random.hpp"
// #include "hx3d/graphics/texture.hpp"
// #include "hx3d/graphics/framebuffer.hpp"
//
// #include <limits>
//
// namespace op {
//
// Body::Body():
//   mainCollider(nullptr),
//   velocity(0.f, 0.f),
//   acceleration(0.f, 0.f),
//   force(0.f, 0.f),
//   airFriction(0.f),
//   active(true),
//   type(Type::Dynamic)
//   {}
//
// Pointer<Collider> Body::createCollider() {
//   auto collider = Make<BoxCollider>(shared_from_this());
//   colliders.push_back(collider);
//
//   return collider;
// }
//
// const Pointer<Collider>& Body::createMainCollider() {
//   mainCollider = Make<BoxCollider>(shared_from_this());
//   return mainCollider;
// }
//
// /////////
//
// Collider::Collider(WeakPointer<Body> body) {
//   contactFriction = 0.f;
//   restitution = 0.f;
//   active = true;
//
//   this->body = body;
// }
//
// BoxCollider::BoxCollider(WeakPointer<Body> body):
//   Collider(body)
//   {
//     shapeType = Type::Box;
//     normals = std::vector<glm::vec2> {
//       {0.f, -1.f},
//       {1.f, 0.f},
//       {0.f, 1.f},
//       {-1.f, 0.f}
//     };
//
//     vertices = std::vector<glm::vec2> {
//       {0.f, 0.f},
//       {0.f, 0.f},
//       {0.f, 0.f},
//       {0.f, 0.f}
//     };
//   }
//
// void BoxCollider::computeVertices() {
//   float hw = this->getTotalWidth() / 2.f;
//   float hh = this->getTotalHeight() / 2.f;
//
//   vertices[0] = {-hw, -hh};
//   vertices[1] = {hw, -hh};
//   vertices[2] = {hw, hh};
//   vertices[3] = {-hw, hh};
// }
//
// void BoxCollider::computeRotation() {
//   float c = std::cos(this->getRotation());
//   float s = std::sin(this->getRotation());
//
//   rotation[0][0] = c;
//   rotation[1][0] = -s;
//   rotation[0][1] = s;
//   rotation[1][1] = c;
// }
//
// glm::vec2 BoxCollider::getSupport(glm::vec2 dir) {
//   float bestProjection = -FLT_MAX;
//   glm::vec2 bestVertex;
//
//   // COMPUTE
//   computeVertices();
//
//   for (unsigned int i = 0; i < 4; ++i) {
//     glm::vec2 v = vertices[i];
//     float projection = (float)glm::dot(v, dir);
//
//     if (projection > bestProjection) {
//       bestVertex = v;
//       bestProjection = projection;
//     }
//   }
//
//   return bestVertex;
// }
//
// float BoxCollider::findAxisLeastPenetration(unsigned int *face, const Pointer<BoxCollider> &co) {
//   float bestDistance = -FLT_MAX;
//   unsigned int bestIndex = 0;
//
//   // COMPUTE ROTATION
//   computeRotation();
//   computeVertices();
//
//   for (unsigned int i = 0; i < 4; ++i) {
//     glm::vec2 normal = normals[i];
//     glm::vec2 rotatedNormal = rotation * normal;
//
//     glm::mat2 bTransposedRotation = glm::transpose(co->rotation);
//     normal = bTransposedRotation * rotatedNormal;
//
//     glm::vec2 support = co->getSupport(-normal);
//     glm::vec2 vertex = vertices[i];
//     vertex = rotation * vertex + this->getPosition();
//     vertex -= co->getPosition();
//     vertex = bTransposedRotation * vertex;
//
//     float dotProduct = (float)glm::dot(normal, support - vertex);
//     if (dotProduct > bestDistance) {
//       bestDistance = dotProduct;
//       bestIndex = i;
//     }
//   }
//
//   *face = bestIndex;
//   return bestDistance;
// }
//
// void BoxCollider::findIncidentFace(std::vector<glm::vec2> &v, const Pointer<BoxCollider> &co, int refIndex) {
//   glm::vec2 normal = normals[refIndex];
//   normal = rotation * normal;
//   normal = glm::transpose(co->rotation) * normal;
//
//   // COMPUTE
//   co->computeVertices();
//
//   unsigned int incidentFace = 0;
//   float minDot = FLT_MAX;
//   for (unsigned int i = 0; i < 4; ++i) {
//     float dot = (float)glm::dot(normal, co->normals[i]);
//     if (dot < minDot) {
//       minDot = dot;
//       incidentFace = i;
//     }
//   }
//
//   v[0] = co->rotation * co->vertices[incidentFace] + co->getPosition();
//   v[1] = co->rotation * co->vertices[(incidentFace + 1) % 4] + co->getPosition();
// }
//
// int BoxCollider::clip(const glm::vec2 n, const float c, std::vector<glm::vec2> &face) {
//   unsigned int sp = 0;
//   std::vector<glm::vec2> out = {face[0], face[1]};
//
//   float d1 = (float)glm::dot(n, face[0]) - c;
//   float d2 = (float)glm::dot(n, face[1]) - c;
//
//   if (d1 <= 0.f) out[sp++] = face[0];
//   if (d2 <= 0.f) out[sp++] = face[1];
//
//   if (d1 * d2 < 0.f) {
//     float alpha = d1 / (d1 - d2);
//     out[sp++] = (face[1] - face[0]) * alpha + face[0];
//   }
//
//   face[0] = out[0];
//   face[1] = out[1];
//
//   assert(sp != 3);
//   return sp;
// }
//
// void BoxCollider::resolveCollision(CollisionResolution &cr, const Pointer<Collider> &coO) {
//   cr.colliderA = shared_from_this();
//   cr.colliderB = coO;
//   cr.collision = false;
//   cr.contacts.clear();
//
//   if (coO->shapeType == Type::Box) {
//     Pointer<BoxCollider> co = std::dynamic_pointer_cast<BoxCollider>(coO);
//
//     computeVertices();
//     computeRotation();
//     co->computeVertices();
//     co->computeRotation();
//
//     unsigned int faceA = 0;
//     float penetrationA = findAxisLeastPenetration(&faceA, co);
//     if (penetrationA >= 0.f)
//       return;
//
//     unsigned int faceB = 0;
//     float penetrationB = co->findAxisLeastPenetration(&faceB, shared_from_this());
//     if (penetrationB >= 0.f)
//       return;
//
//     unsigned int refIndex = 0;
//     bool flip = false;
//
//     Pointer<BoxCollider> ref;
//     Pointer<BoxCollider> inc;
//
//     if (penetrationA >= penetrationB * 0.95f + penetrationA * 0.01f) {
//       ref = shared_from_this();
//       inc = co;
//       refIndex = faceA;
//       flip = false;
//     } else {
//       ref = co;
//       inc = shared_from_this();
//       refIndex = faceB;
//       flip = true;
//     }
//
//     std::vector<glm::vec2> incidentFace = {{0, 0},
//                                            {0, 0}};
//     ref->findIncidentFace(incidentFace, inc, refIndex);
//
//     glm::vec2 v1 = ref->vertices[refIndex];
//     glm::vec2 v2 = ref->vertices[(refIndex + 1) % 4];
//
//     v1 = ref->rotation * v1 + ref->getPosition();
//     v2 = ref->rotation * v2 + ref->getPosition();
//
//     glm::vec2 sidePlaneNormal = math::normalize(v2 - v1);
//     glm::vec2 refFaceNormal = {sidePlaneNormal.y, -sidePlaneNormal.x};
//
//     float refC = (float) glm::dot(refFaceNormal, v1);
//     float negSide = -(float) glm::dot(sidePlaneNormal, v1);
//     float posSide = (float) glm::dot(sidePlaneNormal, v2);
//
//     if (clip(-sidePlaneNormal, negSide, incidentFace) < 2)
//       return;
//     if (clip(sidePlaneNormal, posSide, incidentFace) < 2)
//       return;
//
//     cr.normal = flip ? -refFaceNormal : refFaceNormal;
//
//     unsigned int cp = 0;
//     float separation = (float) glm::dot(refFaceNormal, incidentFace[0]) - refC;
//     if (separation <= 0.f) {
//       cr.contacts.push_back(incidentFace[0]);
//       cp++;
//
//       cr.penetration = -separation;
//     } else {
//       cr.penetration = 0;
//     }
//
//     separation = (float) glm::dot(refFaceNormal, incidentFace[1]) - refC;
//     if (separation <= 0.f) {
//       cr.contacts.push_back(incidentFace[1]);
//       cp++;
//
//       cr.penetration += -separation;
//       cr.penetration /= (float) cp;
//     }
//
//     cr.collision = true;
//   }
// }
//
//
// CircleCollider::CircleCollider(WeakPointer<Body> body):
//   Collider(body)
//   {
//     shapeType = Type::Circle;
//   }
//
// /////////
//
// CollisionResolution::CollisionResolution():
//   colliderA(nullptr),
//   colliderB(nullptr),
//   collision(false)
// {}
//
// void CollisionResolution::computeCollision(const Pointer<Collider>& cA, const Pointer<Collider>& cB) {
//   cA->resolveCollision(*this, cB);
// }
//
// /////////
//
// Simulator::Simulator():
//   unitScale(1.f),
//   gravity(0.f, -9.81f)
// {}
//
// void Simulator::initialize(glm::vec2 gravity, float unitScale) {
//   this->gravity = gravity;
//   this->unitScale = unitScale;
// }
//
// Pointer<Body> Simulator::createBody() {
//   auto body = Make<Body>();
//   bodies.push_back(body);
//
//   return body;
// }
//
// void Simulator::renderDebug(const Pointer<Batch>& batch) {
//   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//   auto sprite = Make<Sprite>();
//   sprite->setTexture(Texture::Blank);
//
//   for (auto& b: bodies) {
//     if (b->type == Body::Type::Dynamic) {
//       sprite->setTint(Color(127, 0, 127));
//     }
//
//     else if (b->type == Body::Type::Static) {
//       sprite->setTint(Color(0, 127, 0));
//     }
//
//     else if (b->type == Body::Type::Kinematic) {
//       sprite->setTint(Color(0, 127, 127));
//     }
//
//     sprite->setTransform(*(b->mainCollider));
//     batch->draw(sprite);
//   }
//
//   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// }
//
// void Simulator::step(float delta) {
//
//   // Collision checks
// //  collisions.clear();
// //  inCollisions.clear();
//
//   for (int i = 0; i < bodies.size() - 1; ++i) {
//     auto& bA = bodies[i];
//     bool collision = false;
//
//     for (int j = i+1; j < bodies.size(); ++j) {
//       auto& bB = bodies[j];
//
//       // Main collider
//       if (bA->type == Body::Type::Dynamic || bB->type == Body::Type::Dynamic) {
//         CollisionResolution cr;
//         cr.computeCollision(bA->mainCollider, bB->mainCollider);
//
//         if (cr.contacts.size() > 0) {
//           // Ajout dans les contacts
// //          inCollisions.insert(cr);
//
//           // HANDLE
//
// //          collisions.insert(cr);
//         }
//       }
//     }
//   }
//
//   // Check old contacts
//
//   // Integrate
//   for (auto& b: bodies) {
//     auto& c = b->mainCollider;
//     if (b->type == Body::Type::Static)
//       return;
//
//     // ATTRACTORS
//   }
//   // Initialize
//   // Impulse
//   // Velocity
//   // Positional correction
//   // Reset
// }
//
// }
//
// /////////
// /////////
//
// Test23::Test23() {
//   sprite->setTexture(Core::Assets()->get<Texture>("box"));
//   batch->setCamera(camera);
//
//   world = Make<op::Simulator>();
//   world->initialize({0, -1.f}, 1.f);
//
//   sprite->setPosition(Core::App()->getSize() / 2);
//   sprite->setScale(0.25f);
//
//   {
//     for (int i = 0; i < 6; ++i) {
//       auto body = world->createBody();
//       auto collider = body->createMainCollider();
//       collider->setTransform(*sprite);
//       collider->setX(math::random(100, Core::App()->getWidth() - 100));
//       collider->setY(math::random(300, Core::App()->getHeight()));
//     }
//   }
//
//   auto ground = world->createBody();
//   ground->type = op::Body::Type::Static;
//
//   auto collider = ground->createMainCollider();
//   collider->setSize(Core::App()->getWidth(), 100);
//   collider->setPosition(Core::App()->getWidth() / 2.f, 50);
// }
//
// void Test23::update(float delta) {
//   world->step(1.f/60.f);
// }
//
// void Test23::render() {
//   Framebuffer::clear(Color::Black);
//
//   batch->begin();
//   world->renderDebug(batch);
//   batch->end();
// }
