/*
    Texture atlas
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

#ifndef HX3D_GRAPHICS_TEXTURE_ATLAS
#define HX3D_GRAPHICS_TEXTURE_ATLAS

#include "hx3d/utils/file.hpp"
#include "hx3d/utils/resource.hpp"

#include "hx3d/graphics/texture_region.hpp"

#include <map>

namespace hx3d {
namespace graphics {

/**
@brief Multi-elements texture atlas.

One texture in memory, multiple objects !
*/
class TextureAtlas: public Resource {
  public:
    /**
    @brief Load an atlas from a path.

    @param pathToAtlas Path to atlas
    */
    TextureAtlas(std::string pathToAtlas);

    /**
    @brief Get a region following a name.

    @param name Region name

    @return TextureRegion
    */
    Pointer<TextureRegion>& getRegion(std::string name);

  private:
    /**
    @brief Load an atlas from a JSON file.

    @param pathToAtlas Path to atlas
    */
    void loadFromJSON(std::string pathToAtlas);

    /// @brief Texture
    Pointer<Texture> _texture;
    /// @brief Regions
    std::map<std::string, Pointer<TextureRegion>> _regions;
};

} /* graphics */
} /* hx3d */

#endif /* HX3D_GRAPHICS_TEXTURE_ATLAS */
