/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/UnsortedBinkBufferFlag.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Bink {
        typedef enum UnsortedBinkBufferFlag {

            UBBF_BINKBUFFERAUTO = 0, // 0x00000000
            UBBF_BINKBUFFERDIRECT = 1, // 0x00000001
            UBBF_BINKBUFFERPRIMARY = 1, // 0x00000001
            UBBF_BINKBUFFERDIBSECTION = 2, // 0x00000002
            UBBF_BINKBUFFERGWORLD = 2, // 0x00000002
            UBBF_BINKBUFFERYV12OVERLAY = 3, // 0x00000003
            UBBF_BINKBUFFERYUY2OVERLAY = 4, // 0x00000004
            UBBF_BINKBUFFERUYVYOVERLAY = 5, // 0x00000005
            UBBF_BINKBUFFERYV12OFFSCREEN = 6, // 0x00000006
            UBBF_BINKBUFFERYUY2OFFSCREEN = 7, // 0x00000007
            UBBF_BINKBUFFERUYVYOFFSCREEN = 8, // 0x00000008
            UBBF_BINKBUFFERRGBOFFSCREENVIDEO = 9, // 0x00000009
            UBBF_BINKBUFFERLAST = 10, // 0x0000000A
            UBBF_BINKBUFFERRGBOFFSCREENSYSTEM = 10, // 0x0000000A
            UBBF_BINKBUFFERTYPEMASK = 31, // 0x0000001F
            UBBF_BINKBUFFERRESOLUTION = 8388608, // 0x00800000
            UBBF_BINKBUFFERSHRINKY = 16777216, // 0x01000000
            UBBF_BINKBUFFERSHRINKYINT = 33554432, // 0x02000000
            UBBF_BINKBUFFERSTRETCHY = 67108864, // 0x04000000
            UBBF_BINKBUFFERSTRETCHYINT = 134217728, // 0x08000000
            UBBF_BINKBUFFERSHRINKX = 268435456, // 0x10000000
            UBBF_BINKBUFFERSHRINKXINT = 536870912, // 0x20000000
            UBBF_BINKBUFFERSTRETCHX = 1073741824, // 0x40000000
            UBBF_BINKBUFFERSTRETCHXINT = 2147483648, // 0x80000000
            UBBF_BINKBUFFERSCALES = 4278190080 // 0xFF000000

        } UnsortedBinkBufferFlag;

        static_assert_cpp98_obj(sizeof(UnsortedBinkBufferFlag) == 4, UnsortedBinkBufferFlag);
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
