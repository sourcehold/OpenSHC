#include "../MenuView.func.hpp"

#include "OpenSHC/Globals/DAT_MenuViewStackTop.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F4050
    MenuView* MenuView::Constructor_MenuView_Reduced(MenuViewType menuType)
    {
        this->menuID = menuType;
        this->nextMenuViewPtr = DAT_MenuViewStackTop::instance;
        DAT_MenuViewStackTop::instance = this;
        return this;
    }

}
}
