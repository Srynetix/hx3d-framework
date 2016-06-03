#include "./base_test_screen.hpp"

#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_structs.h>
#include <utility>

#include "hx3d/graphics/error.hpp"

using namespace hx3d;

#define PLAYER_VELOCITY 500.0

#define PLAYER_GROUND_ACCEL_TIME 0.1
#define PLAYER_GROUND_ACCEL (PLAYER_VELOCITY/PLAYER_GROUND_ACCEL_TIME)

#define PLAYER_AIR_ACCEL_TIME 0.25
#define PLAYER_AIR_ACCEL (PLAYER_VELOCITY/PLAYER_AIR_ACCEL_TIME)

#define JUMP_HEIGHT 100.0
#define JUMP_BOOST_HEIGHT 55.0
#define FALL_VELOCITY 900.0
#define GRAVITY 2000.0
#define TIME_STEP 1.f/60.f

#define CP_VELOCITY_MEM_FN(__datatype__, __memfn__)\
  [](cpBody* body, cpVect gravity, cpFloat damping, cpFloat dt, cpDataPointer data) {\
    reinterpret_cast<__datatype__*>(data)->__memfn__(body, gravity, damping, dt);\
  }

#define CP_ARBITER_MEM_FN(__datatype__, __memfn__)\
  [](cpBody* body, cpArbiter* arb, cpDataPointer data) {\
    reinterpret_cast<__datatype__*>(data)->__memfn__(body, arb);\
  }

struct Vertex {
  glm::vec2 vertex;
  glm::vec2 aa_coord;
  glm::vec4 outline_color;
  glm::vec4 fill_color;
};

struct Triangle {
  Vertex a;
  Vertex b;
  Vertex c;
};

glm::vec2 convcpv(cpVect v) {
  return {v.x, v.y};
}

glm::vec4 convcol(cpSpaceDebugColor c) {
  return {c.r, c.g, c.b, c.a};
}

void setAttribute(GLuint program, char const *name, GLint size, GLenum gltype, GLsizei stride, GLvoid *offset)
{
  GLint index = glGetAttribLocation(program, name);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, gltype, GL_FALSE, stride, offset);
}

