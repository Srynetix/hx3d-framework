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

    def clean(self):
        Utils.rmdir(self.path)

    # Engine
    def prepare_engine(self):
        self.prepare_internal("CXX={} cmake -GNinja ..".format(config["compiler_name"]))
    def build_engine(self):
        self.build_internal()

    # Game
    def build_game(self):
        game_name = config["game_name"]
        Utils.copydir("engine/assets", "{}/{}/assets".format(self.path, game_name))
        Utils.copydir("{}/assets".format(game_name), "{}/{}/assets".format(self.path, game_name))
    def debug_game(self):
        game_name = config["game_name"]
        debugger_name = config["debugger_name"]
        Utils.execCommand("cd {}/{} && {} ./{}".format(self.path, game_name, debugger_name, game_name))
    def execute_game(self):
        game_name = config["game_name"]
        profCmd = "apitrace trace --api gl" if self._profile else ""
        Utils.execCommand("cd {}/{} && {} ./{}".format(self.path, game_name, profCmd, game_name))

    # Tests
    def build_tests(self):
        Utils.copydir("engine/assets", "{}/tests/assets".format(self.path))
        Utils.copydir("tests/assets", "{}/tests/assets".format(self.path))
    def debug_tests(self):
        debugger_name = config["debugger_name"]
        Utils.execCommand("cd {}/tests && {} ./tests".format(self.path, debugger_name))
    def execute_tests(self):
        profCmd = "apitrace trace --api gl" if self._profile else ""
        Utils.execCommand("cd {}/tests && {} ./tests".format(self.path, profCmd))
