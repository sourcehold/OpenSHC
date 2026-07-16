/**
  path: 'OpenSHC/Input/ModifierKeyState.func.hpp'
*/

#include "OpenSHC/Input/ModifierKeyState.hpp"
namespace OpenSHC {
namespace Input {
    namespace ModifierKeyState_Func {

        // Constructor

        MACRO_FUNCTION_RESOLVER(ModifierKeyState* (ModifierKeyState::*)(), false, Address::SHC_3BB0A8C1_0x00468A10,
            &ModifierKeyState::Constructor_ModifierKeyState)
        Constructor_ModifierKeyState;

        MACRO_FUNCTION_RESOLVER(void (ModifierKeyState::*)(), false, Address::SHC_3BB0A8C1_0x00468A20,
            &ModifierKeyState::updateCtrlShiftAltKeyStateMemory)
        updateCtrlShiftAltKeyStateMemory;

    } // namespace ModifierKeyState_Func
} // namespace Input
} // namespace OpenSHC
