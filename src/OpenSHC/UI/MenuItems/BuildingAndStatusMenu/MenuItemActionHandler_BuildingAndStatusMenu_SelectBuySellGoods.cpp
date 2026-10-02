#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuViewType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004659E0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods(int param_1, ...)
        {
            BOOLEnum BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable,
                DAT_GameState::ptr)((OpenSHC::Game::Resources::ResourceType)param_1);
            if (BVar1 != FALSE) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .marketSelectedResourceType = param_1;
                DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x39;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            }
        }

    }
}
}