#define SET_ATTRIBUTE(program, type, name, gltype) \
  setAttribute(program, #name, sizeof(((type *)NULL)->name)/sizeof(GLfloat), gltype, sizeof(type), (GLvoid *)offsetof(type, name))

class DebugDrawer {
public:
  DebugDrawer() {
    PointLineScale = 1.f;
    OutlineWidth = 1.f;
    _shader = Core::Assets()->get<Shader>("debugdraw");

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, vertex, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, aa_coord, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, fill_color, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, outline_color, GL_FLOAT);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

  	glEnable(GL_LINE_SMOOTH);
  	glEnable(GL_POINT_SMOOTH);

  	// glEnable(GL_BLEND);
  	// glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    GL_ERROR_CHECK();

    _options.drawCircle = [](cpVect pos, cpFloat angle, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {
      reinterpret_cast<DebugDrawer*>(data)->drawCircle(pos, angle, radius, cOutlineColor, cFillColor);
    };
    _options.drawSegment = [](cpVect a, cpVect b, cpSpaceDebugColor color, void* data) {
      reinterpret_cast<DebugDrawer*>(data)->drawSegment(a, b, color);
    };
    _options.drawFatSegment = [](cpVect a, cpVect b, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {
      reinterpret_cast<DebugDrawer*>(data)->drawFatSegment(a, b, radius, cOutlineColor, cFillColor);
    };
    _options.drawPolygon = [](int count, const cpVect *verts, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {
      reinterpret_cast<DebugDrawer*>(data)->drawPolygon(count, verts, radius, cOutlineColor, cFillColor);
    };
    _options.drawDot = [](cpFloat size, cpVect pos, cpSpaceDebugColor cFillColor, void* data) {
      reinterpret_cast<DebugDrawer*>(data)->drawDot(size, pos, cFillColor);
    };
    _options.colorForShape = [](cpShape* shape, void* data) -> cpSpaceDebugColor {
      return reinterpret_cast<DebugDrawer*>(data)->colorForShape(shape);
    };

    _options.flags = (cpSpaceDebugDrawFlags)(CP_SPACE_DEBUG_DRAW_SHAPES | CP_SPACE_DEBUG_DRAW_CONSTRAINTS | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS);
    _options.shapeOutlineColor = {200.0f/255.0f, 210.0f/255.0f, 230.0f/255.0f, 1.0f};
    _options.constraintColor = {0.0f, 0.75f, 0.0f, 1.0f};
    _options.collisionPointColor = {1.0f, 0.0f, 0.0f, 1.0f};
    _options.data = this;
  }

  float PointLineScale;
  float OutlineWidth;

  void drawCircle(cpVect pos, cpFloat angle, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor) {

    auto outlineColor = convcol(cOutlineColor);
    auto fillColor = convcol(cFillColor);

    cpFloat r = radius + 1.0f/PointLineScale;
    Vertex a = {{(GLfloat)(pos.x - r), (GLfloat)(pos.y - r)}, {-1.0f, -1.0f}, fillColor, outlineColor};
    Vertex b = {{(GLfloat)(pos.x - r), (GLfloat)(pos.y + r)}, {-1.0f,  1.0f}, fillColor, outlineColor};
    Vertex c = {{(GLfloat)(pos.x + r), (GLfloat)(pos.y + r)}, { 1.0f,  1.0f}, fillColor, outlineColor};
    Vertex d = {{(GLfloat)(pos.x + r), (GLfloat)(pos.y - r)}, { 1.0f, -1.0f}, fillColor, outlineColor};

    _triangles.push_back(Triangle{a, b, c});
    _triangles.push_back(Triangle{a, c, d});

    drawSegment(pos, cpvadd(pos, cpvmult(cpvforangle(angle), radius - PointLineScale*0.5f)), cOutlineColor);
  }

  void drawSegment(cpVect a, cpVect b, cpSpaceDebugColor color) {
    drawFatSegment(a, b, 0.0f, color, color);
  }

  void drawFatSegment(cpVect a, cpVect b, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor) {

    cpVect n = cpvnormalize(cpvrperp(cpvsub(b, a)));
    cpVect t = cpvrperp(n);

    cpFloat half = 1.0f/PointLineScale;
    cpFloat r = radius + half;
    if(r <= half){
      r = half;
      cFillColor = cOutlineColor;
    }

    cpVect nw = (cpvmult(n, r));
    cpVect tw = (cpvmult(t, r));
    auto v0 = convcpv(cpvsub(b, cpvadd(nw, tw)));
    auto v1 = convcpv(cpvadd(b, cpvsub(nw, tw))); // { 1.0,  1.0}
    auto v2 = convcpv(cpvsub(b, nw)); // { 0.0, -1.0}
    auto v3 = convcpv(cpvadd(b, nw)); // { 0.0,  1.0}
    auto v4 = convcpv(cpvsub(a, nw)); // { 0.0, -1.0}
    auto v5 = convcpv(cpvadd(a, nw)); // { 0.0,  1.0}
    auto v6 = convcpv(cpvsub(a, cpvsub(nw, tw))); // {-1.0, -1.0}
    auto v7 = convcpv(cpvadd(a, cpvadd(nw, tw))); // {-1.0,  1.0}

    auto outlineColor = convcol(cOutlineColor);
    auto fillColor = convcol(cFillColor);

    _triangles.push_back(Triangle{{v0, { 1.0f, -1.0f}, fillColor, outlineColor}, {v1, { 1.0f,  1.0f}, fillColor, outlineColor}, {v2, { 0.0f, -1.0f}, fillColor, outlineColor}});
    _triangles.push_back(Triangle{{v3, { 0.0f,  1.0f}, fillColor, outlineColor}, {v1, { 1.0f,  1.0f}, fillColor, outlineColor}, {v2, { 0.0f, -1.0f}, fillColor, outlineColor}});
    _triangles.push_back(Triangle{{v3, { 0.0f,  1.0f}, fillColor, outlineColor}, {v4, { 0.0f, -1.0f}, fillColor, outlineColor}, {v2, { 0.0f, -1.0f}, fillColor, outlineColor}});
    _triangles.push_back(Triangle{{v3, { 0.0f,  1.0f}, fillColor, outlineColor}, {v4, { 0.0f, -1.0f}, fillColor, outlineColor}, {v5, { 0.0f,  1.0f}, fillColor, outlineColor}});
    _triangles.push_back(Triangle{{v6, {-1.0f, -1.0f}, fillColor, outlineColor}, {v4, { 0.0f, -1.0f}, fillColor, outlineColor}, {v5, { 0.0f,  1.0f}, fillColor, outlineColor}});
    _triangles.push_back(Triangle{{v6, {-1.0f, -1.0f}, fillColor, outlineColor}, {v7, {-1.0f,  1.0f}, fillColor, outlineColor}, {v5, { 0.0f,  1.0f}, fillColor, outlineColor}});
  }

  void drawPolygon(int count, const cpVect *verts, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor) {

    auto outlineColor = convcol(cOutlineColor);
    auto fillColor = convcol(cFillColor);

    struct ExtrudeVerts {cpVect offset, n;};
    std::vector<ExtrudeVerts> extrude(count);
    glm::vec2 v2f0 = {0, 0};

    for(int i=0; i<count; i++){
      cpVect v0 = verts[(i-1+count)%count];
      cpVect v1 = verts[i];
      cpVect v2 = verts[(i+1)%count];

      cpVect n1 = cpvnormalize(cpvrperp(cpvsub(v1, v0)));
      cpVect n2 = cpvnormalize(cpvrperp(cpvsub(v2, v1)));

      cpVect offset = cpvmult(cpvadd(n1, n2), 1.0/(cpvdot(n1, n2) + 1.0f));
      extrude[i] = ExtrudeVerts{offset, n2};
    }

    cpFloat inset = -cpfmax(0.0f, 1.0f/PointLineScale - radius);
    for(int i=0; i<count-2; i++){
      auto v0 = convcpv(cpvadd(verts[  0], cpvmult(extrude[  0].offset, inset)));
      auto v1 = convcpv(cpvadd(verts[i+1], cpvmult(extrude[i+1].offset, inset)));
      auto v2 = convcpv(cpvadd(verts[i+2], cpvmult(extrude[i+2].offset, inset)));

      _triangles.push_back(Triangle{{v0, v2f0, fillColor, fillColor}, {v1, v2f0, fillColor, fillColor}, {v2, v2f0, fillColor, fillColor}});
    }

    cpFloat outset = 1.0f/PointLineScale + radius - inset;
    for(int i=0, j=count-1; i<count; j=i, i++){
      cpVect vA = verts[i];
      cpVect vB = verts[j];

      cpVect nA = extrude[i].n;
      cpVect nB = extrude[j].n;

      cpVect offsetA = extrude[i].offset;
      cpVect offsetB = extrude[j].offset;

      cpVect innerA = cpvadd(vA, cpvmult(offsetA, inset));
      cpVect innerB = cpvadd(vB, cpvmult(offsetB, inset));

      // Admittedly my variable naming sucks here...
      auto inner0 = convcpv(innerA);
      auto inner1 = convcpv(innerB);
      auto outer0 = convcpv(cpvadd(innerA, cpvmult(nB, outset)));
      auto outer1 = convcpv(cpvadd(innerB, cpvmult(nB, outset)));
      auto outer2 = convcpv(cpvadd(innerA, cpvmult(offsetA, outset)));
      auto outer3 = convcpv(cpvadd(innerA, cpvmult(nA, outset)));

      auto n0 = convcpv(nA);
      auto n1 = convcpv(nB);
      auto offset0 = convcpv(offsetA);

      _triangles.push_back(Triangle{{inner0, v2f0, fillColor, outlineColor}, {inner1,    v2f0, fillColor, outlineColor}, {outer1,      n1, fillColor, outlineColor}});
      _triangles.push_back(Triangle{{inner0, v2f0, fillColor, outlineColor}, {outer0,      n1, fillColor, outlineColor}, {outer1,      n1, fillColor, outlineColor}});
      _triangles.push_back(Triangle{{inner0, v2f0, fillColor, outlineColor}, {outer0,      n1, fillColor, outlineColor}, {outer2, offset0, fillColor, outlineColor}});
      _triangles.push_back(Triangle{{inner0, v2f0, fillColor, outlineColor}, {outer2, offset0, fillColor, outlineColor}, {outer3,      n0, fillColor, outlineColor}});
    }
  }

  void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor cFillColor) {
    auto fillColor = convcol(cFillColor);

    float r = (float)(size*0.5f/PointLineScale);
    Vertex a = {{(float)pos.x - r, (float)pos.y - r}, {-1.0f, -1.0f}, fillColor, fillColor};
    Vertex b = {{(float)pos.x - r, (float)pos.y + r}, {-1.0f,  1.0f}, fillColor, fillColor};
    Vertex c = {{(float)pos.x + r, (float)pos.y + r}, { 1.0f,  1.0f}, fillColor, fillColor};
    Vertex d = {{(float)pos.x + r, (float)pos.y - r}, { 1.0f, -1.0f}, fillColor, fillColor};

    _triangles.push_back(Triangle{a, b, c});
    _triangles.push_back(Triangle{a, c, d});
  }

  void drawBB(cpBB bb, cpSpaceDebugColor outlineColor) {

    cpVect verts[] = {
      cpv(bb.r, bb.b),
      cpv(bb.r, bb.t),
      cpv(bb.l, bb.t),
      cpv(bb.l, bb.b),
    };

    drawPolygon(4, verts, 0.0f, outlineColor, {0, 0, 0, 0});
  }

  cpSpaceDebugColor colorForShape(cpShape *shape)
  {
    if(cpShapeGetSensor(shape)) {
      return {1.f, 1.f, 1.f, 0.1f};
    } else {
      cpBody *body = cpShapeGetBody(shape);

      if(cpBodyIsSleeping(body)){
        return {0.2f, 0.2f, 0.2f, 1.0f};
      } else if(body->sleeping.idleTime > shape->space->sleepTimeThreshold) {
        return {0.66f, 0.66f, 0.66f, 1.0f};
      } else {
        uint32_t val = (uint32_t)shape->hashid;

        // scramble the bits up using Robert Jenkins' 32 bit integer hash function
        val = (val+0x7ed55d16) + (val<<12);
        val = (val^0xc761c23c) ^ (val>>19);
        val = (val+0x165667b1) + (val<<5);
        val = (val+0xd3a2646c) ^ (val<<9);
        val = (val+0xfd7046c5) + (val<<3);
        val = (val^0xb55a4f09) ^ (val>>16);

        GLfloat r = (GLfloat)((val>>0) & 0xFF);
        GLfloat g = (GLfloat)((val>>8) & 0xFF);
        GLfloat b = (GLfloat)((val>>16) & 0xFF);

        GLfloat max = (GLfloat)cpfmax(cpfmax(r, g), b);
        GLfloat min = (GLfloat)cpfmin(cpfmin(r, g), b);
        GLfloat intensity = (cpBodyGetType(body) == CP_BODY_TYPE_STATIC ? 0.15f : 0.75f);

        // Saturate and scale the color
        if(min == max){
          return {intensity, 0.0f, 0.0f, 1.0f};
        } else {
          GLfloat coef = (GLfloat)intensity/(max - min);
          return {
            (r - min)*coef,
            (g - min)*coef,
            (b - min)*coef,
            1.0f
          };
        }
      }
    }
  }

  void draw(const Pointer<Camera>& camera) {

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle)*_triangles.size(), _triangles.data(), GL_STREAM_DRAW);

    Shader::use(_shader);
    _shader->setUniformMatrix4f("u_projection", camera->projection);
    _shader->setUniformMatrix4f("u_view", camera->view);
    _shader->setUniformMatrix4f("u_model", glm::mat4(1.f));
    _shader->setUniform1f("u_outline_coef", OutlineWidth);
    //
    //
    // SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, vertex, GL_FLOAT);
    // SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, aa_coord, GL_FLOAT);
    // SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, fill_color, GL_FLOAT);
    // SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, outline_color, GL_FLOAT);

    glDrawArrays(GL_TRIANGLES, 0, _triangles.size() * 3);

    GL_ERROR_CHECK();

    _triangles.clear();
  }

  void update(cpSpace* space) {
    cpSpaceDebugDraw(space, &_options);
  }

private:
  GLuint _vao;
  GLuint _vbo;
  std::vector<Triangle> _triangles;
  unsigned int _trianglesCount;
  Pointer<Shader> _shader;
  cpSpaceDebugDrawOptions _options;
};

