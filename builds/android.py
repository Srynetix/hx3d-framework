#     Android target.
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

from .dependencies.colorama import Fore
from .dependencies.colorama import Style

class AndroidBuilder(Builder):
    def __init__(self, options, game):
        super().__init__("android", options, game)

    def install(self):
        Utils.execCommand("cd {}/android && ant debug install -q".format(config["game_name"]))

    def prepare(self):
        command = \
            "cmake \
            -GNinja \
            -DANDROID_STANDALONE_TOOLCHAIN={} \
            -DCMAKE_TOOLCHAIN_FILE=cmake/android.toolchain.cmake \
            -DCMAKE_BUILD_TYPE={}                  \
            ..".format(config["android_toolchain_path"], config["android_build_type"])

        self.prepare_internal(command)

    def test(self):
        self.prepare()
        self.build_internal()

        game_name = "tests"

        # Libs
        android_hx3d_path = "{}/android/ext/hx3d".format(game_name)
        Utils.mkdir(android_hx3d_path)

        Utils.copy("{}/engine/libhx3d.so".format(self.path), "{}/libhx3d.so".format(android_hx3d_path))
        Utils.copy("{}/{}/lib{}.so".format(self.path, game_name, game_name), "{}/lib{}.so".format(android_hx3d_path, game_name))

        # Includes
        Utils.copydir("engine/include/hx3d", "{}/android/jni/include/hx3d".format(game_name))
        Utils.copydir("{}/core/include/{}".format(game_name, game_name), "{}/android/jni/include/{}".format(game_name, game_name))

        # Assets
        Utils.copydir("engine/assets", "{}/android/assets".format(game_name))
        Utils.copydir("{}/assets".format(game_name), "{}/android/assets".format(game_name))

        print()
        Utils.gPrint("> NDK building...")
        Utils.execCommand("cd {}/android && ndk-build NDK_DEBUG=1".format("tests"))

        print()
        Utils.gPrint("> ANT building...")
        Utils.execCommand("cd {}/android && ant debug -q".format("tests"))

        print()
        Utils.gPrint("> Installing...")
        Utils.execCommand("cd {}/android && ant debug install -q".format("tests"))

    def build(self):
        self.build_internal()
        game_name = config["game_name"]

        if self.game_build:
            # Libs
            android_hx3d_path = "{}/android/ext/hx3d".format(game_name)
            Utils.mkdir(android_hx3d_path)

            Utils.copy("{}/engine/libhx3d.so".format(self.path), "{}/libhx3d.so".format(android_hx3d_path))
            Utils.copy("{}/{}/lib{}.so".format(self.path, game_name, game_name), "{}/lib{}.so".format(android_hx3d_path, game_name))

            # Includes
            Utils.copydir("engine/include/hx3d", "{}/android/jni/include/hx3d".format(game_name))
            Utils.copydir("{}/core/include/{}".format(game_name, game_name), "{}/android/jni/include/{}".format(game_name, game_name))

            # Assets
            Utils.copydir("engine/assets", "{}/android/assets".format(game_name))
            Utils.copydir("{}/assets".format(game_name), "{}/android/assets".format(game_name))

    def clean(self):
        Utils.rmdir(self.path)
        Utils.rmdir(config["game_name"] + "/android/assets")
        Utils.rmdir(config["game_name"] + "/android/ext/hx3d")
        Utils.rmdir(config["game_name"] + "/android/jni/include")

        Utils.rmdir("tests/android/assets")
        Utils.rmdir("tests/android/ext/hx3d")
        Utils.rmdir("tests/android/jni/include")

    def execute(self):
        command = "adb shell am start {}/{}".format(config["android_package_name"], config["android_package_name"] + "." + config["android_activity_name"])
        Utils.execCommand(command)

    def post_build(self):
        if self.game_build:
            print()
            Utils.gPrint("> NDK building...")
            Utils.execCommand("cd {}/android && ndk-build NDK_DEBUG=1".format(config["game_name"]))

            print()
            Utils.gPrint("> ANT building...")
            Utils.execCommand("cd {}/android && ant debug -q".format(config["game_name"]))
