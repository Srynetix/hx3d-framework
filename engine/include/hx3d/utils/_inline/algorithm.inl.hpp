/*
    Algorithms.
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

namespace hx3d {
namespace algo {

template <class Container, class Function>
void apply(Container& container, Function func) {
  std::for_each(container.begin(), container.end(), func);
}

template <class Source, class Dest>
void clone(Source& src, Dest& dst) {
  std::copy(src.begin(), src.end(), std::inserter(dst, dst.begin()));
}

template <class Container, class Type>
Type reduce(Container& container, Type init) {
  return std::accumulate(container.begin(), container.end(), init);
}

template <class Container, class Type, class Operation>
Type reduce(Container& container, Type init, Operation operation) {
  return std::accumulate(container.begin(), container.end(), init, operation);
}

} /* algo */
} /* hx3d */
