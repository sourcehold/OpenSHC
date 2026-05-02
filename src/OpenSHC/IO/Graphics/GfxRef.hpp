/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/GfxRef.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct GfxRef {

            int width; // 0x00000000 length: 4
            int height; // 0x00000004 length: 4
            int offsetInBuffer; // 0x00000008 length: 4
            int backwardsOffsetInBuffer; // 0x0000000C length: 4

        } GfxRef;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GfxRef) == 16, GfxRef);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
