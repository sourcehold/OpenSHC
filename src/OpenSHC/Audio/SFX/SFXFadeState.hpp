/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/SFXFadeState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {
        typedef enum SFXFadeState {

            SFXFS_IDLE = 0, // 0x00000000
            SFXFS_FADE_IN = 1, // 0x00000001
            SFXFS_FADE_OUT = 2 // 0x00000002

        } SFXFadeState;

        static_assert_cpp98_obj(sizeof(SFXFadeState) == 4, SFXFadeState);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
