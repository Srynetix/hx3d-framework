#include "./base_test_screen.hpp"

#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_structs.h>
#include <utility>

#include "hx3d/graphics/error.hpp"

using namespace hx3d;

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
    _shader = Core::Assets()->get<Shader>("debugdraw");
    glGenBuffers(1, &_buffer);

    _options.drawCircle = drawCircle;
    _options.drawSegment = drawSegment;
    _options.drawFatSegment = drawFatSegment;
    _options.drawPolygon = drawPolygon;
    _options.drawDot = drawDot;
    _options.flags = (cpSpaceDebugDrawFlags)(CP_SPACE_DEBUG_DRAW_SHAPES | CP_SPACE_DEBUG_DRAW_CONSTRAINTS | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS);
    _options.colorForShape = colorForShape;
    _options.shapeOutlineColor = {200.0f/255.0f, 210.0f/255.0f, 230.0f/255.0f, 1.0f};
    _options.constraintColor = {0.0f, 0.75f, 0.0f, 1.0f};
    _options.collisionPointColor = {1.0f, 0.0f, 0.0f, 1.0f};
  }

  static float PointLineScale;
  static float OutlineWidth;

  static void drawCircle(cpVect pos, cpFloat angle, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {
    auto outlineColor = convcol(cOutlineColor);
    auto fillColor = convcol(cFillColor);

    cpFloat r = radius + 1.0f/PointLineScale;
    Vertex a = {{(GLfloat)(pos.x - r), (GLfloat)(pos.y - r)}, {-1.0f, -1.0f}, fillColor, outlineColor};
    Vertex b = {{(GLfloat)(pos.x - r), (GLfloat)(pos.y + r)}, {-1.0f,  1.0f}, fillColor, outlineColor};
    Vertex c = {{(GLfloat)(pos.x + r), (GLfloat)(pos.y + r)}, { 1.0f,  1.0f}, fillColor, outlineColor};
    Vertex d = {{(GLfloat)(pos.x + r), (GLfloat)(pos.y - r)}, { 1.0f, -1.0f}, fillColor, outlineColor};

    _triangles.push_back(Triangle{a, b, c});
    _triangles.push_back(Triangle{a, c, d});
    _trianglesCount += 2;

    drawSegment(pos, cpvadd(pos, cpvmult(cpvforangle(angle), radius - PointLineScale*0.5f)), cOutlineColor, data);
  }

  static void drawSegment(cpVect a, cpVect b, cpSpaceDebugColor color, void* data) {
    drawFatSegment(a, b, 0.0f, color, color, data);
  }

  static void drawFatSegment(cpVect a, cpVect b, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {

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
    _trianglesCount += 6;
  }

  static void drawPolygon(int count, const cpVect *verts, cpFloat radius, cpSpaceDebugColor cOutlineColor, cpSpaceDebugColor cFillColor, void* data) {
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
      _trianglesCount++;
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
      _trianglesCount += 4;
    }
  }

  static void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor cFillColor, void* data) {
    auto fillColor = convcol(cFillColor);

    float r = (float)(size*0.5f/PointLineScale);
    Vertex a = {{(float)pos.x - r, (float)pos.y - r}, {-1.0f, -1.0f}, fillColor, fillColor};
    Vertex b = {{(float)pos.x - r, (float)pos.y + r}, {-1.0f,  1.0f}, fillColor, fillColor};
    Vertex c = {{(float)pos.x + r, (float)pos.y + r}, { 1.0f,  1.0f}, fillColor, fillColor};
    Vertex d = {{(float)pos.x + r, (float)pos.y - r}, { 1.0f, -1.0f}, fillColor, fillColor};

    _triangles.push_back(Triangle{a, b, c});
    _triangles.push_back(Triangle{a, c, d});
    _trianglesCount += 2;
  }

  static void drawBB(cpBB bb, cpSpaceDebugColor outlineColor, void* data) {
    cpVect verts[] = {
      cpv(bb.r, bb.b),
      cpv(bb.r, bb.t),
      cpv(bb.l, bb.t),
      cpv(bb.l, bb.b),
    };

    drawPolygon(4, verts, 0.0f, outlineColor, {0, 0, 0, 0}, data);
  }

  static cpSpaceDebugColor colorForShape(cpShape *shape, cpDataPointer data)
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

  static void draw(const Pointer<Camera>& camera) {
    Shader::use(_shader);

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle)*_trianglesCount, _triangles.data(), GL_STREAM_DRAW);

    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, vertex, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, aa_coord, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, fill_color, GL_FLOAT);
    SET_ATTRIBUTE(_shader->getProgramID(), struct Vertex, outline_color, GL_FLOAT);

    _shader->setUniformMatrix4f("u_projection", camera->projection);
    _shader->setUniformMatrix4f("u_view", camera->view);
    _shader->setUniformMatrix4f("u_model", glm::mat4(1.f));
    _shader->setUniform1f("u_outline_coef", PointLineScale);

    glDrawArrays(GL_TRIANGLES, 0, _trianglesCount * 3);

    GL_ERROR_CHECK();

    _trianglesCount = 0;
  }

  static void update(cpSpace* space) {
    cpSpaceDebugDraw(space, &_options);
  }

