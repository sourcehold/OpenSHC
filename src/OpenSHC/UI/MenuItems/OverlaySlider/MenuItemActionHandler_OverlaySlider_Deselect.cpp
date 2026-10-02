#include "../OverlaySlider.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B0F70
        void OverlaySlider::MenuItemActionHandler_OverlaySlider_Deselect(int param_1, ...)
        {
            if ((DAT_MouseState::instance.rightClickStart != 0)
                && (MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE),
                    DAT_MenuModalComposition2::instance.sliderCallbackFunction != (undefined*)0x0)) {
                ((void (*)())DAT_MenuModalComposition2::instance.sliderCallbackFunction)();
                DAT_MenuModalComposition2::instance.minus1 = -1;
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                if ((((DAT_MenuModalComposition2::instance.modalMenu.x <= DAT_MouseState::instance.screenSpaceX)
                         && (DAT_MouseState::instance.screenSpaceX < DAT_MenuModalComposition2::instance.modalMenu.width
                                 + DAT_MenuModalComposition2::instance.modalMenu.x))
                        && (DAT_MenuModalComposition2::instance.modalMenu.y <= DAT_MouseState::instance.screenSpaceY))
                    && (DAT_MouseState::instance.screenSpaceY < DAT_MenuModalComposition2::instance.modalMenu.height
                            + DAT_MenuModalComposition2::instance.modalMenu.y)) {}
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                if (DAT_MenuModalComposition2::instance.sliderCallbackFunction != (undefined*)0x0) {
                    ((void (*)())DAT_MenuModalComposition2::instance.sliderCallbackFunction)();
                    DAT_MenuModalComposition2::instance.minus1 = -1;
                }
            }
        }

    }
}
}
