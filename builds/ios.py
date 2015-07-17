#     iOS target.
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

class iOSBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("ios", options, game)

    def install(self):
        pass

    def prepare(self):
        command = \
            "cmake \
            -GNinja \
            -DCMAKE_TOOLCHAIN_FILE=cmake/iOS.cmake \
            -DIOS_PLATFORM={} \
            ..".format(config["ios_platform"])

        self.prepare_internal(command)

    def build(self):
        self.build_internal()

    def clean(self):
        Utils.rmdir(self.path)
