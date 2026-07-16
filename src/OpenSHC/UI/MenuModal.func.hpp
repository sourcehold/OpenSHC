/**
  path: 'OpenSHC/UI/MenuModal.func.hpp'
*/

#include "OpenSHC/UI/MenuModal.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuModal_Func {

        // Constructor

        MACRO_FUNCTION_RESOLVER(
            MenuModal* (MenuModal::*)(MenuModalType, int, int, int, int, int, int, MenuModalRenderFunction*, Menu*),
            false, Address::SHC_3BB0A8C1_0x004A9E00, &MenuModal::Constructor_MenuModal)
        Constructor_MenuModal;

    } // namespace MenuModal_Func
} // namespace UI
} // namespace OpenSHC
