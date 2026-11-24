/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ColorChannelMask.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    typedef enum ColorChannelMask {

        CCM_RGB_BLUE = 31, // 0x0000001F
        CCM_RGB555_GREEN = 992, // 0x000003E0
        CCM_RGB565_GREEN = 2016, // 0x000007E0
        CCM_RGB555_RED = 31744, // 0x00007C00
        CCM_RGB565_RED = 63488 // 0x0000F800

    } ColorChannelMask;

    static_assert_cpp98_obj(sizeof(ColorChannelMask) == 4, ColorChannelMask);
} // namespace Rendering
} // namespace OpenSHC
