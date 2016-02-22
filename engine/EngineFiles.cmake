set(
  COMMON_FILES

  # CORE

  "${ENGINE_SRC}/core/core.cpp"

  # AUDIO

  "${ENGINE_SRC}/audio/audio.cpp"
  "${ENGINE_SRC}/audio/effect.cpp"
  "${ENGINE_SRC}/audio/fft.cpp"
  "${ENGINE_SRC}/audio/music.cpp"
  "${ENGINE_SRC}/audio/display.cpp"
  "${ENGINE_SRC}/audio/display/spectrum.cpp"
  "${ENGINE_SRC}/audio/display/waveform.cpp"
  "${ENGINE_SRC}/audio/converters/s16_converter.cpp"

  # WINDOW

  "${ENGINE_SRC}/window/application.cpp"
  "${ENGINE_SRC}/window/application_config.cpp"
  "${ENGINE_SRC}/window/event_manager.cpp"
  "${ENGINE_SRC}/window/game.cpp"
  "${ENGINE_SRC}/window/input_handler.cpp"
  "${ENGINE_SRC}/window/screen.cpp"

  "${ENGINE_SRC}/window/sdl2/sdl2_application.cpp"
  "${ENGINE_SRC}/window/sdl2/sdl2_events.cpp"

  # UTILS

  "${ENGINE_SRC}/utils/benchmark.cpp"
  "${ENGINE_SRC}/utils/bitset.cpp"
  "${ENGINE_SRC}/utils/callback_timer.cpp"
  "${ENGINE_SRC}/utils/chronometer.cpp"
  "${ENGINE_SRC}/utils/file.cpp"
  "${ENGINE_SRC}/utils/log.cpp"
  "${ENGINE_SRC}/utils/object_map.cpp"
  "${ENGINE_SRC}/utils/poolable.cpp"
  "${ENGINE_SRC}/utils/resource.cpp"
  "${ENGINE_SRC}/utils/string.cpp"
  "${ENGINE_SRC}/utils/timer_manager.cpp"
  "${ENGINE_SRC}/utils/timer.cpp"

  # MATH

  "${ENGINE_SRC}/math/function.cpp"
  "${ENGINE_SRC}/math/number_utils.cpp"
  "${ENGINE_SRC}/math/random.cpp"
  "${ENGINE_SRC}/math/vector_utils.cpp"

  # GRAPHICS

  "${ENGINE_SRC}/graphics/animation.cpp"
  "${ENGINE_SRC}/graphics/base_batch.cpp"
  "${ENGINE_SRC}/graphics/batch.cpp"
  "${ENGINE_SRC}/graphics/color.cpp"
  "${ENGINE_SRC}/graphics/error.cpp"
  "${ENGINE_SRC}/graphics/fade_transition.cpp"
  "${ENGINE_SRC}/graphics/font.cpp"
  "${ENGINE_SRC}/graphics/framebuffer.cpp"
  "${ENGINE_SRC}/graphics/image.cpp"
  "${ENGINE_SRC}/graphics/mesh.cpp"
  "${ENGINE_SRC}/graphics/ordered_batch.cpp"
  "${ENGINE_SRC}/graphics/particle_emitter.cpp"
  "${ENGINE_SRC}/graphics/particle_manager.cpp"
  "${ENGINE_SRC}/graphics/particle.cpp"
  "${ENGINE_SRC}/graphics/shader.cpp"
  "${ENGINE_SRC}/graphics/sprite.cpp"
  "${ENGINE_SRC}/graphics/stencil.cpp"
  "${ENGINE_SRC}/graphics/texture_atlas.cpp"
  "${ENGINE_SRC}/graphics/texture_region.cpp"
  "${ENGINE_SRC}/graphics/texture.cpp"
  "${ENGINE_SRC}/graphics/transform.cpp"
  "${ENGINE_SRC}/graphics/transition.cpp"

  "${ENGINE_SRC}/graphics/viewports/fit_viewport.cpp"
  "${ENGINE_SRC}/graphics/viewports/viewport.cpp"

  "${ENGINE_SRC}/graphics/cameras/camera.cpp"
  "${ENGINE_SRC}/graphics/cameras/orthographic_camera.cpp"
  "${ENGINE_SRC}/graphics/cameras/perspective_camera.cpp"

  "${ENGINE_SRC}/graphics/buffers/attribute_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/buffers/attribute_stream_buffer.cpp"
  "${ENGINE_SRC}/graphics/buffers/attribute.cpp"
  "${ENGINE_SRC}/graphics/buffers/index_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/buffers/multi_array_buffer.cpp"

  "${ENGINE_SRC}/graphics/geometries/base_geometry.cpp"
  "${ENGINE_SRC}/graphics/geometries/cube_geometry.cpp"
  "${ENGINE_SRC}/graphics/geometries/geometry.cpp"
  "${ENGINE_SRC}/graphics/geometries/origin_geometry.cpp"
  "${ENGINE_SRC}/graphics/geometries/sprite_geometry.cpp"
  "${ENGINE_SRC}/graphics/geometries/star_geometry.cpp"

  # GUI

  "${ENGINE_SRC}/gui/system.cpp"
  "${ENGINE_SRC}/gui/text.cpp"
  "${ENGINE_SRC}/gui/widget.cpp"

  # NET

  "${ENGINE_SRC}/net/net.cpp"

  # 2D PHYSICS

  "${ENGINE_SRC}/physics/2d/attractor.cpp"
  "${ENGINE_SRC}/physics/2d/collider.cpp"
  "${ENGINE_SRC}/physics/2d/collision_matrix.cpp"
  "${ENGINE_SRC}/physics/2d/collisions.cpp"
  "${ENGINE_SRC}/physics/2d/manifold.cpp"
  "${ENGINE_SRC}/physics/2d/mass.cpp"
  "${ENGINE_SRC}/physics/2d/material.cpp"
  "${ENGINE_SRC}/physics/2d/world.cpp"

  "${ENGINE_SRC}/physics/2d/colliders/circle.cpp"
  "${ENGINE_SRC}/physics/2d/colliders/polygon.cpp"

  "${ENGINE_SRC}/physics/2d/attractors/global_attractor.cpp"
  "${ENGINE_SRC}/physics/2d/attractors/point_attractor.cpp"
  "${ENGINE_SRC}/physics/2d/attractors/zone_attractor.cpp"

  # ECS

  "${ENGINE_SRC}/ecs/component.cpp"
  "${ENGINE_SRC}/ecs/engine.cpp"
  "${ENGINE_SRC}/ecs/entity.cpp"
  "${ENGINE_SRC}/ecs/node.cpp"
  "${ENGINE_SRC}/ecs/scene_graph.cpp"
  "${ENGINE_SRC}/ecs/system.cpp"

  "${ENGINE_SRC}/ecs/nodes/sprite_node.cpp"
  "${ENGINE_SRC}/ecs/nodes/physics_node.cpp"

  # TWEENS

  "${ENGINE_SRC}/tweens/base_tween.cpp"
  "${ENGINE_SRC}/tweens/callback.cpp"
  "${ENGINE_SRC}/tweens/delay.cpp"
  "${ENGINE_SRC}/tweens/parallel.cpp"
  "${ENGINE_SRC}/tweens/sequence.cpp"
  "${ENGINE_SRC}/tweens/tween_manager.cpp"
)
