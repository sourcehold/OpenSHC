/**
  path: 'OpenSHC/UI/MenuModalComposition.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModal.hpp"
#include "OpenSHC/UI/MenuModalComposition.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModalComposition_Func {

        using OpenSHC::UI::MenuModal;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // Constructor

        MACRO_FUNCTION_RESOLVER(MenuModalComposition* (MenuModalComposition::*)(int), false,
            Address::SHC_3BB0A8C1_0x004A9E60, &MenuModalComposition::Constructor_MenuModalComposition)
        Constructor_MenuModalComposition;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(), false, Address::SHC_3BB0A8C1_0x004A9E80,
            &MenuModalComposition::loadAllMenuElementsOfMenuModals)
        loadAllMenuElementsOfMenuModals;

        MACRO_FUNCTION_RESOLVER(MenuModal* (MenuModalComposition::*)(MenuModalType), false,
            Address::SHC_3BB0A8C1_0x004A9EB0, &MenuModalComposition::findModalMenu)
        findModalMenu;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalType, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x004A9ED0, &MenuModalComposition::activateModalDialog)
        activateModalDialog;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalType, int, int), false,
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
            Address::SHC_3BB0A8C1_0x004AA930, &MenuModalComposition::setModalSliderParameters)
        setModalSliderParameters;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(), false, Address::SHC_3BB0A8C1_0x004B0B30,
            &MenuModalComposition::renderMenuModal)
        renderMenuModal;

        MACRO_FUNCTION_RESOLVER(void (MenuModalComposition::*)(MenuModalType), false, Address::SHC_3BB0A8C1_0x004B2820,
            &MenuModalComposition::activateModalDialog2)
        activateModalDialog2;

    } // namespace MenuModalComposition_Func
} // namespace UI
} // namespace OpenSHC
