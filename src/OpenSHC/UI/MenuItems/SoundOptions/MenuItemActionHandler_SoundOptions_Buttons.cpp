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

        // FUNCTION: STRONGHOLDCRUSADER 0x004940B0
        void SoundOptions::MenuItemActionHandler_SoundOptions_Buttons(SoundMenuClickType param_1, ...)
        {
            switch (param_1) {
            case OpenSHC::UI::Enums::SMCT_TOGGLE_SOUND_ACTIVEUnk:
                if (DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar != 0) {
                    DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::deactivateSoundFromMenuFuncUnk,
                        DAT_SoundSystemState::ptr)();
                    return;
                }
                DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar = 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::Audio::MSS::SoundSystem_Func::activateSoundFromMenuFuncUnk, DAT_SoundSystemState::ptr)();
                return;
            case OpenSHC::UI::Enums::SMCT_TOGGLE_GENIE: {
                int genieVoiceActive = FALSE;
                if (DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar == 0) {
                    genieVoiceActive = TRUE;
                }
                DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar = genieVoiceActive;
                DAT_GameCore::instance.genieVoiceActive = (OpenSHC::WindowsHelper::Enums::BOOLEnum)genieVoiceActive;
                return;
            }
            case OpenSHC::UI::Enums::SMCT_SOUND_MENU_RETURNUnk:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case OpenSHC::UI::Enums::SMCT_RESET_MUSIC_VOLUME: {
                int local_8;
                int local_4;
                param_1 = (SoundMenuClickType)90;
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    0, 3, &local_4, &local_8, (int*)&param_1);
                return;
            }
            case OpenSHC::UI::Enums::SMCT_RESET_SFX_VOLUME: {
                int local_8;
                int local_4;
                param_1 = (SoundMenuClickType)80;
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    1, 3, &local_4, &local_8, (int*)&param_1);
                return;
            }
            case OpenSHC::UI::Enums::SMCT_RESET_SPEECH_VOLUME: {
                int local_8;
                int local_4;
                param_1 = (SoundMenuClickType)85;
                MACRO_CALL(OpenSHC::UI::MenuItems::SoundOptions_Func::MenuItemActionHandler_SoundOptions_VolumeSlider)(
                    2, 3, &local_4, &local_8, (int*)&param_1);
                return;
            }
            }
        }

    }
}
}
