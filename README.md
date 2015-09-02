# README #

hx3d is a simple and easy to understand 2D/3D game framework made in C++.  
It is inspired by the well-known Java framework LibGDX plus some books and tutorials on the subject.

It currently uses SDL 2 as a window backend, with SDL_image for texture loading.  
All the rendering is done with OpenGL 3+ / OpenGLES 2.0.

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

They are included in the dependencies repository.  
To import them, just clone them in the "dependencies" folder.

You can use the `clone_dependencies.sh` script.

- SDL *2.0.3*
- SDL_image *2.0.0*
- Freetype *2.6*
- Freetype-GL *git*
- Box2D *2.3.1*

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
  - [ ] Lights
  - [ ] Particle system
  - [ ] SVG handling or preprocessing
  - [ ] Mesh loading
  - [ ] Animation and tweening
- **Fonts**
  - [x] Basic font drawing
  - [x] Individual glyph drawing
- **Physics**
  - [ ] *2D physics (Box2D) (in progress)*
  - [ ] 3D physics (Bullet ?)
- **Scene Graph & ECS**
  - [x] Entity Component System
  - [x] Scene Graph and Nodes
  - [x] Hybrid Engine (ZGraph)
- **Audio**
  - [ ] Base audio
- **GUI**
  - [ ] Base GUI
- **Network**
  - [ ] Base network (SDL_net ?)
- **Scripting**
  - [ ] Base scripting (Lua ?)
  - [ ] Console (because it's cool !)

## <a name="systems"></a> Compatible systems ##

- Linux
- Android

#### In process ####

- Windows
- Mac OS X

#### Will be available later ####

- iOS
- Emscripten ?

## <a name="building"></a> Building ##

hx3d has it's own build system made in Python.  
It uses CMake and Ninja internally.

It's simple enough to add new targets easily.

The build script is `build.py`.  
The configuration is in `config.py`.

You must provide the target. The existing targets are:

- `linux`
- `android`
- `windows`
- `macos`

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

## <a name="testing"></a> Testing ##

For now, you can run the tests on Linux.
Just do:

```
  ./build.py linux --test
```

# <a name="new_project"></a> How to create a project #

To create a project, just use the [**hx3d generator**](https://github.com/Srynetix/hx3d-generator).
