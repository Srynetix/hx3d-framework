/*
    Graphics header.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#pragma once

#include "hx3d/graphics/animation.hpp"
#include "hx3d/graphics/color.hpp"
#include "hx3d/graphics/error.hpp"
#include "hx3d/graphics/font.hpp"
#include "hx3d/graphics/framebuffer.hpp"
#include "hx3d/graphics/gl.hpp"
#include "hx3d/graphics/image.hpp"
#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/particle_emitter.hpp"
#include "hx3d/graphics/particle_manager.hpp"
#include "hx3d/graphics/particle.hpp"
#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/texture_atlas.hpp"
#include "hx3d/graphics/texture_region.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/text.hpp"
#include "hx3d/graphics/transform.hpp"

#include "hx3d/graphics/batches/simple_batch.hpp"
#include "hx3d/graphics/batches/batch.hpp"
#include "hx3d/graphics/batches/fast_batch.hpp"
#include "hx3d/graphics/batches/particle_batch.hpp"
#include "hx3d/graphics/batches/ordered_batch.hpp"

#include "hx3d/graphics/buffers/array_buffer.hpp"
#include "hx3d/graphics/buffers/attribute_array_buffer.hpp"
#include "hx3d/graphics/buffers/attribute_stream_buffer.hpp"
#include "hx3d/graphics/buffers/attribute.hpp"
#include "hx3d/graphics/buffers/buffer.hpp"
#include "hx3d/graphics/buffers/index_array_buffer.hpp"
#include "hx3d/graphics/buffers/multi_array_buffer.hpp"

#include "hx3d/graphics/cameras/camera.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"
#include "hx3d/graphics/cameras/perspective_camera.hpp"

#include "hx3d/graphics/geometries/cube_geometry.hpp"
#include "hx3d/graphics/geometries/geometry.hpp"
#include "hx3d/graphics/geometries/origin_geometry.hpp"
#include "hx3d/graphics/geometries/sprite_geometry.hpp"
#include "hx3d/graphics/geometries/quad_geometry.hpp"
#include "hx3d/graphics/geometries/star_geometry.hpp"

#include "hx3d/graphics/transitions/fade_transition.hpp"
#include "hx3d/graphics/transitions/transition.hpp"

#include "hx3d/graphics/viewports/fit_viewport.hpp"
#include "hx3d/graphics/viewports/viewport.hpp"

#include "hx3d/graphics/skeletons/skeleton.hpp"
#include "hx3d/graphics/skeletons/joint.hpp"
#include "hx3d/graphics/skeletons/bone.hpp"
