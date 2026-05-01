/**
  path: 'OpenSHC/UI/MenuTextInputState.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/MenuTextInputState.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuTextInputState_Func {

        using OpenSHC::UI::Enums::MenuModalTypeInt;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(MenuModalTypeInt), false, Address::SHC_3BB0A8C1_0x004916C0,
            &MenuTextInputState::activateModalDialogAndClearText)
        activateModalDialogAndClearText;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(), false, Address::SHC_3BB0A8C1_0x00491730,
            &MenuTextInputState::clearModalDialog2to6)
        clearModalDialog2to6;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(), false, Address::SHC_3BB0A8C1_0x00491750,
            &MenuTextInputState::clearAnyOtherModalDialogs)
        clearAnyOtherModalDialogs;

        MACRO_FUNCTION_RESOLVER(
            void (MenuTextInputState::*)(), false, Address::SHC_3BB0A8C1_0x004917C0, &MenuTextInputState::meth_0x4917c0)
        meth_0x4917c0;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(), false, Address::SHC_3BB0A8C1_0x00493900,
            &MenuTextInputState::popModalDialog)
        popModalDialog;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(int), false, Address::SHC_3BB0A8C1_0x00493980,
            &MenuTextInputState::activateLoadOrSaveMapUI)
        activateLoadOrSaveMapUI;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(MenuModalTypeInt), false, Address::SHC_3BB0A8C1_0x00493AC0,
            &MenuTextInputState::loadOrSaveMap)
        loadOrSaveMap;

        MACRO_FUNCTION_RESOLVER(void (MenuTextInputState::*)(int), false, Address::SHC_3BB0A8C1_0x004968A0,
            &MenuTextInputState::loadOrSaveGame)
        loadOrSaveGame;

    } // namespace MenuTextInputState_Func
} // namespace UI
} // namespace OpenSHC
