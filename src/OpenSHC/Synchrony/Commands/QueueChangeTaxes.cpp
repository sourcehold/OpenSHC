#include "../Commands.func.hpp"

#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465700
    void Commands::QueueChangeTaxes()
    {
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSliderUI
            == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .taxesSetting2) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
            if (!MACRO_CALL(OpenSHC::Game_Func::Tutorial_IsActionAllowed)(4,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI)) {
                // the tutorial doesn't allow the change yet: the slider goes back
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .taxesSliderUI
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .taxesSetting2;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                return;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(13,
                (OpenSHC::Map::Buildings::BuildingType)DAT_GameState::instance
                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .taxesSliderUI);
        }
        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            .timeTaxesOrRationsChange = timeGetTime();
        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSetting2
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .taxesSliderUI;
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .taxesSliderUI;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_CHANGE_TAXES);
    }

}
}
