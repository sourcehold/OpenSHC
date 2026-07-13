/**
  path: 'OpenSHC/UI/MenuHandlerState.func.hpp'
*/

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/MenuHandlerState.hpp"
#include "OpenSHC/UI/MenuIDMenuElementAddressPair.hpp"
#include "OpenSHC/UI/UC.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuHandlerState_Func {

        using OpenSHC::UI::MenuIDMenuElementAddressPair;
        using OpenSHC::UI::UC;
        using OpenSHC::UI::Enums::MenuViewTypeInt;

        MACRO_FUNCTION_RESOLVER(void (MenuHandlerState::*)(dword, dword), false, Address::SHC_3BB0A8C1_0x004F4C60,
            &MenuHandlerState::setupBuildMenuState)
        setupBuildMenuState;

        MACRO_FUNCTION_RESOLVER(void (MenuHandlerState::*)(int), false, Address::SHC_3BB0A8C1_0x004F4C80,
            &MenuHandlerState::startBuildMenuTransition)
        startBuildMenuTransition;

        MACRO_FUNCTION_RESOLVER(void (MenuHandlerState::*)(), false, Address::SHC_3BB0A8C1_0x004F4CD0,
            &MenuHandlerState::computeBuildMenuTransitionShift)
        computeBuildMenuTransitionShift;

        MACRO_FUNCTION_RESOLVER(void (MenuHandlerState::*)(MenuIDMenuElementAddressPair*, UC*, char*), false,
            Address::SHC_3BB0A8C1_0x004F6A20, &MenuHandlerState::initializeUI)
        initializeUI;

        MACRO_FUNCTION_RESOLVER(void (MenuHandlerState::*)(MenuViewTypeInt), false, Address::SHC_3BB0A8C1_0x004F6A80,
            &MenuHandlerState::setupMenuForRendering)
        setupMenuForRendering;

    } // namespace MenuHandlerState_Func
} // namespace UI
} // namespace OpenSHC
