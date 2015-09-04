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

    def clean(self):
        Utils.rmdir(self.path)

    # Engine
    def prepare_engine(self):
        self.prepare_internal("cmake -GNinja ..")
    def build_engine(self):
        self.build_internal()

    # Game
    def build_game(self):
        game_name = config["game_name"]
        Utils.copydir("engine/assets", "{}/{}/assets".format(self.path, game_name))
        Utils.copydir("{}/assets".format(game_name), "{}/{}/assets".format(self.path,game_name))
    def install_game(self):
        game_name = config["game_name"]
        Utils.copy("{}/engine/libhx3d.dll".format(self.path), "{}/{}/libhx3d.dll".format(self.path, game_name))
        Utils.copydir("dependencies/lib/windows/dlls", "{}/{}".format(self.path, game_name))
    def execute_game(self):
        game_name = config["game_name"]
        Utils.execCommand("cd {}/{} && ./{}".format(self.path, game_name, game_name))

    # Tests
    def build_tests(self):
        Utils.copydir("engine/assets", "{}/tests/assets".format(self.path))
        Utils.copydir("tests/assets", "{}/tests/assets".format(self.path))
    def install_tests(self):
        Utils.copy("{}/engine/libhx3d.dll".format(self.path), "{}/tests/libhx3d.dll".format(self.path))
        Utils.copydir("dependencies/lib/windows/dlls", "{}/tests".format(self.path))
    def execute_tests(self):
        Utils.execCommand("cd {}/tests && ./tests".format(self.path))
