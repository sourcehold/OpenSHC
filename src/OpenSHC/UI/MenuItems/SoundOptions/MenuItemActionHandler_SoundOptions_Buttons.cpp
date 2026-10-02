#include "../SoundOptions.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/UI/MenuItems/SoundOptions.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/SoundMenuClickType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::SoundMenuClickType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004940B0
        void SoundOptions::MenuItemActionHandler_SoundOptions_Buttons(SoundMenuClickType param_1, ...)
        {
            bool bVar1;
            int local_8;
            int local_4;
            switch (param_1) {
            case OpenSHC::UI::Enums::SMCT_SOUND_MENU_RETURNUnk:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case OpenSHC::UI::Enums::SMCT_TOGGLE_SOUND_ACTIVEUnk:
                break;
            case OpenSHC::UI::Enums::SMCT_TOGGLE_GENIE:
                bVar1 = DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar == 0;
                DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar = (uint)bVar1;
                DAT_GameCore::instance.genieVoiceActive = (uint)bVar1;
                return;
            default:
                return;
            case OpenSHC::UI::Enums::SMCT_RESET_SPEECH_VOLUME:
                param_1 = ((SoundMenuClickType)0x55);
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    2, 3, &local_4, &local_8, (int*)&param_1);
                return;
            case OpenSHC::UI::Enums::SMCT_RESET_SFX_VOLUME:
                param_1 = ((SoundMenuClickType)0x50);
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    1, 3, &local_4, &local_8, (int*)&param_1);
                return;
            case OpenSHC::UI::Enums::SMCT_RESET_MUSIC_VOLUME:
                param_1 = ((SoundMenuClickType)0x5a);
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    0, 3, &local_4, &local_8, (int*)&param_1);
            }
            if (DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar == 0) {
                DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar = 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::Audio::MSS::SoundSystem_Func::activateSoundFromMenuFuncUnk, DAT_SoundSystemState::ptr)();
            }
            DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Audio::MSS::SoundSystem_Func::deactivateSoundFromMenuFuncUnk, DAT_SoundSystemState::ptr)();
        }

    }
}
}
