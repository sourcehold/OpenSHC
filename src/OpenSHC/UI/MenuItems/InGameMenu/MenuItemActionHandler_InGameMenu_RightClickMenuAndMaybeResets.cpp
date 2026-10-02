#include "../InGameMenu.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00438B60
        void InGameMenu::MenuItemActionHandler_InGameMenu_RightClickMenuAndMaybeResets(int param_1, ...)
        {
            DAT_MouseState::instance.mouseBasedEvent = 0;
            if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 != 0) {
                if ((DAT_MouseState::instance.rightClickStart == 0)
                    || ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)))))) {
                    if ((DAT_MouseState::instance.rightClickState != FALSE)
                        && (DAT_MouseState::instance.previewEnabled != 0)) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Input::MouseState_Func::updateRightDragCameraControl, DAT_MouseState::ptr)();
                    }
                } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
                    DAT_MouseState::instance.previewEnabled = 1;
                    DAT_GameSynchronyState::instance.field299_0x109e7c = 1;
                }
                DAT_MouseState::instance.previewEnabled = 0;
            }
        }

    }
}
}