class Keybind {
public:

  void set(const std::string& str, KeyEvent::Key key) {
    _keys[str] = key;
  }

  KeyEvent::Key get(const std::string& str) {
    if (_keys.find(str) == _keys.end()) {
      Log.Error("Error: Undefined key for `%s`", str.c_str());
      return KeyEvent::Key::None;
    }

    return _keys[str];
  }

private:
  std::map<std::string, KeyEvent::Key> _keys;
};


class Once {
public:
  Once(bool value = false): _active(value), _set(false) {}

  void activate() {
    _active = true;
  }

  void lock() {
    _set = true;
  }

  bool justActivated() {
    return _active && !_set;
  }

  bool locked() {
    return _set;
  }

  void reset() {
    _set = false;
    _active = false;
  }

private:
  bool _active;
  bool _set;
};

class PlayerMovement {
public:
  PlayerMovement():
    attacking(false),
    remainingBoost(0), grounded(false), lastJumpState(false), dmg(0)
  {}

  void initialize(Keybind bind, cpBody* body, cpShape* shape) {
    _bind = bind;
    playerBody = body;
    playerShape = shape;

    cpBodySetVelocityUpdateDataFunc(playerBody, CP_VELOCITY_MEM_FN(PlayerMovement, updateVelocity), this);
    playerBody->userData = this;
  }

