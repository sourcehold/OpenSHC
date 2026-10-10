#include "../OverlaySlider.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B0F70
        void OverlaySlider::MenuItemActionHandler_OverlaySlider_Deselect(int param_1, ...)
        {
            if ((DAT_MouseState::instance.rightClickStart)
                && (MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_NONE, FALSE),
                    DAT_MenuModalComposition2::instance.sliderCallbackFunction != (undefined*)0x0)) {
                ((void (*)())DAT_MenuModalComposition2::instance.sliderCallbackFunction)();
                DAT_MenuModalComposition2::instance.minus1 = -1;
            }
            if (DAT_MouseState::instance.leftClickStart) {
                if (DAT_MenuModalComposition2::instance.modalMenu.x <= DAT_MouseState::instance.screenSpaceX
                    && DAT_MouseState::instance.screenSpaceX < DAT_MenuModalComposition2::instance.modalMenu.width
                            + DAT_MenuModalComposition2::instance.modalMenu.x
                    && DAT_MenuModalComposition2::instance.modalMenu.y <= DAT_MouseState::instance.screenSpaceY
                    && DAT_MouseState::instance.screenSpaceY < DAT_MenuModalComposition2::instance.modalMenu.height
                            + DAT_MenuModalComposition2::instance.modalMenu.y) {}
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                if (DAT_MenuModalComposition2::instance.sliderCallbackFunction != (undefined*)0x0) {
                    ((void (*)())DAT_MenuModalComposition2::instance.sliderCallbackFunction)();
                    DAT_MenuModalComposition2::instance.minus1 = -1;
                }
            }
        }

    }
}
}
