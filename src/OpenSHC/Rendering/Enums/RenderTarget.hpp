/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Enums/RenderTarget.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Enums {
        typedef enum RenderTarget {

            RT_SCREEN_MENU = 0, // 0x00000000
            RT_MAP_GAME = 1, // 0x00000001
            RT_BUTTON_AND_ALPHA = 2, // 0x00000002
            RT_CONTEXT_BASED = 4294967295 // 0xFFFFFFFF

        } RenderTarget;

        static_assert_cpp98_obj(sizeof(RenderTarget) == 4, RenderTarget);
    } // namespace Enums
} // namespace Rendering
} // namespace OpenSHC
