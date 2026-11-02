#include "../MenuView.func.hpp"

#include "OpenSHC/Globals/DAT_MenuViewStackTop.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4020
    MenuView* MenuView::Constructor_MenuView(
        MenuViewType menuID, cdeclVoidFunc* prepareMenuView, cdeclVoidFunc* doInitial, cdeclVoidFunc* doEveryFrame)
    {
        this->menuID = menuID;
        this->prepare = prepareMenuView;
        this->doInitial = doInitial;
        this->doEveryFrame = doEveryFrame;
        this->nextMenuViewPtr = DAT_MenuViewStackTop::instance;
        DAT_MenuViewStackTop::instance = this;
        return this;
    }

}
}
