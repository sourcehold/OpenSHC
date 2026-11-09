#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuViewStackTop.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6210
    void Rendering::RenderCurrentMenuView()
    {
        MenuView* pMVar1;
        for (pMVar1 = DAT_MenuViewStackTop::instance; pMVar1 != (MenuView*)0x0; pMVar1 = pMVar1->nextMenuViewPtr) {
            /*
              menu id
             */
            if (DAT_GameCore::instance.currentMenuViewType == pMVar1->menuID) {
                if (pMVar1->menuID == UI::Enums::MVT_NO_VIEW) {
                    if (DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial) {
                        MACRO_CALL(UI::Rendering_Func::RenderNoViewsFoundWarning)();
                    }
                } else {
                    if (DAT_MenuView_TriggerPrepare::instance) {
                        /*
                          renderMenuBackground
                         */
                        (*pMVar1->prepare)();
                    }
                    if ((DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial)
                        || (DAT_MenuView_TriggerPrepare::instance)) {
                        /*
                          someRenderFunction
                         */
                        (*pMVar1->doInitial)();
                    }
                    /*
                      renderMenuItemsFunction
                     */
                    (*pMVar1->doEveryFrame)();
                }
            }
            /*
              move up in the menu linked list
             */
        }
        DAT_MenuView_TriggerPrepare::instance = FALSE;
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = FALSE;
    }

}
}
