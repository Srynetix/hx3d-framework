#     Helper functions.
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

import sys, os
import glob
import shutil

from distutils.dir_util import copy_tree

from .colorama import Fore
from .colorama import Style

class Utils:

    @staticmethod
    def copydir(src, dest):
        try:
            copy_tree(src, dest, update=1)
            print('\t- Copied `{}` to `{}`'.format(src, dest))
        except OSError as e:
            print('\t- Directory not copied. Error: %s' % e)

    @staticmethod
    def copy(src, dest):
        if os.path.exists(dest):
            shutil.rmtree(dest, ignore_errors=True)
        try:
            shutil.copy(src, dest)
            print('\t- Copied `{}` to `{}`'.format(src, dest))
        except OSError as e:
            print("\t- File not copied. Error: %s" % e)

    @staticmethod
    def pwd():
        return os.getcwd()

    @staticmethod
    def abs_path(relative_path):
        return Utils.pwd() + "/" + relative_path

    @staticmethod
    def rmdir(relative_path):
        path = Utils.abs_path(relative_path)
        if os.path.exists(path):
            shutil.rmtree(path, ignore_errors=True)

    @staticmethod
    def direxists(relative_path):
        path = Utils.abs_path(relative_path)
        return os.path.exists(path)

    @staticmethod
    def mkdir(relative_path):
        path = Utils.abs_path(relative_path)
        if not (os.path.exists(path)):
            os.makedirs(path)

    @staticmethod
    def execCommand(command):
        code = os.system(command)
        if code != 0:
            Utils.gPrint("> Error.", Fore.RED)
            exit(code)

    @staticmethod
    def gPrint(text, color=Fore.GREEN):
        print(Style.BRIGHT + color + text)
