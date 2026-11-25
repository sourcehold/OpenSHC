#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042A840
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_SkirmishTypeAndBalance(int button, ...)
        {
            if (DAT_00b960dc::instance != 0) {
                return;
            }
            // only the host changes the game type and the balance
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            // button 4 draws the balance bar and button 20 the game type panel: clicking them changes nothing
            if (button == 4 || button == 20) {
                return;
            }
            // buttons 1 to 3 pick the game type
            if (button >= 1 && button <= 3) {
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = button;
            }
            // the balance buttons start at 10 and set balance 1 from there, 3 (button 12) being even
            if (button >= 10) {
                DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = button - 9;
                // 256 at either end, 255 one step from even, 254 at even
                if (button == 10 || button == 14) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x100);
                }
                if (button == 11 || button == 13) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFF);
                }
                if (button == 12) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFE);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        }

    }
}
}
