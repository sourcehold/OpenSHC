/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Floaters/FloaterVariationFlags.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Floaters {
        typedef enum FloaterVariationFlags {

            FVF_SECOND_PASS = 1, // 0x00000001
            FVF_FIRST_PASS = 2, // 0x00000002
            FVF_SET_RENDERED_OWNER = 4, // 0x00000004
            FVF_USE_TOTAL_HEIGHT = 8, // 0x00000008
            FVF_RENDERED_OWNER_0 = 16, // 0x00000010
            FVF_MASK_IMAGE = 32 // 0x00000020

        } FloaterVariationFlags;

        static_assert_cpp98_obj(sizeof(FloaterVariationFlags) == 4, FloaterVariationFlags);
    } // namespace Floaters
} // namespace Map
} // namespace OpenSHC
