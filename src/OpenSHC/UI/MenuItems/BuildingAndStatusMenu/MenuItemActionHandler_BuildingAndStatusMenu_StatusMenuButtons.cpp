#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0043E490
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons(int param_1, ...)
        {
            if (param_1 == 71 && DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo == 75
                && INT_00b96120::instance == 4) {
                param_1 = Map::Buildings::BT_OXTETHER;
            }
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = param_1;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL)
                && (param_1 != Map::Buildings::BT_KEEPDOOR_LEFT)) {
                MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(0xf, (BuildingType)((int)(param_1)));
            }
        }

    }
}
}
