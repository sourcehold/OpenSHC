#include "../TacticalPowerBar.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TacticalPowersHelpTextDisplayBool.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA050
        void TacticalPowerBar::MenuItemActionHandler_TacticalPowerBar_Main(int tacticalPower, ...)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0) {
                return;
            }
            int const barLevel
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .tacticalPowersBarLevel;
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            if (barLevel < (tacticalPower + 1) * 636
                || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .lordKilledByPlayerID
                    != 0) {
                return;
            }
            if (DAT_TacticalPowersHelpTextDisplayBool::instance) {
                DAT_MissionDefinedData::instance.field39_0x1370 = 0;
                DAT_TacticalPowersHelpTextDisplayBool::instance = false;
            }
            if (tacticalPower == 5) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 5;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ACTIVATE_TACTICAL_POWERS);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0x100);
                return;
            }
            DAT_TileMapState::instance.activeTacticalPower = tacticalPower;
            DAT_TileMapState::instance.shiftRelated0or3 = 5;
            switch (tacticalPower) {
            case 2:
            case 3:
            case 4:
            case 6:
            case 13:
            case 16:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0x104);
                return;
            case 1:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_CHAPEL_BELL);
                return;
            case 7:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0x105);
            }
        }

    }
}
}
