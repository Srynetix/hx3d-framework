/*
    Sprite node.
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

#ifndef HX3D_ECS_NODES_SPRITENODE
#define HX3D_ECS_NODES_SPRITENODE

#include "hx3d/ecs/node.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/base_batch.hpp"

namespace hx3d {
namespace ecs {

/**
@brief Simple sprite node.
*/
class SpriteNode: public Node {
public:
  /**
  @brief Create a sprite node using a texture

  @param name    Name
  @param texture Texture (Ptr)
  */
  SpriteNode(std::string name, const Ptr<graphics::Texture>& texture);

  virtual void draw(const Ptr<graphics::BaseBatch>& batch) override;
  virtual void update(float delta) override;

protected:
  Ptr<graphics::Texture> _texture;
  Ptr<graphics::Sprite> _sprite;
};

} /* ecs */
} /* hx3d */

#endif /* HX3D_ECS_NODES_SPRITENODE */
