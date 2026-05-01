/**
  path: 'OpenSHC/Input/ModifierKeyState.func.hpp'
*/

#include "OpenSHC/Input/ModifierKeyState.hpp"
namespace OpenSHC {
namespace Input {
    namespace ModifierKeyState_Func {

        MACRO_FUNCTION_RESOLVER(void (ModifierKeyState::*)(), false, Address::SHC_3BB0A8C1_0x00468A20,
            &ModifierKeyState::updateCtrlShiftAltKeyStateMemory)
        updateCtrlShiftAltKeyStateMemory;

    } // namespace ModifierKeyState_Func
} // namespace Input
} // namespace OpenSHC
