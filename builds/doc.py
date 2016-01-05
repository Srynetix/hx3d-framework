#     Doc target.
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

BROWSER = "chromium"

class DocBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("doc", options, game)

    def build_game(self):
        Utils.execCommand("doxygen")
    def execute_game(self):
        Utils.execCommand("{} site/doc/html/index.html".format(BROWSER))
