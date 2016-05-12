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
namespace window {

class InputHandler;

/**
@brief Manage real-time inputs
*/
class EventManager {

public:
    EventManager();
    virtual ~EventManager();

    /**
    @brief Poll the event queue.

    > IMPLEMENTATION NEEDED.
    */
    void poll();

    /**
    @brief Test the window state.

    @param type Type

    @return True/False
    */
    bool isWindowState(WindowEvent::Type type);

    /**
    @brief Test if a mouse button have been clicked.

    @param button Button

    @return True/False
    */
    bool isMouseButtonClicked(MouseButtonEvent::Button button);
    /**
    @brief Test if a mouse button have been relased.

    @param button Button

    @return True/False
    */
    bool isMouseButtonReleased(MouseButtonEvent::Button button);
    /**
    @brief Test if a mouse button have just been clicked.

    @param button Button

    @return True/False
    */
    bool isMouseButtonJustClicked(MouseButtonEvent::Button button);
    /**
    @brief Test if a mouse button have just been released.

    @param button Button

    @return True/False
    */
    bool isMouseButtonJustReleased(MouseButtonEvent::Button button);

    /**
    @brief Test if the mouse wheel have been turned in a direction.

    @param direction Direction

    @return True/False
    */
    bool isMouseWheelTurned(MouseWheelEvent::Direction direction);

    /**
    @brief Test if the screen have been touched.

    @return True/False
    */
    bool isScreenTouched();
    /**
    @brief Test if the screen have been released.

    @return True/False
    */
    bool isScreenReleased();
    /**
    @brief Test if the screen have been just touched.

    @return True/False
    */
    bool isScreenJustTouched();
    /**
    @brief Test if the screen have been just released.

    @return True/False
    */
    bool isScreenJustReleased();

    /**
    @brief Test if the key have been pressed.

    @param key Key

    @return True/False
    */
    bool isKeyPressed(KeyEvent::Key key);
    /**
    @brief Test if the key have been released.

    @param key Key

    @return True/False
    */
    bool isKeyReleased(KeyEvent::Key key);
    /**
    @brief Test if the key have just been pressed.

    @param key Key

    @return True/False
    */
    bool isKeyJustPressed(KeyEvent::Key key);
    /**
    @brief Test if the key have just been released.

    @param key Key

    @return True/False
    */
    bool isKeyJustReleased(KeyEvent::Key key);

    /**
    @brief Get the current mouse position.

    @return Mouse position
    */
    glm::vec2 getMousePosition();
    /**
    @brief Get the current mouse movement.

    @return Mouse movement
    */
    glm::vec2 getMouseMovement();
    /**
    @brief Get the current mouse wheel movement.

    @return Mouse wheel movement
    */
    glm::vec2 getMouseWheelMovement();

    /**
    @brief Get the current touch position.

    @return Touch position
    */
    glm::vec2 getTouchPosition();
    /**
    @brief Get the screen converted touch position.

    @return Screen converted touch position
    */
    glm::vec2 getScreenConvertedTouchPosition();
    /**
    @brief Get the current touch movement.

    @return Touch movement
    */
    glm::vec2 getTouchMovement();
    /**
    @brief Get the current touch pressure.

    @return Touch pressure
    */
    float getTouchPressure();

    /**
    @brief Emulate the touch system with the mouse.

    This will emulate the touch position and the touch movement.
    When clicked, the touch pressure will be at 1.0.

    @param value True/False
    */
    void emulateTouchWithMouse(bool value);

    /**
    @brief Define an input handler.

    @param handler Input handler (Raw ptr)
    */
    void setInputHandler(InputHandler* handler);

    /**
    @brief Define an input handler.

    @param handler Input handler (Ptr)
    */
    void setInputHandler(Pointer<InputHandler> handler);

  protected:
    /// @brief Keys released
    bool* _keysReleased;
    /// @brief Keys pressed
    bool* _keysPressed;

    /// @brief Mouse buttons clicked
    bool* _mouseButtonClicked;
    /// @brief Mouse buttons released
    bool* _mouseButtonReleased;

    /// @brief Mouse wheels turned
    bool* _mouseWheelTurned;
    /// @brief Window events
    bool* _windowEvents;

    /// @brief Screen touched ?
    bool _screenTouched;
    /// @brief Screen released ?
    bool _screenReleased;

    /// @brief Mouse position
    glm::vec2 _mousePosition;
    /// @brief Mouse movement
    glm::vec2 _mouseMovement;
    /// @brief Mouse wheel movement
    glm::vec2 _mouseWheelMovement;

    /// @brief Touch position
    glm::vec2 _touchPosition;
    /// @brief Touch movement
    glm::vec2 _touchMovement;
    /// @brief Touch pressure
    float _touchPressure;

    /// @brief Is touch simulated with mouse ?
    bool _touchSimulation;

    /// @brief Current input handler
    InputHandler* _currentHandler;
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_EVENT_MANAGER */
