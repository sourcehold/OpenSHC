#include "../MenuView.func.hpp"

#include "OpenSHC/Globals/DAT_MenuViewStackTop.hpp"

namespace OpenSHC {
namespace UI {

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
