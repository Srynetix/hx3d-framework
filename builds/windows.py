#     Windows target.
#
#     Copyright (C) 2015 Denis BOURGE
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License as published by the Free Software Foundation; either
#     version 2.1 of the License, or (at your option) any later version.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#     USA

from .dependencies.builder import Builder
from .dependencies.utils import Utils
from .config import config

class WindowsBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("windows", options, game)

    def install(self):
        game_name = config["game_name"]

        Utils.copydir("engine/assets", "{}/{}/assets".format(self.path, game_name))
        Utils.copydir("{}/assets".format(game_name), "{}/{}/assets".format(self.path,game_name))

        Utils.copy("{}/engine/libhx3d.dll".format(self.path), "{}/{}/libhx3d.dll".format(self.path, game_name))

        Utils.copy("dependencies/lib/windows/dlls/glew32.dll", "{}/{}/glew32.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/libjpeg-9.dll", "{}/{}/libjpeg-9.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/libpng16-16.dll", "{}/{}/libpng16-16.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/libtiff-5.dll", "{}/{}/libtiff-5.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/libwebp-4.dll", "{}/{}/libwebp-4.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/SDL2.dll", "{}/{}/SDL2.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/SDL2_image.dll", "{}/{}/SDL2_image.dll".format(self.path, game_name))
        Utils.copy("dependencies/lib/windows/dlls/zlib1.dll", "{}/{}/zlib1.dll".format(self.path, game_name))

    def prepare(self):
        self.prepare_internal("cmake -GNinja ..")

    def build(self):
        self.build_internal()

    def clean(self):
        Utils.rmdir(self.path)

    def execute(self):
        game_name = config["game_name"]
        Utils.execCommand("cd {}/{} && ./{}".format(self.path, game_name, game_name))
