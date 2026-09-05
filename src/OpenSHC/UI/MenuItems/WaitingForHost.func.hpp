/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/WaitingForHost.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/WaitingForHost.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace WaitingForHost_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047E3E0,
                &OpenSHC::UI::MenuItems::WaitingForHost::MenuItemActionHandler_WaitingForHost_Button)
            MenuItemActionHandler_WaitingForHost_Button;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047E420,
                &OpenSHC::UI::MenuItems::WaitingForHost::MenuItemRenderFunction_WaitingForHost_Button)
            MenuItemRenderFunction_WaitingForHost_Button;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004914D0,
                &OpenSHC::UI::MenuItems::WaitingForHost::MenuItemActionHandler_WaitingForHost_ConnectToLobby)
            MenuItemActionHandler_WaitingForHost_ConnectToLobby;

        } // namespace WaitingForHost_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
