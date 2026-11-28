/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/MinimapDrawFlags.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum MinimapDrawFlags {

            MDF_CENTER_ON_OFFSETS = 1, // 0x00000001
            MDF_VIEWPORT_BOX = 2, // 0x00000002
            MDF_HALF_SIZE = 4 // 0x00000004

        } MinimapDrawFlags;

        static_assert_cpp98_obj(sizeof(MinimapDrawFlags) == 4, MinimapDrawFlags);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