  void updateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt) {

    bool jumpState = false;

    if (Core::Events()->isKeyPressed(_bind.get("Jump"))) {
      jumpState = true;
    }

    // Grab the grounding normal from last frame
    cpVect groundNormal = cpvzero;
    cpBodyEachArbiter(playerBody, (cpBodyArbiterIteratorFunc)selectGroundNormal, &groundNormal);

    grounded = (groundNormal.y > 0.0);
    if(groundNormal.y < 0.0f) remainingBoost = 0.0f;

    // Do a normal-ish update
    cpBool boost = (jumpState && remainingBoost > 0.0f);
    cpVect g = (boost ? cpvzero : gravity);
    cpBodyUpdateVelocity(body, g, damping, dt);

    // Target horizontal speed for air/ground control
    int mvmt = 0;
    if (Core::Events()->isKeyPressed(_bind.get("Left"))) {
      mvmt = -1;
    }

    else if (Core::Events()->isKeyPressed(_bind.get("Right"))) {
      mvmt = 1;
    }

    cpFloat target_vx = PLAYER_VELOCITY*mvmt;

    // Update the surface velocity and friction
    // Note that the "feet" move in the opposite direction of the player.
    cpVect surface_v = cpv(-target_vx, 0.0);
    playerShape->surfaceV = surface_v;
    playerShape->u = (grounded ? PLAYER_GROUND_ACCEL/GRAVITY : 0.0);

    // Apply air control if not grounded
    if(!grounded){
      // Smoothly accelerate the velocity
      playerBody->v.x = cpflerpconst(playerBody->v.x, target_vx, PLAYER_AIR_ACCEL*dt);
    }

    body->v.y = cpfclamp(body->v.y, -FALL_VELOCITY, INFINITY);

    //////

    if (throwed.justActivated()) {
      throwed.lock();

      cpVect direction = cpvzero;
      cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)contactDirectionCheck, &direction);
      direction = direction * (500 * (1 + dmg));

      cpVect b2pos = cpBodyGetPosition(body);
      cpBodyApplyImpulseAtWorldPoint(body, direction, b2pos);

      dmg += 0.5f;
    }
  }

  static void contactDirectionCheck(cpBody* body, cpArbiter* arb, cpVect* direction) {
    cpShape *s1, *s2;
    cpArbiterGetShapes(arb, &s1, &s2);

    if (cpShapeGetCollisionType(s2) == 1) {
      cpVect n = cpvneg(cpArbiterGetNormal(arb));
      *direction = n;
    }
  }

  void update(float delta) {
    int jumpState = 0;
    if (Core::Events()->isKeyPressed(_bind.get("Jump"))) {
      jumpState = 1;
    }

    attacking = (Core::Events()->isKeyPressed(_bind.get("Attack")));

  	// If the jump key was just pressed this frame, jump!
  	if (jumpState && !lastJumpState && grounded) {
  		cpFloat jump_v = cpfsqrt(2.0*JUMP_HEIGHT*GRAVITY);
  		playerBody->v = cpvadd(playerBody->v, cpv(0.0, jump_v));

  		remainingBoost = JUMP_BOOST_HEIGHT/jump_v;
  	}

    remainingBoost -= delta/2.f;
    lastJumpState = jumpState;
  }

  static void selectGroundNormal(cpBody* body, cpArbiter* arb, cpVect* groundNormal) {
    cpVect n = cpvneg(cpArbiterGetNormal(arb));

  	if (n.y > groundNormal->y) {
      groundNormal->x = n.x;
  		groundNormal->y = n.y;
  	}
  }

  Once throwed;
  bool attacking;

