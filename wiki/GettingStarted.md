# Getting Started

Welcome to the hx3d Framework !  
Here you will learn to create a new project and get started.

You will also learn how to create an **animated loading screen !**

## Table of contents

1. [Prerequisites](#prereq)
2. [Generation and execution](#genex)
3. [Analyzing the existing code and structure](#exist)
4. [Create a loading screen](#create)

## <a name="prereq"></a> 1. Prerequisites

In this guide, I suppose that we are on a **Linux** system.  
You can easily follow this guide using another system (just type `windows` instead of `linux` in the *build commands*).

Before all, you will need some programs:
  - **Python 3**
  - **Git**
  - **CMake**
  - And **Ninja** (a small and fast build system)

I will let you install it alone, on Windows it can be tiring, on Linux and Mac it's just plain simple.

Now, you will need to fetch the **[hx3d Generator](https://github.com/Srynetix/hx3d-generator)**, specially created for project creation.

So, create a folder somewhere, and start a terminal:

```bash
# Let's clone the generator

~/hx3d-test> git clone https://github.com/Srynetix/hx3d-generator.git generator
```

---

## <a name="genex"></a> 2. Generation and execution

### Project generation

Now, you just need to generate a game.  
The syntax is quite simple:
```./generate.py  --new [game name] [game folder] [game package name]```

For tests purposes, we will name the game `Example`, create an `example-game` directory inside of `~/hx3d-game`, and name the package `com.me.examplegame`.

```bash
# Let's use it
~/hx3d-test> cd generator
~/hx3d-test/generator> ./generate.py --new Example ../example-game com.me.examplegame
```

The generator will automatically clone the hx3d framework and its dependencies.  
Once it is finished, you should see *"Done."* at the end.

```bash
[...]
Done.

~/hx3d-test/generator> cd ../example-game
~/hx3d-test/example-game> _
```

### Ready to use

Now you should be able to compile and run the test game.  
You can always read the docs here: **[srynetix.github.io](https://srynetix.github.io)**.

```bash
~/hx3d-test/example-game> ./build.py linux --execute # or -e
```

If it's all good, it should compile and start the game with moving stars.  
If not, you can **[add an issue](https://github.com/Srynetix/hx3d-framework/issues/new)** to help the project.

You can also launch the tests and the demo application to have a little showcase:

```bash
~/hx3d-test/example-game> ./build.py linux --test --execute # or -te
```
-----------

## <a name="exist"></a> 3. Analyzing the existing code

We will begin with the main project structure:

- **builds**: contains the python builders and dependencies for the project building.
- **cmake**: contains CMake helper files (to reduce code).
- **dependencies**: contains the framework precompiled dependencies, such as *SDL2*.
- **engine**: contains the hx3d framework code, it is needed to build your game.
- **game**: contains your game code. It's the **only folder you should edit in**.
- **tests**: contains the hx3d framework unit tests.
- **wiki**: contains Markdown pages to help about the framework.
- and finally **build.py**: the project build script.

To summarize, you only need to care about the **game** folder, which is structured like this:

- **android**: contains the android specific code
- **assets**: contains your resources (music/textures/etc.)
- **core**: contains the common code (**this is where you will spend most of your time**)
- **desktop**: contains the desktop specific code (Linux/Windows/MacOS)
- **ios**: contains the iOS specific code
- and finally **GameFiles.cmake**, which indexes your `.cpp` files.

In the **desktop** folder (and other platform folders too), you can see a **main.cpp** file, which is the entry-point of your game (with the application configuration).  

So you will write most of your code in the **core** folder.  
Right now, there are two important classes:
- the `Example` class (or *the name you have chosen*), which inherit the [`Game`](https://srynetix.github.io/doc/html/classhx3d_1_1window_1_1_game.html) class
- and the `TestScreen` class, which inherit a basic [`Screen`](https://srynetix.github.io/doc/html/classhx3d_1_1window_1_1_screen.html) with moving stars.

**`Example` class**
```c++
#ifndef GAME_EXAMPLE
#define GAME_EXAMPLE

#include "hx3d/window/game.hpp"

class Example: public hx3d::window::Game {
  virtual void create() override;
};

#endif
```

```c++
#include "game/example.hpp"

#include "game/screens/test_screen.hpp"

#include "hx3d/utils/assets.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/events.hpp"

using namespace hx3d;

void Example::create() {

  /** Want to load a texture ?
    *   Core::Assets()->create<Texture>("texture_name", "textures/here.png")
    */

  Core::Events()->emulateTouchWithMouse(true);

  this->setScreen(Make<TestScreen>());
}
```

**`TestScreen` class**
```c++
#ifndef GAME_SCREENS_TESTSCREEN
#define GAME_SCREENS_TESTSCREEN

#include "hx3d/window/screen.hpp"

#include "hx3d/graphics/shader.hpp"
#include "hx3d/graphics/batch.hpp"

#include "hx3d/graphics/cameras/perspective_camera.hpp"

#include "hx3d/graphics/geometries/star_geometry.hpp"
#include "hx3d/graphics/geometries/origin_geometry.hpp"

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;

class TestScreen: public Screen {

public:
  TestScreen();

  virtual void update(float delta) override;
  virtual void render() override;
  virtual void resize(int width, int height) override;

private:
  Ptr<Shader> shader;

  PerspectiveCamera camera;
  Batch batch;

  Mesh star;
  Mesh origin;

  float angle;
};

#endif
```

```c++
#include "game/screens/test_screen.hpp"

#include "hx3d/core/core.hpp"
#include "hx3d/window/application.hpp"
#include "hx3d/window/game.hpp"
#include "hx3d/window/events.hpp"

#include "hx3d/graphics/framebuffer.hpp"

#include "hx3d/math/number_utils.hpp"
#include "hx3d/math/random.hpp"

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/assets.hpp"

TestScreen::TestScreen():
  shader(Core::Assets()->get<Shader>("base")),
  camera(0.1f, 100.f)
{
  camera.translate(glm::vec3(0.f, 0.f, -5.f));
  camera.rotate(180.f, glm::vec3(0, 1, 0));

  batch.setCamera(camera);
  batch.setShader(shader);

  origin.setGeometry(Make<geom::OriginGeometry>());
  origin.transform.position = glm::vec3(0);
  origin.transform.size = glm::vec3(0.5f);

  star.setGeometry(Make<geom::StarGeometry>());

  angle = 0.f;
}

void TestScreen::update(float delta) {
  camera.rotateAround(glm::vec3(0.f, 0.f, 0.f), 1.f, glm::vec3(0, 1, 0));
  camera.update();

  if (Core::CurrentSystem == Core::SystemType::Android) {
    if (Core::Events()->isKeyJustPressed(KeyEvent::Key::AndroidBack)) {
      Core::CurrentGame()->stop();
    }
  }

  if (Core::Events()->isKeyPressed(KeyEvent::Key::Escape)) {
    Core::CurrentGame()->stop();
  }
}

void TestScreen::resize(int width, int height) {
}

void TestScreen::render() {

  Framebuffer::clear(Color(0, 0, 0));

  batch.begin();

  star.transform.size = glm::vec3(0.3f);
  star.transform.position.x = 0;
  star.transform.position.y = 0;
  star.transform.position.z = 0;
  star.transform.rotation.x = std::sin(glm::radians(angle * 10));
  star.transform.rotation.y = glm::radians(angle * 2);
  batch.draw(star);

  star.transform.size = glm::vec3(0.1f);
  star.transform.rotation.y = glm::radians(-angle * 4);

  star.transform.position.x = -0.75f;
  batch.draw(star);

  star.transform.position.x = 0.f;
  star.transform.position.z = -0.75f;
  batch.draw(star);

  star.transform.position.x = 0.75f;
  star.transform.position.z = 0.f;
  batch.draw(star);

  star.transform.position.x = 0;
  star.transform.position.z = 0.75f;
  batch.draw(star);

  star.transform.position.y = 0.75f;
  star.transform.position.z = 0;
  batch.draw(star);

  star.transform.position.y = -0.75f;
  batch.draw(star);

  batch.draw(origin);

  angle = math::mclamp(angle + 0.5f, 0.f, 360.f);

  batch.end();
}
```

With the help of the [**official documentation**](https://srynetix.github.io/doc/html/index.html), you can try to deduce what is going on here.

In the next step, we will create a new screen which can act as a loading screen.

## <a name="create"></a> 4. Create a loading screen

Let's create a **new screen**.
Create a `LoadingScreen` class:
  - `LoadingScreen.hpp` in `game/core/include/game/screens`
  - `LoadingScreen.cpp` in `game/core/src/screens`

### a. The header file

Put an *include guard* and inherit the [`Screen`](https://srynetix.github.io/doc/html/classhx3d_1_1window_1_1_screen.html) class.  

You don't need to implement all the `Screen` methods.
For this example, only implement `update` and `render`, and create a *constructor*.

To simplify a little we will do something quite **not recommendable**: *use namespaces in a header file* !  
If you want, you can write all the namespaces each time you need them, as `Screen` is in reality `hx3d::window::Screen`.

`LoadingScreen.hpp`
```c++
#ifndef GAME_SCREENS_LOADINGSCREEN
#define GAME_SCREENS_LOADINGSCREEN

#include "hx3d/window/screen.hpp"

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;

class LoadingScreen: public Screen {

public:
  LoadingScreen();

  virtual void update(float delta) override;
  virtual void render() override;
};

#endif
```

To actually render something, we will need a [`Batch`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_batch.html) and a [`Camera`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_camera.html).  
We will also need a [`Text`](https://srynetix.github.io/doc/html/classhx3d_1_1gui_1_1_text.html) (in `gui`) and a [`Sprite`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_sprite.html), to display a message with an image.

The `Batch` will draw to the screen, and the `Camera` will manage the screen current view.  
We will create a 2D loading screen, so we will use the [`OrthographicCamera`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_orthographic_camera.html).  
To have a 3D view, you should use a [`PerspectiveCamera`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_perspective_camera.html).

New `LoadingScreen.hpp`
```c++
#ifndef GAME_SCREENS_LOADINGSCREEN
#define GAME_SCREENS_LOADINGSCREEN

#include "hx3d/window/screen.hpp"

#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include "hx3d/gui/text.hpp"

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;

class LoadingScreen: public Screen {

public:
  LoadingScreen();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  Batch batch;
  OrthographicCamera camera;

  Sprite sprite;
  gui::Text text;
};

#endif
```

That's all for our screen class declaration !  
Now we will attack the screen implementation.

### b. The implementation

Start by implementing the functions declared in the header.

Base `LoadingScreen.cpp`
```c++
#include "game/screens/loading_screen.hpp"

LoadingScreen::LoadingScreen() {}

void LoadingScreen::update(float delta) {}

void LoadingScreen::render() {}
```

We will start with the *constructor*.  
We need to build the camera and prepare the batch for drawing.

If we do not initialize the camera manually, it will automatically take the screen width and height, so that's what we will do.

Now, we need to configure the batch.
The batch need two things, a `Camera` and a [`Shader`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_shader.html).  
Fortunately, the framework come with base assets, including *shaders*. So we just have to load it.

To load an asset, you have to use an [`AssetManager`](https://srynetix.github.io/doc/html/classhx3d_1_1_asset_manager.html).  
The core assets (as the shader we will use) are in the [`Core`](https://srynetix.github.io/doc/html/classhx3d_1_1_core.html)'s AssetManager, accessible with `Core::Assets()`.

The `Core` class is a centralized place for the application main components, like the `Application` itself, the `Game`, the `Audio`, etc...  
For example, to have the screen width, just write `Core::App()->getWidth()`.

Now that we know about the `AssetManager`, we just need to use it to load the shader *"base"*.

```c++
#include "hx3d/core/core.hpp"

#include "hx3d/utils/assets.hpp"

LoadingScreen::LoadingScreen() {

  auto shader = Core::Assets()->get<Shader>("base");

  batch.setCamera(camera);
  batch.setShader(shader);
}
```

Before initializing the sprite and the text, we will try to make the screen draw something.

Let's now paint the screen with light blue in the `render` function.  
We need the [`Framebuffer`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_framebuffer.html) class.

As the default framebuffer is used, you only need to do `Framebuffer::clear(Color(r, g, b))`.

```c++
#include "hx3d/graphics/framebuffer.hpp"

void LoadingScreen::render() {
  Framebuffer::clear(Color(145, 242, 219));
}
```

Go to your game *.cpp* file (in my case `example.cpp`), at the following line:

```c++
this->setScreen(Make<TestScreen>());
```

Replace `TestScreen` with `LoadingScreen`, and don't forget to include your screen header at the top.

Now, add your screen *.cpp* file to the `GameFiles.cmake` list, below the `test_screen.cpp` entry:

```cmake
"${CORE_SRC}/screens/loading_screen.cpp"
```

You should now be able to run the game and you should see a light blue screen !

```bash
~hx3d-test/example-game> ./build.py linux -e
```

### c. Draw the sprite !

Now, we will draw our sprite. But before that, we need to load a texture.  
As the framework is shipped with a logo, we can use it.

Go to your game *.cpp* file, in my case `example.cpp`, and add the following start in the beginning of the create function:

```c++
Core::Assets()->create<Texture>("logo", "textures/logo.png");
```

As you may have guessed, it will load the *textures/logo.png* file and add it into the Core's AssetManager at the key *"logo"*.  

Go back to your `LoadingScreen.cpp`, in the *constructor*.  
We first need to get the texture we just added.

You may already know how to:

```c++
auto logo = Core::Assets()->get<Texture>("logo");
```

Super easy ! Now, let's initialize the sprite.

```c++
sprite.setTexture(logo);
sprite.transform.size.x = 300;
sprite.transform.size.y = 300;
sprite.transform.position.x = Core::App()->getWidth() / 2;
sprite.transform.position.y = Core::App()->getHeight() / 2;
```

Here, the sprite will have our texture, will be resized at the *300x300* resolution, and will be centered on the screen.  
To use `Core::App()`, you will need to include the `Application` header at the top.

To draw the sprite, insert this after the screen clearing in the `render` function:

```c++
batch.begin();

batch.draw(sprite);

batch.end();
```

If you start the game (`./build.py linux -e`), you should see the sprite.

### d. Text and animation.

Adding a sprite to a screen is really not difficult, you will see that adding a text is the same thing.
To create a text, we need a [`Font`](https://srynetix.github.io/doc/html/classhx3d_1_1graphics_1_1_font.html).

Guess where is the default font ?... In the Core's AssetManager ! And it's name is "default".

We will create an *orange* text, with a big enough character size.  
So, in the *constructor*:

```c++
auto font = Core::Assets()->get<Font>("default");

text.setFont(font);
text.setCharacterSize(26);
text.setTint(Color(240, 120, 10));
text.setContent("Loading...");

text.transform.position.x = sprite.transform.position.x;
text.transform.position.y = sprite.transform.position.y - 300;
```

That's it, now the drawing (`render` function), between the batch `begin` and `end`:

```c++
batch.draw(text);
```

Start the game, and you have your text !  
But we will try something more interesting: **an animated** text !

In the `render` function, remove the `batch.draw(text)` and replace by this:
```c++
batch.draw(text, math::Function(Core::App()->getElapsedTime() * 2, 0.5f,
  [](float& x, float& y, float t) {
    x = std::sin(t) * 2.f;
    y = std::sin(t) * 5.f;
  }
));
```

> What the f%@* is this ?

Just start the game and try.

Now that you came back, explication time: you can draw texts using a [math function](https://srynetix.github.io/doc/html/classhx3d_1_1math_1_1_function.html) !

Three arguments:
  - The initial value (here, the current elapsed time since the beginning of the game)
  - The speed
  - The actual function with **x**, **y**, and **t** parameter.

In this function, you need to set the new **x** and **y** values to write a letter.

Here, we use simple sinusoidal functions to move the text around.

Finally, let's rotate the logo.  
In the `update` function:

```c++
static float angle = 0.f; // A little ugly, you can also add an "angle" member to your screen definition

sprite.transform.rotation.z = glm::radians(angle);
angle = math::mclamp(angle + 1.f, 0.f, 360.f);
```

To use [`math::mclamp`](https://srynetix.github.io/doc/html/namespacehx3d_1_1math.html#a69897c541b2af73f4a8eedda935e3f11), you need to include "hx3d/math/number_utils.hpp" at the top.

Start your game and the sprite should rotate forever.

---

Here are the screen codes for reference:

`LoadingScreen.hpp`
```c++
#ifndef GAME_SCREENS_LOADINGSCREEN
#define GAME_SCREENS_LOADINGSCREEN

#include "hx3d/window/screen.hpp"

#include "hx3d/graphics/batch.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/cameras/orthographic_camera.hpp"

#include "hx3d/gui/text.hpp"

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::window;

class LoadingScreen: public Screen {

public:
  LoadingScreen();

  virtual void update(float delta) override;
  virtual void render() override;

private:
  Batch batch;
  OrthographicCamera camera;

  Sprite sprite;
  gui::Text text;
};

#endif
```

`LoadingScreen.cpp`
```c++
#include "game/screens/loading_screen.hpp"

#include "hx3d/core/core.hpp"

#include "hx3d/window/application.hpp"
#include "hx3d/utils/assets.hpp"
#include "hx3d/math/number_utils.hpp"

LoadingScreen::LoadingScreen() {
  auto shader = Core::Assets()->get<Shader>("base");
  auto logo = Core::Assets()->get<Texture>("logo");
  auto font = Core::Assets()->get<Font>("default");

  batch.setCamera(camera);
  batch.setShader(shader);

  sprite.setTexture(logo);
  sprite.transform.size.x = 300;
  sprite.transform.size.y = 300;
  sprite.transform.position.x = Core::App()->getWidth() / 2;
  sprite.transform.position.y = Core::App()->getHeight() / 2;

  text.setFont(font);
  text.setCharacterSize(26);
  text.setTint(Color(240, 120, 10));
  text.setContent("Loading...");
  text.transform.position.x = sprite.transform.position.x;
  text.transform.position.y = sprite.transform.position.y - 300;
}

void LoadingScreen::update(float delta) {
  static float angle = 0.f;

  sprite.transform.rotation.z = glm::radians(angle);
  angle = math::mclamp(angle + 1.f, 0.f, 360.f);
}

void LoadingScreen::render() {
  Framebuffer::clear(Color(145, 242, 219));

  batch.begin();

  batch.draw(sprite);
  batch.draw(text, math::Function(Core::App()->getElapsedTime() * 2, 0.5f,
    [](float& x, float& y, float t) {
      x = std::sin(t) * 2.f;
      y = std::sin(t) * 5.f;
    }
  ));

  batch.end();
}
```

---

That's the end of this tutorial !  

Read the docs and try to customize your loading screen.  
Using [events](http://srynetix.github.io/doc/html/classhx3d_1_1window_1_1_event_manager.html) (Core::Events()), try to stop the game by hitting the *Escape* key.
