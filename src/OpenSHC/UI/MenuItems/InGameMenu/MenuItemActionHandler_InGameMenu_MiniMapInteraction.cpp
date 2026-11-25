#include "../InGameMenu.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00ed31d0.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00434270
        void InGameMenu::MenuItemActionHandler_InGameMenu_MiniMapInteraction(int mouseButtonUnk, ...)
        {
            if (mouseButtonUnk == 2
                && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS
                    || DAT_TileMapState::instance.shiftRelated0or3 != 1)) {
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            }
            // no scrolling while a wall, stair or crenel is being dragged out
            if ((DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_WALL
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_WOODWALL
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_STAIR
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_CRENAL)
                && DAT_MouseState::instance.leftClickState) {
                return;
            }
            if (DAT_MouseState::instance.selectionBoxState != 0) {
                return;
            }
            if (DAT_GameCore::instance.isBinkVideoPlaying) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                return;
            }
            if (DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying) {
                return;
            }
            DAT_00ed31d0::instance = 200;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MinimapViewState_Func::scrollViewportToMinimapClick, DAT_MinimapViewState::ptr)();
        }

    }
}
}