// private:
  Keybind _bind;
  float remainingBoost;
  bool grounded;
  bool lastJumpState;
  float dmg;

  cpBody* playerBody;
  cpShape* playerShape;
};

class BallBehavior {
public:
  BallBehavior() {}

  void initialize(cpBody* body) {
    cpBodySetVelocityUpdateDataFunc(body, CP_VELOCITY_MEM_FN(BallBehavior, updateFunc), this);
    body->userData = this;
  }

  void updateFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt) {

  	// Skip kinematic bodies.
  	if(cpBodyGetType(body) == CP_BODY_TYPE_KINEMATIC) return;

  	body->v = cpvadd(cpvmult(body->v, damping), cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), dt));
  	body->w = body->w*damping + body->t*body->i_inv*dt;

  	// Reset forces.
  	body->f = cpvzero;
  	body->t = 0.0f;

    if (throwed.justActivated()) {
      throwed.lock();

      cpVect direction = cpvzero;
      cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)contactDirectionCheck, &direction);
      direction = direction * 1000.f;

      cpVect b2pos = cpBodyGetPosition(body);
      cpBodyApplyImpulseAtWorldPoint(body, direction, b2pos);
    }
  }

  static void contactDirectionCheck(cpBody* body, cpArbiter* arb, cpVect* direction) {
    cpShape *s1, *s2;
    cpArbiterGetShapes(arb, &s1, &s2);

    if (cpShapeGetCollisionType(s2) == 1) {
      cpVect n = cpvneg(cpArbiterGetNormal(arb));
      if (n.x != 0 || n.y != 0) {
        *direction = n;
      }
    }
  }

  Once throwed;
};

