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

    def prepare(self):
        print("/!\ no preparing.")

    def build(self):
        print("/!\ no building.")

    def install(self):
        print("/!\ no installing.")

    def clean(self):
        print("/!\ no cleaning.")

    def execute(self):
        print("/!\ no executing.")

    def debug(self):
        print("/!\ no debugging.")

    def test(self):
        print("/!\ no testing.")

    def post_build(self):
        pass

    def run(self):
        Utils.gPrint("** {} build **".format(self.name), Fore.YELLOW)
        print()

        if self._clean:
            Utils.gPrint("> Cleaning...")
            self.clean()

        elif self._test:
            Utils.gPrint("> Test mode...")
            self.test()

        else:
            self.prepare()
            self.build()

            self.post_build()

            if self._install:
                print()
                Utils.gPrint("> Installing...")
                self.install()

            if self._execute:
                if self.game_build:
                    print()
                    Utils.gPrint("> Running...")
                    self.execute()
                else:
                    print()
                    Utils.gPrint("> Can not execute: building game OFF.", Fore.RED)

            elif self._debug:
                if self.game_build:
                    print()
                    Utils.gPrint("> Debugging...")
                    self.debug()
                else:
                    print()
                    Utils.gPrint("> Can not debug: building game OFF.", Fore.RED)

        Utils.gPrint("> Done.")

    def prepare_internal(self, command):
        Utils.gPrint("> Preparing...")

        Utils.mkdir(self.path)
        Utils.execCommand("cd {} && {} > /dev/null".format(self.path, command))

    def build_internal(self):
        if not Utils.direxists(self.path):
            self.prepare()

        Utils.gPrint("> Building...")
        Utils.execCommand("cd {} && ninja".format(self.path))
