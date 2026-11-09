#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0043E490
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons(int tabType, ...)
        {
            if (tabType == UI::Enums::BASMTT_STATUS_OVERVIEW
                && DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo == UI::Enums::BASMTT_STATUS_FOOD
                && INT_00b96120::instance == UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP) {
                tabType = UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP;
            }
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = tabType;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL)
                && (tabType != UI::Enums::BASMTT_STATUS_OVERVIEW)) {
                MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(15, (BuildingType)tabType);
            }
        }

    }
}
}
