# README #

<img src="https://raw.githubusercontent.com/Srynetix/hx3d-framework/master/engine/assets/textures/logo.png" alt="hx3d Logo" width=200 height=200 />

**Official hx3d Framework documentation site: [srynetix.github.io](https://srynetix.github.io)**

hx3d is an open-source and easy to understand 2D/3D game framework made in C++.  
It is inspired by the well-known Java framework LibGDX plus some books and tutorials on the subject.

hx3d is somewhat modular. For now, rendering is done with SDL2, but one can easily change the implementation.
All the rendering is done with OpenGL 3+ / OpenGLES 2.0.

The "cross-platform" part works good thanks to SDL2.

# Table of contents

- [Dependencies](#dependencies)
- [Features](#features)
- [Compatible systems](#systems)
- [Building](#building)
- [Testing](#testing)
- [How to create a project](#new_project)

## <a name="dependencies"></a> Dependencies ##

##### For building #####
- CMake *3.3*
- Ninja *1.6*

##### For compiling/executing #####

They are included in the [**dependencies repository**](https://github.com/Srynetix/hx3d-dependencies).  
To import them, just clone them in the "dependencies" folder.

You can use the `clone_dependencies.sh` script.

- SDL2 *2.0.3*
- SDL2_mixer *2.0.0*
- Freetype *2.6*
- Freetype-GL *git*
- stb_image *git*

If you want to build for Android, you will need the **Android SDK** and **NDK**.  
For iOS, you will need Mac OS (obviously), and **ios-deploy** to deploy on your device.  

You can install *ios-deploy* with `npm`:

```bash
npm install -g ios-deploy
```

##### For testing #####
- Google Test *1.7.0*

## <a name="features"></a> Features ##

- **Core**
  - [x] Application and Game systems
  - [x] Screens
  - [x] Asset management
  - [x] File handling
  - **Event management**
    - [x] Window
    - [x] Keyboard
    - [x] Mouse
    - [x] Single Touch
    - [ ] Multi Touch
    - [ ] Gestures
- **Graphics**
  - [x] Textures
  - [x] Sprites
  - [x] Batches
  - [x] Meshes
  - [x] Framebuffers
  - [x] Cameras
  - [x] Viewports
  - [x] Particle system
  - [ ] Animations
  - [ ] Lights
  - [ ] SVG handling or preprocessing
  - [ ] Mesh loading
- **Tweening**
  - [x] Base tweening
  - [x] Parallel tweens
  - [x] Tween sequences
- **Fonts**
  - [x] Basic font drawing
  - [x] Individual glyph drawing
- **Physics**
  - [x] Custom 2D physics
  - [ ] 3D physics (Bullet ?)
- **Scene Graph & ECS**
  - [x] Entity Component System
  - [x] Scene Graph and Nodes
  - [x] Hybrid Engine
- **Audio**
  - [x] Base audio
  - [x] Frequency amplitude detection
- **GUI**
  - [ ] Base GUI
- **Network**
  - [ ] Base network
- **Scripting**
  - [ ] Base scripting (Lua ?)
  - [ ] Console (because it's cool !)

## <a name="systems"></a> Compatible systems ##

- Linux
- Android
- Mac OS X
- iOS

#### In process ####

- Windows

#### Will be available later ####

- Emscripten ?

## <a name="building"></a> Building ##

**hx3d** has it's own build system made in Python.  
It uses CMake and Ninja internally.

It's simple enough to add new targets easily.

The build script is `build.py`.  
The configuration is in `config.py`.

You must provide the target. The existing targets are:

- `linux`
- `android`
- `windows`
- `macos`
- `ios`

Then it supports multiple options:

- `-c / --clean`: clean the build
- `-e / --execute`: start the game
- `-i / --install`: install the game
- `-t / --test`: start the HX3D test executable
- `-d / --debug`: debug the game

So, here are some examples:

- `./build.py linux`: build the game for Linux
- `./build.py linux -d`: build and debug the game for Linux
- `./build.py android --execute`: build and start the game for Android
- `./build.py windows -c`: clean the build for Windows

When the `game` folder isn't here, the build script only build the framework.
So the options as `--install`, `--execute`, or `--debug` will not work (you will be warned.)

### Windows building ###

Currently, Windows build are supported using MinGW.

The recommended way is to use MSYS2.
Then, you install the required packages into MSYS2: MinGW-w64, CMake and Ninja.

MSVC *may be* supported later.

## <a name="testing"></a> Testing ##

#### On Android ####

Testing is different on desktop platforms and on Android.  
On Android, you can only play with the test screens.  
Just do:

```
  ./build.py android --test --install
# Or ./build.py android -ti
```

It will install the application "hx3d tests".

#### On desktop ####

Desktop testing works on Linux and Windows.  
Just do:

```
  ./build.py linux --test --install --execute
# Or ./build.py linux -tie
```

# <a name="new_project"></a> How to create a project #

To create a project, just use the [**hx3d generator**](https://github.com/Srynetix/hx3d-generator).  
You can follow the tutorial [**Getting Started**](https://github.com/Srynetix/hx3d-framework/wiki/Getting-Started).
