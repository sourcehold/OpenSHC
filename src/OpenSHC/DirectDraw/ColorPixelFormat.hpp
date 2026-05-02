/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/ColorPixelFormat.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectDraw {
    typedef enum ColorPixelFormat {

        CPF_RGB15 = 1365, // 0x00000555
        CPF_RGB16 = 1381 // 0x00000565

    } ColorPixelFormat;

    static_assert_cpp98_obj(sizeof(ColorPixelFormat) == 4, ColorPixelFormat);
} // namespace DirectDraw
} // namespace OpenSHC
