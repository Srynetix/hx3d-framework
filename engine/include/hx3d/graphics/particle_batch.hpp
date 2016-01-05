// #ifndef HX3D_GRAPHICS_PARTICLE_BATCH
// #define HX3D_GRAPHICS_PARTICLE_BATCH
//
// #include "hx3d/graphics/geometries/geometry.hpp"
//
// namespace hx3d {
// namespace graphics {
//
// namespace geom {
//
// class ParticleGeometry: public BaseGeometry {
// public:
//
//   ParticleGeometry():
//     BaseGeometry()
//   {
//     addAttribute("New", Attribute("a_new", GL_FLOAT, 2));
//
//     setAttribute("Position", std::vector<float> {
//       -0.5f, -0.5f, 0.f,
//       0.5f, -0.5f, 0.f,
//       -0.5f, 0.5f, 0.f,
//       0.5f, 0.5f, 0.f
//     });
//
//   }
//
//   virtual void draw(Ptr<Shader> shader) override {
//
//   }
// };
//
// } /* geom */
//
// class ParticleBatch {
// private:
//
// public:
//   ParticleBatch(const unsigned int maxParticles) {}
// };
//
// } /* graphics */
// } /* hx3d */
//
// #endif /* HX3D_GRAPHICS_PARTICLE_BATCH */