class Test19: public BaseTestScreen {
public:
  Test19()
  {
    batch->setCamera(camera);
    sprite->setTexture(Core::Assets()->get<Texture>("box"));

    space = cpSpaceNew();
    space->iterations = 10;
    space->gravity = {0, -GRAVITY};

    cpBody *body, *staticBody = cpSpaceGetStaticBody(space);
    cpShape *shape;

    // Create segments around the edge of the screen.
    auto win_size = Core::App()->getSize();
    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(0, win_size.y), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(win_size.x, 0), cpv(win_size.x, win_size.y), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(win_size.x, 0), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0, win_size.y), cpv(win_size.x, win_size.y), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(0, win_size.y / 16), cpv(win_size.x / 16, 0), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(win_size.x - win_size.x / 16, 0), cpv(win_size.x, win_size.y / 16), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    // Set up the player
    body = cpSpaceAddBody(space, cpBodyNew(1.0f, INFINITY));
    body->p = cpv(win_size.x / 4, win_size.y / 2);

    shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(-15.0, -27.5, 15.0, 27.5), 5.0));
    shape->e = 0.0f; shape->u = 0.0f;
    shape->type = 1;
    cpShapeSetCollisionType(shape, 1);
    cpShapeSetFilter(shape, cpShapeFilterNew(1, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES));
    auto plShape = shape;

    // shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(15.0, -27.5, 60.0, 27.5), 5.0));
    // shape->e = 0.0f;
    // shape->u = 0.0f;
    // shape->type = 1;
    // cpShapeSetCollisionType(shape, 1);
    // cpShapeSetSensor(shape, 1);
    // cpShapeSetFilter(shape, cpShapeFilterNew(1, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES));
    // shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(-60.0, -27.5, -15.0, 27.5), 5.0));
    // shape->e = 0.0f;
    // shape->u = 0.0f;
    // shape->type = 1;
    // cpShapeSetCollisionType(shape, 1);
    // cpShapeSetSensor(shape, 1);
    // cpShapeSetFilter(shape, cpShapeFilterNew(1, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES));

    Keybind pl1;
    pl1.set("Left", KeyEvent::Key::Left);
    pl1.set("Right", KeyEvent::Key::Right);
    pl1.set("Jump", KeyEvent::Key::Up);
    pl1.set("Attack", KeyEvent::Key::Down);
    playerOne.initialize(pl1, body, plShape);

    ///////////////

    body = cpSpaceAddBody(space, cpBodyNew(1.0f, INFINITY));
    body->p = cpv(win_size.x / 2 + win_size.x / 4, win_size.y / 4);

    shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(-15.0, -27.5, 15.0, 27.5), 5.0));
    shape->e = 0.0f; shape->u = 0.0f;
    shape->type = 1;
    cpShapeSetCollisionType(shape, 1);

    Keybind pl2;
    pl2.set("Left", KeyEvent::Key::Q);
    pl2.set("Right", KeyEvent::Key::D);
    pl2.set("Jump", KeyEvent::Key::Z);
    pl2.set("Attack", KeyEvent::Key::S);
    playerTwo.initialize(pl2, body, shape);

    // Ball
    body = cpSpaceAddBody(space, cpBodyNew(1, cpMomentForCircle(1, 0, 25, cpvzero)));
    cpBodySetPosition(body, cpv(100, 100));
    shape = cpSpaceAddShape(space, cpCircleShapeNew(body, 25, cpvzero));
    cpShapeSetFriction(shape, 0.7);
    cpShapeSetCollisionType(shape, 2);

    auto collisionHandler = cpSpaceAddCollisionHandler(space, 1, 2);
    collisionHandler->separateFunc = [](cpArbiter* arb, cpSpace* space, void* data) {
      cpBody *b1, *b2;
      cpArbiterGetBodies(arb, &b1, &b2);

      if (b2->userData) {
        auto behavior = static_cast<BallBehavior*>(b2->userData);
        behavior->throwed.reset();
      }
    };

    collisionHandler->postSolveFunc = [](cpArbiter* arb, cpSpace* space, void* data) {
      cpBody *b1, *b2;
      cpArbiterGetBodies(arb, &b1, &b2);
      PlayerMovement *pl;
      BallBehavior* ball;

      pl = static_cast<PlayerMovement*>(b1->userData);
      ball = static_cast<BallBehavior*>(b2->userData);

      if (pl->attacking)
        ball->throwed.activate();
    };

    auto playerCollHandler = cpSpaceAddCollisionHandler(space, 1, 1);
    playerCollHandler->postSolveFunc = [](cpArbiter* arb, cpSpace* space, void* data) {
      cpBody *b1, *b2;
      cpArbiterGetBodies(arb, &b1, &b2);
      PlayerMovement *m1, *m2;

      m1 = static_cast<PlayerMovement*>(b1->userData);
      m2 = static_cast<PlayerMovement*>(b2->userData);

      if (m1->attacking) {
        m2->throwed.activate();
      } else if (m2->attacking) {
        m1->throwed.activate();
      }
    };

    playerCollHandler->separateFunc = [](cpArbiter* arb, cpSpace* space, void* data) {
      cpBody *b1, *b2;
      cpArbiterGetBodies(arb, &b1, &b2);

      if (b1->userData) {
        auto behavior = static_cast<PlayerMovement*>(b1->userData);
        behavior->throwed.reset();
      }

      if (b2->userData) {
        auto behavior = static_cast<PlayerMovement*>(b2->userData);
        behavior->throwed.reset();
      }
    };

    ballBehavior.initialize(body);
  }

  virtual void dispose() {
    cpSpaceFree(space);
  }

  virtual void update(float delta) override {
    camera->update();

    playerOne.update(TIME_STEP);
    playerTwo.update(TIME_STEP);

    cpVect p1pos = cpBodyGetPosition(playerOne.playerBody);
    p1dmg->transform.position.x = p1pos.x;
    p1dmg->transform.position.y = p1pos.y;
    p1dmg->transform.position.z = 0.5f;
    p1dmg->setTint(Color::Red);
    p1dmg->setContent(format("%.0f", playerOne.dmg));

    cpVect p2pos = cpBodyGetPosition(playerTwo.playerBody);
    p2dmg->transform.position.x = p2pos.x;
    p2dmg->transform.position.y = p2pos.y;
    p2dmg->transform.position.z = 0.5f;
    p2dmg->setTint(Color::Red);
    p2dmg->setContent(format("%.0f", playerTwo.dmg));

    cpSpaceStep(space, TIME_STEP);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    drawer.update(space);
    drawer.draw(camera);

    batch->begin();
    batch->draw(p1dmg);
    batch->draw(p2dmg);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  gui::Text::Ref text;

  gui::Text::Ref p1dmg;
  gui::Text::Ref p2dmg;

  DebugDrawer drawer;
  SimpleBatch::Ref batch;
  Sprite::Ref sprite;

  cpSpace* space;
  PlayerMovement playerOne;
  PlayerMovement playerTwo;
  BallBehavior ballBehavior;
};
