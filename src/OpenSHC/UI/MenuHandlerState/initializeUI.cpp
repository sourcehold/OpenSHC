#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuHandlerState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6A20
    void MenuHandlerState::initializeUI(
        MenuIDMenuElementAddressPair* menuIDMenuElementAddressPair, UC* ucPtr, char* ptrStrongholdUCString)
    {
        this->ucPtrStruct.ucArrayPointer = ucPtr;
        this->pointerToMenuIDMenuElementAddressMap = menuIDMenuElementAddressPair;
        for (MenuIDMenuElementAddressPair* pair = menuIDMenuElementAddressPair; pair->menuID != -1; ++pair) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::loadMenuElements, pair->menuAddress)(0);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::prepareButtonAndAlphaSurface,
            AlphaAndButtonSurfaceObj::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MenuModalComposition_Func::loadAllMenuElementsOfMenuModals, DAT_MenuModalComposition1::ptr)();
    }

}
}
