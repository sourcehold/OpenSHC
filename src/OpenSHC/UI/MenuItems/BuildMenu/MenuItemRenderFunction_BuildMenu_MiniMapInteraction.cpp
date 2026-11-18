#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00434300
        void BuildMenu::MenuItemRenderFunction_BuildMenu_MiniMapInteraction(int unused, ...)
        {
            if (DAT_ButtonCurrentlyInteracting::instance
                && DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS
                    || DAT_TileMapState::instance.shiftRelated0or3 == 1)) {
                DAT_MinimapViewState::instance.minimapClickEnabled = TRUE;
                return;
            }
            DAT_MinimapViewState::instance.minimapClickEnabled = FALSE;
        }

    }
}
}
