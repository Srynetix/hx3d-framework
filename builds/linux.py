#     Linux target.
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

class LinuxBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("linux", options, game)

    def install(self):
        pass

    def prepare(self):
        self.prepare_internal("cmake -GNinja ..")

    def build(self):
        self.build_internal()

        if self.game_build:
            game_name = config["game_name"]
            Utils.copydir("engine/assets", "{}/{}/assets".format(self.path, game_name))
            Utils.copydir("{}/assets".format(game_name), "{}/{}/assets".format(self.path, game_name))

    def clean(self):
        Utils.rmdir(self.path)

    def test(self):
        self.prepare();
        self.build_internal();

        game_name = config["game_name"]

        Utils.copydir("engine/assets", "{}/tests/assets".format(self.path))
        Utils.copydir("tests/assets".format(game_name), "{}/tests/assets".format(self.path))

        Utils.execCommand("cd {}/tests && ./tests".format(self.path))

    def debug(self):
        game_name = config["game_name"]
        debugger_name = config["debugger_name"]

        Utils.execCommand("cd {}/{} && {} ./{}".format(self.path, game_name, debugger_name, game_name))

    def execute(self):
        game_name = config["game_name"]
        Utils.execCommand("cd {}/{} && ./{}".format(self.path, game_name, game_name))
