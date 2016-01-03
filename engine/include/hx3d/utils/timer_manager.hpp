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

class TimerManager {
  public:
    TimerManager();

    void addNamedTimer(std::string name, CallbackTimer& timer);
    void createNamedTimer(std::string name, float delay, std::function<void()> callback);

    void addTemporaryTimer(CallbackTimer& timer);
    void createTemporaryTimer(float delay, std::function<void()> callback);

    void update(float delta);

  private:
    std::map<std::string, CallbackTimer> _registered;
    std::vector<CallbackTimer> _temporaries;
};

} /* hx3d */

#endif /* HX3D_UTILS_TIMER_MANAGER */
