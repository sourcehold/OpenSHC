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

        using Audio::SFX::SoundEffectID;
        using Commands::GameCommandType;
        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA050
        void TacticalPowerBar::MenuItemActionHandler_TacticalPowerBar_Main(int param_1, ...)
        {
            int iVar1;
            if ((((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                     || (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER))
                    || (!DAT_GameState::instance.mapAndTime.skirmishNoRushTicks))
                && (iVar1
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .tacticalPowersBarLevel,
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)(),
                    (param_1 + 1) * 0x27c <= iVar1
                        && (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .lordKilledByPlayerID
                            == 0))) {
                if (DAT_TacticalPowersHelpTextDisplayBool::instance != false) {
                    DAT_MissionDefinedData::instance.field39_0x1370 = 0;
                    DAT_TacticalPowersHelpTextDisplayBool::instance = false;
                }
                if (param_1 == 5) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 5;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_ACTIVATE_TACTICAL_POWERS);
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        ((SoundEffectID)0x100));
                }
                DAT_TileMapState::instance.activeTacticalPower = param_1;
                DAT_TileMapState::instance.shiftRelated0or3 = 5;
                switch (param_1) {
                case 1:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        Audio::SFX::SEID_CHAPEL_BELL);
                    return;
                case 2:
                case 3:
                case 4:
                case 6:
                case 0xd:
                case 0x10:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        ((SoundEffectID)0x104));
                    return;
                case 7:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        ((SoundEffectID)0x105));
                }
            }
        }

    }
}
}
