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

    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6210
    void Rendering::RenderCurrentMenuView()
    {
        MenuView* pMVar1;
        for (pMVar1 = DAT_MenuViewStackTop::instance; pMVar1 != (MenuView*)0x0; pMVar1 = pMVar1->nextMenuViewPtr) {
            /*
              menu id
             */
            if (DAT_GameCore::instance.currentMenuViewType == pMVar1->menuID) {
                if (pMVar1->menuID == OpenSHC::UI::Enums::MVT_NO_VIEW) {
                    if (DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial != FALSE) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderNoViewsFoundWarning)();
                    }
                } else {
                    if (DAT_MenuView_TriggerPrepare::instance != FALSE) {
                        /*
                          renderMenuBackground
                         */
                        (*pMVar1->prepare)();
                    }
                    if ((DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial != FALSE)
                        || (DAT_MenuView_TriggerPrepare::instance != FALSE)) {
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
