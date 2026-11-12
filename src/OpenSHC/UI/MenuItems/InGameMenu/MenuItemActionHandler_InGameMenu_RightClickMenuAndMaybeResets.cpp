#include "../InGameMenu.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00438B60
        void InGameMenu::MenuItemActionHandler_InGameMenu_RightClickMenuAndMaybeResets(int unused, ...)
        {
            DAT_MouseState::instance.mouseBasedEvent = 0;
            if (!DAT_ViewportRenderState::instance.viewportState.field_0x0) {
                return;
            }
            if (!DAT_MouseState::instance.rightClickStart
                || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                        || DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD))) {
                if (DAT_MouseState::instance.rightClickState && DAT_MouseState::instance.previewEnabled) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Input::MouseState_Func::updateRightDragCameraControl, DAT_MouseState::ptr)();
                    return;
                }
            } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
                DAT_MouseState::instance.previewEnabled = 1;
                DAT_GameSynchronyState::instance.editorPlacementPlayerID = 1;
                return;
            }
            DAT_MouseState::instance.previewEnabled = 0;
        }

    }
}
}
