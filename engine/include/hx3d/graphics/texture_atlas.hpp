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

#include <rapidjson/document.h>

namespace hx3d {

class TextureAtlas: public Resource {
  public:
    TextureAtlas(std::string pathToAtlas) {
      loadFromJSON(pathToAtlas);
    }

    TextureRegion& getRegion(std::string name) {
      return _regions[name];
    }

  private:
    void loadFromJSON(std::string pathToAtlas) {
      auto file = File::loadAsciiFile(pathToAtlas);
      std::string content = file->toString();

      rapidjson::Document d;
      d.Parse(content.c_str());

      std::string image = d["image"].GetString();
      std::string type = d["type"].GetString();

      Log.Info("Loading texture atlas `%s`...", pathToAtlas.c_str());
      Log.Info("\tImage: %s", image.c_str());
      Log.Info("\tType: %s", type == "pure" ? "Pure" : "Animated");

      if (type == "pure") {
        _texture = Make<Texture>(image);

        const rapidjson::Value& frames = d["frames"];
        for (auto it = frames.Begin(); it != frames.End(); ++it) {
          const rapidjson::Value& val = *it;
          std::string name = val["name"].GetString();
          int x = std::atoi(val["x"].GetString());
          int y = std::atoi(val["y"].GetString());
          int w = std::atoi(val["w"].GetString());
          int h = std::atoi(val["h"].GetString());

          TextureRegion region(
            _texture,
            x,
            x + w,
            y,
            y + h
          );

          _regions.emplace(std::make_pair(name, region));
        }

      } else {
        Log.Error("/!\\ Animated atlas not supported yet.");
        return;
      }
    }

    Ptr<Texture> _texture;
    std::map<std::string, TextureRegion> _regions;
};

} /* hx3d */

#endif /* HX3D_GRAPHICS_TEXTURE_ATLAS */
