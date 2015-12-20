/*
    Event manager.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef HX3D_WINDOW_EVENT_MANAGER
#define HX3D_WINDOW_EVENT_MANAGER

#include <glm/vec2.hpp>

#include "hx3d/utils/log.hpp"
#include "hx3d/utils/ptr.hpp"

#include "hx3d/window/events.hpp"

namespace hx3d {

class InputHandler;
class EventManager {

public:
    EventManager();
    virtual ~EventManager();

    /**
    Poll the event queue.
    */
    virtual void poll() = 0;

    /**
    Test the window state.

    @param type Type
    */
    bool isWindowState(WindowEvent::Type type);

    /**
    Test if a mouse button have been clicked.

    @param button Button
    */
    bool isMouseButtonClicked(MouseButtonEvent::Button button);
    /**
    Test if a mouse button have been relased.

    @param button Button
    */
    bool isMouseButtonReleased(MouseButtonEvent::Button button);
    /**
    Test if a mouse button have just been clicked.

    @param button Button
    */
    bool isMouseButtonJustClicked(MouseButtonEvent::Button button);
    /**
    Test if a mouse button have just been released.

    @param button Button
    */
    bool isMouseButtonJustReleased(MouseButtonEvent::Button button);

    /**
    Test if the mouse wheel have been turned in a direction.

    @param direction Direction
    */
    bool isMouseWheelTurned(MouseWheelEvent::Direction direction);

    /**
    Test if the screen have been touched.
    */
    bool isScreenTouched();
    /**
    Test if the screen have been released.
    */
    bool isScreenReleased();
    /**
    Test if the screen have been just touched.
    */
    bool isScreenJustTouched();
    /**
    Test if the screen have been just released.
    */
    bool isScreenJustReleased();

    /**
    Test if the key have been pressed.

    @param key Key
    */
    bool isKeyPressed(KeyEvent::Key key);
    /**
    Test if the key have been released.

    @param key Key
    */
    bool isKeyReleased(KeyEvent::Key key);
    /**
    Test if the key have just been pressed.

    @param key Key
    */
    bool isKeyJustPressed(KeyEvent::Key key);
    /**
    Test if the key have just been released.

    @param key Key
    */
    bool isKeyJustReleased(KeyEvent::Key key);

    /**
    Get the current mouse position.

    @return Mouse position
    */
    glm::vec2 getMousePosition();
    /**
    Get the current mouse movement.

    @return Mouse movement
    */
    glm::vec2 getMouseMovement();
    /**
    Get the current mouse wheel movement.

    @return Mouse wheel movement
    */
    glm::vec2 getMouseWheelMovement();

    /**
    Get the current touch position.

    @return Touch position
    */
    glm::vec2 getTouchPosition();
    /**
    Get the current touch movement.

    @return Touch movement
    */
    glm::vec2 getTouchMovement();
    /**
    Get the current touch pressure.

    @return Touch pressure
    */
    float getTouchPressure();

    /**
    Emulate the touch system with the mouse.
    This will emulate the touch position and the touch movement.
    When clicked, the touch pressure will be at 1.0.

    @param value True/False
    */
    void emulateTouchWithMouse(bool value);

    /**
    Define an input handler.

    @param handler Input handler (Raw ptr)
    */
    void setInputHandler(InputHandler* handler);

    /**
    Define an input handler.

    @param handler Input handler (Ptr)
    */
    void setInputHandler(Ptr<InputHandler> handler);

  protected:
    bool* _keysReleased;
    bool* _keysPressed;

    bool* _mouseButtonClicked;
    bool* _mouseButtonReleased;

    bool* _mouseWheelTurned;
    bool* _windowEvents;

    bool _screenTouched;
    bool _screenReleased;

    glm::vec2 _mousePosition;
    glm::vec2 _mouseMovement;
    glm::vec2 _mouseWheelMovement;

    glm::vec2 _touchPosition;
    glm::vec2 _touchMovement;

    float _touchPressure;

    bool _touchSimulation;

    InputHandler* _currentHandler;
};

} /* hx3d */

#endif /* HX3D_WINDOW_EVENT_MANAGER */
