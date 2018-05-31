#ifndef Magnum_GlmIntegration_GtxIntegration_h
#define Magnum_GlmIntegration_GtxIntegration_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
@brief Integration of GLM experimental extension types

Provides conversion for the following types:

| Magnum type                           | Equivalent GLM type               |
| ------------------------------------- | --------------------------------- |
| @ref Magnum::DualQuaternion "DualQuaternion", @ref Magnum::DualQuaterniond "DualQuaterniond" | `glm::dualquat`, `glm::ddualquat` |

Types with extra qualifiers (such as `glm::mediump_ddualquat`) are treated the
same as types with no qualifier. Debug output using @ref Corrade::Utility::Debug
for all types is provided as well. Example usage:

@snippet GlmIntegration.cpp GtxIntegration

See @ref Magnum/GlmIntegration/Integration.h
and @ref Magnum/GlmIntegration/GtxIntegration.h for conversion of other types.
*/

#include <glm/gtx/dual_quaternion.hpp>

#include "Magnum/Math/DualQuaternion.h"
#include "Magnum/GlmIntegration/GtcIntegration.h"

#ifndef DOXYGEN_GENERATING_OUTPUT
namespace Magnum { namespace Math { namespace Implementation {

/* Dual quaternion */

template<class T,
    #if GLM_VERSION < 990
    glm::precision
    #else
    glm::qualifier /* thanks, GLM */
    #endif
q> struct DualQuaternionConverter<T, glm::tdualquat<T, q>> {
    static DualQuaternion<T> from(const glm::tdualquat<T, q>& other) {
        return {Quaternion<T>(other.real), Quaternion<T>(other.dual)};
    }

    static glm::tdualquat<T, q> to(const DualQuaternion<T>& other) {
        return {glm::tquat<T, q>(other.real()), glm::tquat<T, q>(other.dual())};
    }
};

}}}
#endif

namespace glm {
    /**
     * @brief Debug output operator for GLM dual quaternion types
     *
     * Uses `glm::to_string()` internally.
     */
    template<class T,
        #if GLM_VERSION < 990
        glm::precision
        #else
        glm::qualifier /* thanks, GLM */
        #endif
    q> Corrade::Utility::Debug& operator<<(Corrade::Utility::Debug& debug, const tdualquat<T, q>& value);
}

#endif