private:
  static GLuint _buffer;
  static std::vector<Triangle> _triangles;
  static unsigned int _trianglesCount;
  static Pointer<Shader> _shader;
  static cpSpaceDebugDrawOptions _options;
};

GLuint DebugDrawer::_buffer;
std::vector<Triangle> DebugDrawer::_triangles;
unsigned int DebugDrawer::_trianglesCount = 0;
Pointer<Shader> DebugDrawer::_shader;
cpSpaceDebugDrawOptions DebugDrawer::_options;
float DebugDrawer::PointLineScale = 1.f;
float DebugDrawer::OutlineWidth = 1.f;

class Test19: public BaseTestScreen {
public:
  Test19()
  {
    camera->translate({-640, -320, 0});
    camera->update();

    batch->setCamera(camera);
    sprite->setTexture(Core::Assets()->get<Texture>("box"));

    space = cpSpaceNew();
    space->iterations = 10;
    space->gravity = {0, -100};

    cpBody *body, *staticBody = cpSpaceGetStaticBody(space);
    cpShape *shape;

    // Create segments around the edge of the screen.
    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(-320,240), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(320,-240), cpv(320,240), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,-240), cpv(320,-240), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    shape = cpSpaceAddShape(space, cpSegmentShapeNew(staticBody, cpv(-320,240), cpv(320,240), 0.0f));
    shape->e = 1.0f; shape->u = 1.0f;

    // Set up the player
    body = cpSpaceAddBody(space, cpBodyNew(1.0f, INFINITY));
    body->p = cpv(0, -200);
    // body->velocity_func = playerUpdateVelocity;
    // playerBody = body;

    shape = cpSpaceAddShape(space, cpBoxShapeNew2(body, cpBBNew(-15.0, -27.5, 15.0, 27.5), 10.0));
    //  shape = cpSpaceAddShape(space, cpSegmentShapeNew(playerBody, cpvzero, cpv(0, radius), radius));
    shape->e = 0.0f; shape->u = 0.0f;
    shape->type = 1;
    // playerShape = shape;

    // Add some boxes to jump on
    for(int i=0; i<6; i++){
      for(int j=0; j<3; j++){
        body = cpSpaceAddBody(space, cpBodyNew(4.0f, INFINITY));
        body->p = cpv(100 + j*60, -200 + i*60);

        shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 50, 50, 0.0));
        shape->e = 0.0f; shape->u = 0.7f;
      }
    }
  }

  virtual void update(float delta) override {
    camera->update();

    cpSpaceStep(space, delta);
    drawer.update(space);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    drawer.draw(camera);

    // batch->begin();
    //
    // sprite->setTint(Color::White);
    // sprite->transform.position.x = 150.f;
    // sprite->transform.position.y = 150.f;
    // sprite->transform.position.z = 0.f;
    // batch->draw(sprite);
    //
    // batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  gui::Text::Ref text;

  DebugDrawer drawer;
  SimpleBatch::Ref batch;
  Sprite::Ref sprite;

  cpSpace* space;
};
