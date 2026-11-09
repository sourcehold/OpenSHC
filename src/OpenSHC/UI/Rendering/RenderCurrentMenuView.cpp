#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuViewStackTop.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6210
    void Rendering::RenderCurrentMenuView()
    {
        for (MenuView* menuView = DAT_MenuViewStackTop::instance; menuView != NULL;
            menuView = menuView->nextMenuViewPtr) {
            // menu id
            if (DAT_GameCore::instance.currentMenuViewType == menuView->menuID) {
                if (menuView->menuID == UI::Enums::MVT_NO_VIEW) {
                    if (DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial) {
                        MACRO_CALL(UI::Rendering_Func::RenderNoViewsFoundWarning)();
                    }
                } else {
                    if (DAT_MenuView_TriggerPrepare::instance) {
                        // renderMenuBackground
                        (*menuView->prepare)();
                    }
                    if ((DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial)
                        || (DAT_MenuView_TriggerPrepare::instance)) {
                        // someRenderFunction
                        (*menuView->doInitial)();
                    }
                    // renderMenuItemsFunction
                    (*menuView->doEveryFrame)();
                }
            }
            // move up in the menu linked list
        }
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = FALSE;
        DAT_MenuView_TriggerPrepare::instance = FALSE;
    }

}
}
