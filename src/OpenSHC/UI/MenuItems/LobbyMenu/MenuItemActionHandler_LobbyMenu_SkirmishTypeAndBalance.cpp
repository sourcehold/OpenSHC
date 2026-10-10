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

        using Audio::SFX::SoundEffectID;
        using Commands::GameCommandType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042A840
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...)
        {
            if (!DAT_00b960dc::instance && DAT_GameSynchronyState::instance.isHost && param_1 != 4 && param_1 != 0x14) {
                if (param_1 - 1U < 3) {
                    DAT_GameSynchronyState::instance.skirmishGameIntensityType = param_1;
                }
                if (9 < param_1) {
                    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = param_1 + -9;
                    if ((param_1 == 10) || (param_1 == 0xe)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            ((SoundEffectID)0x100));
                    }
                    if ((param_1 == 0xb) || (param_1 == 0xd)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (Audio::SFX::SoundEffectID)(Audio::SFX::SEID_UNIT_DAMAGE3
                                | Audio::SFX::SEID_PEOPLE_ARE_COMING_TO_THE_CASTLE));
                    }
                    if (param_1 == 0xc) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                            (Audio::SFX::SoundEffectID)(Audio::SFX::SEID_UNIT_DAMAGE3 | Audio::SFX::SEID_ARROW_KILL));
                    }
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
            }
        }

    }
}
}
