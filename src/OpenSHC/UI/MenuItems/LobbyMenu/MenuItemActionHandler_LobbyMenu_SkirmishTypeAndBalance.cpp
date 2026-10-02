#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042A840
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...)
        {
            if ((((DAT_00b960dc::instance == 0) && (DAT_GameSynchronyState::instance.isHost != FALSE))
                    && (param_1 != 4))
                && (param_1 != 0x14)) {
                if (param_1 - 1U < 3) {
                    DAT_GameSynchronyState::instance.skirmishGameIntensityType = param_1;
                }
                if (9 < param_1) {
                    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = param_1 + -9;
                    if ((param_1 == 10) || (param_1 == 0xe)) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            ((SoundEffectID)0x100));
                    }
                    if ((param_1 == 0xb) || (param_1 == 0xd)) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3
                                | OpenSHC::Audio::SFX::SEID_PEOPLE_ARE_COMING_TO_THE_CASTLE));
                    }
                    if (param_1 == 0xc) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3
                                | OpenSHC::Audio::SFX::SEID_ARROW_KILL));
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
            }
        }

    }
}
}
