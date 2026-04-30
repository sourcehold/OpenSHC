/**
  path: 'OpenSHC/UI/MenuModalComposition.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/MenuModal.hpp"
#include "OpenSHC/UI/MenuModalComposition.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModalComposition_Func {

        using OpenSHC::UI::MenuModal;
        using OpenSHC::UI::Enums::MenuModalTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(), false, Address::SHC_3BB0A8C1_0x004A9E80,
            &MenuModalComposition::loadAllMenuElementsOfMenuModals)
        loadAllMenuElementsOfMenuModals;

        MACRO_FUNCTION_RESOLVER(MenuModal* (MenuModalComposition::*)(MenuModalTypeInt), false,
            Address::SHC_3BB0A8C1_0x004A9EB0, &MenuModalComposition::findModalMenu)
        findModalMenu;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalTypeInt, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x004A9ED0, &MenuModalComposition::activateModalDialog)
        activateModalDialog;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalTypeInt, int, int), false,
            Address::SHC_3BB0A8C1_0x004AA0A0, &MenuModalComposition::setExtraActiveModalDialog)
        setExtraActiveModalDialog;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(), false, Address::SHC_3BB0A8C1_0x004AA1F0,
            &MenuModalComposition::handleActiveModalDialogUnk)
        handleActiveModalDialogUnk;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(int*, int*, int*, int*), false,
            Address::SHC_3BB0A8C1_0x004AA3E0, &MenuModalComposition::fillWithMenuModalDimensions)
        fillWithMenuModalDimensions;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(int, int, int, undefined*, void*), false,
            Address::SHC_3BB0A8C1_0x004AA480, &MenuModalComposition::setSliderParameters)
        setSliderParameters;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(dword, dword, dword, dword, undefined*), false,
            Address::SHC_3BB0A8C1_0x004AA540, &MenuModalComposition::setSliderParameters2)
        setSliderParameters2;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(int, int, dword, dword, undefined*, undefined*), false,
            Address::SHC_3BB0A8C1_0x004AA930, &MenuModalComposition::meth_0x4aa930)
        meth_0x4aa930;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(), false, Address::SHC_3BB0A8C1_0x004B0B30,
            &MenuModalComposition::renderMenuModal)
        renderMenuModal;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalTypeInt), false,
            Address::SHC_3BB0A8C1_0x004B2820, &MenuModalComposition::activateModalDialog2)
        activateModalDialog2;

    } // namespace MenuModalComposition_Func
} // namespace UI
} // namespace OpenSHC
