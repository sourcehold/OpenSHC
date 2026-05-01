/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Enums/SoundMenuClickType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum SoundMenuClickType {

            SMCT_SOUND_MENU_RETURNUnk = 17, // 0x00000011
            SMCT_TOGGLE_SOUND_ACTIVEUnk = 34, // 0x00000022
            SMCT_TOGGLE_GENIE = 4294967286, // 0xFFFFFFF6
            SMCT_RESET_SPEECH_VOLUME = 4294967292, // 0xFFFFFFFC
            SMCT_RESET_SFX_VOLUME = 4294967293, // 0xFFFFFFFD
            SMCT_RESET_MUSIC_VOLUME = 4294967294 // 0xFFFFFFFE

        } SoundMenuClickType;

        static_assert_cpp98_obj(sizeof(SoundMenuClickType) == 4, SoundMenuClickType);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
