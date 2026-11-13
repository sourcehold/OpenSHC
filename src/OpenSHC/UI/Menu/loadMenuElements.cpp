#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/UC.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // 0x004F4D70 is not declared in the headers yet; it is a UCPointerStruct member (thiscall).
    struct UCProxy {
        void loadMenuElement(int ucID, int* x, int* y, ushort* iconDeactivated, int ucPositionIndex);
    };

    MACRO_FUNCTION_RESOLVER(void (UCProxy::*)(int, int*, int*, ushort*, int), false, Address::SHC_3BB0A8C1_0x004F4D70,
        &UCProxy::loadMenuElement)
    UCProxy_loadMenuElement;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F69D0
    void Menu::loadMenuElements(int ucPositionIndex)
    {
        for (MenuItem* item = this->menuItemArray; item->menuItemType != 102; ++item) {
            if (item->ucID >= 0) {
                MACRO_CALL_MEMBER(UCProxy_loadMenuElement, (UCProxy*)&DAT_MenuHandlerState::instance.ucPtrStruct)(
                    item->ucID, &item->position.position.x, &item->position.position.y, &item->iconDeactivatedUnk_0x36,
                    ucPositionIndex);
            }
        }
    }

}
}
