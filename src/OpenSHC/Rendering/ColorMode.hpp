/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Rendering/ColorMode.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    typedef enum ColorMode {

        RGB_555 = 1365, // 0x00000555
        RGB_565 = 1381 // 0x00000565

    } ColorMode;

    static_assert_cpp98_obj(sizeof(ColorMode) == 4, ColorMode);
} // namespace Rendering
} // namespace OpenSHC
