#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004659E0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods(
            int resourceType, ...)
        {
            if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                    (Game::Resources::ResourceType)resourceType)) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .marketSelectedResourceType = resourceType;
                DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = UI::Enums::BASMTT_MARKETPLACE_TRADE;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            }
        }

    }
}
}
