#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::BuildMenuTabType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00434300
        void BuildMenu::MenuItemRenderFunction_BuildMenu_MiniMapInteraction(int param_1, ...)
        {
            if (DAT_ButtonCurrentlyInteracting::instance
                && DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == UI::Enums::BMTT_SOLDIERS
                    || (DAT_TileMapState::instance.shiftRelated0or3 == 1))) {
                DAT_MinimapViewState::instance.minimapClickEnabled = 1;
            }
            DAT_MinimapViewState::instance.minimapClickEnabled = 0;
        }

    }
}
}
