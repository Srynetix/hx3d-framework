#     Base target for building.
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

from .utils import Utils

from .colorama import Fore
from .colorama import Style

class Builder:
    def __init__(self, name, options, game):
        self.name = name;
        self.path = "_build_{}".format(name)
        self.game_build = game
        self._execute = options.execute
        self._install = options.install
        self._clean = options.clean
        self._debug = options.debug
        self._test = options.test

    # Engine
    def prepare_engine(self):
        pass
    def build_engine(self):
        pass

    # Game
    def prepare_game(self):
        pass
    def build_game(self):
        pass
    def install_game(self):
        pass
    def debug_game(self):
        pass
    def execute_game(self):
        pass

    # Tests
    def prepare_tests(self):
        pass
    def build_tests(self):
        pass
    def install_tests(self):
        pass
    def debug_tests(self):
        pass
    def execute_tests(self):
        pass

    def clean(self):
        pass

    def run(self):
        Utils.gPrint("** {} build **".format(self.name), Fore.YELLOW)
        print()

        if self._clean:
            Utils.gPrint("> Cleaning...")
            self.clean()

        else:
            Utils.gPrint("> Preparing engine...")
            self.prepare_engine()
            Utils.gPrint("> Building engine...")
            self.build_engine()

            if self._test:
                Utils.gPrint("> Preparing tests...")
                self.prepare_tests()
                Utils.gPrint("> Building tests...")
                self.build_tests()

                if self._install:
                    print()
                    Utils.gPrint("> Installing tests...")
                    self.install_tests()

                if self._debug:
                    print()
                    Utils.gPrint("> Debugging tests...")
                    self.debug_tests()

                elif self._execute:
                    print()
                    Utils.gPrint("> Executing tests...")
                    self.execute_tests()

            elif self.game_build:
                Utils.gPrint("> Preparing game...")
                self.prepare_game()
                Utils.gPrint("> Building game...")
                self.build_game()

                if self._install:
                    print()
                    Utils.gPrint("> Installing game...")
                    self.install_game()

                if self._debug:
                    print()
                    Utils.gPrint("> Debugging game...")
                    self.debug_game()

                elif self._execute:
                    print()
                    Utils.gPrint("> Executing game...")
                    self.execute_game()

        Utils.gPrint("> Done.")

    def prepare_internal(self, command):
        Utils.mkdir(self.path)
        Utils.execCommand("cd {} && {} > /dev/null".format(self.path, command))

    def build_internal(self):
        Utils.execCommand("cd {} && ninja".format(self.path))
