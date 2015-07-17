# README #

hx3d is a simple and easy to understand 2D/3D game framework made in C++.  
It is inspired by the well-known Java framework LibGDX plus some books and tutorials on the subject.

It currently uses SDL 2 as a window backend, with SDL_image for texture loading.  
All the rendering is done with OpenGL 3+ / OpenGLES 2.0.

## Dependencies ##

##### For building #####
- CMake *3.3*
- Ninja *1.6*

##### For compiling/executing #####
- SDL *2.0.3*
- SDL_image *2.0.0*
- Freetype *2.6*
- Freetype-GL *git*

These are included in the dependencies repository.

##### For testing #####
- Google Test *1.7.0*

## Features ##

- **Core**
  - [x] Application and Game systems
  - [x] Screens
  - [x] Asset management
  - [x] File handling
  - **Event management**
    - [x] Window
    - [x] Keyboard
    - [x] Mouse
    - [x] Touch
- **Graphics**
  - [x] Textures
  - [x] Batches
  - [x] Meshes
  - [x] Framebuffers
  - [x] Cameras
  - [x] Viewports
  - [ ] Multi-component buffers ?
  - [ ] Lights
  - [ ] Particle system
  - [ ] SVG handling ? Preprocessing ?
  - [ ] Mesh loading
  - [ ] Animation and tweening
- **Fonts**
  - [x] Basic font drawing
  - [x] Individual glyph drawing
- **Physics**
  - [ ] 2D physics (Box2D ?)
  - [ ] 3D physics (Bullet ?)
- **Scene Graph & ECS**
  - [x] Entity Component System
  - [ ] Scene Graph / Node system
- **Audio**
  - [ ] Base audio
- **GUI**
  - [ ] Base GUI
- **Network**
  - [ ] Base network (SDL_net ?)
- **Scripting**
  - [ ] Base scripting (Lua ?)
  - [ ] Console (because it's cool !)

## Compatible systems ##

- Linux
- Android
- Windows
- Mac OS X

#### Will be available later ####

- iOS
- Emscripten ?

## Building ##

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

- `build.py linux`: build the game for Linux
- `build.py linux -d`: build and debug the game for Linux
- `build.py android --execute`: build and start the game for Android
- `build.py windows -c`: clean the build for Windows

When the `game` folder isn't here, the build script only build the framework.
So the options as `--install`, `--execute`, or `--debug` will not work (you will be warned.)
