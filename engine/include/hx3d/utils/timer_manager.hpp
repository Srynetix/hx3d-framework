/*
    Timer manager.
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

#ifndef HX3D_UTILS_TIMER_MANAGER
#define HX3D_UTILS_TIMER_MANAGER

#include "hx3d/utils/callback_timer.hpp"
#include <map>
#include <vector>

namespace hx3d {

/**
@brief Manages multiple callback timers.
*/
class TimerManager {
  public:
    TimerManager();

    /**
    @brief Add an existing named timer.

    @param name   Name
    @param timer  Timer
    */
    void addNamedTimer(std::string name, CallbackTimer& timer);

    /**
    @brief Create a new named timer.

    @param name     Name
    @param delay    Delay before callback activation
    @param callback Callback to execute
    */
    void createNamedTimer(std::string name, float delay, std::function<void()> callback);

    /**
    @brief Add an existing temporary timer.

    @param timer  Timer
    */
    void addTemporaryTimer(CallbackTimer& timer);

    /**
    @brief Create a new temporary timer.

    @param delay    Delay before callback activation
    @param callback Callback to execute
    */
    void createTemporaryTimer(float delay, std::function<void()> callback);

    /**
    @brief Update the timers

    @param delta Delta time
    */
    void update(float delta);

  private:
    std::map<std::string, CallbackTimer> _registered;
    std::vector<CallbackTimer> _temporaries;
};

} /* hx3d */

#endif /* HX3D_UTILS_TIMER_MANAGER */
