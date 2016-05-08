/*
    Algorithm utils.
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

#ifndef HX3D_UTILS_ALGORITHM
#define HX3D_UTILS_ALGORITHM

#include <vector>

namespace hx3d {

/**
@brief Useful algorithm helpers
*/
namespace algo {

/**
@brief Function application helper on a container.

@param container  Container
@param func       Function

<i>Example code</i>

@code
// Vector creation from 1 to 6
std::vector<int> v = {1, 2, 3, 4, 5, 6};

// Display each value
algo::apply(v, [](int e) { Log.Info("Num: %d", e); });
@endcode
*/
template <class Container, class Function>
void apply(Container& container, Function func);

/**
@brief Map a container.

@param container  Container
@param func       Function

@return New container
*/
template <class Container, class Function>
Container map(Container& container, Function func);

/**
@brief Clone a container.

@param src Source container
@param dst Destination container
*/
template <class Source, class Dest>
void clone(Source& src, Dest& dst);

/**
@brief Generate a range.

@param beg First value
@param end Last value

@return Range between 'beg' and 'end'
*/
template <class T>
std::vector<T> range(T beg, T end);

/**
@brief Apply a simple reduce.

@param container  Container
@param init       Base value

@return Accumulated value
*/
template <class Container, class Type>
Type reduce(Container& container, Type init);

/**
@brief Apply a reduce operation.

@param container  Container
@param init       Base value
@param operation  Operation

@return Accumulated value
*/
template <class Container, class Type, class Operation>
Type reduce(Container& container, Type init, Operation operation);

} /* algo */
} /* hx3d */

#include "hx3d/utils/_inline/algorithm.inl.hpp"

#endif /* HX3D_UTILS_ALGORITHM */
