#include "../BuildingAndStatusMenu.func.hpp"

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
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00465820
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_ChangeRations(int rations, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                if (!MACRO_CALL(OpenSHC::Game_Func::Tutorial_IsActionAllowed)(3, rations)) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(12, (BuildingType)rations);
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = rations;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_CHANGE_RATIONS);
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .rationsSetting3 = rations;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .timeTaxesOrRationsChange = timeGetTime();
        }

    }
}
}
