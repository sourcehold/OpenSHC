/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/Chat.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/Chat.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Chat_Func {

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047FD50,
                &OpenSHC::UI::MenuItems::Chat::MenuItemRenderFunction_Chat_MostButtons)
            MenuItemRenderFunction_Chat_MostButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047FFA0,
                &OpenSHC::UI::MenuItems::Chat::MenuItemActionHandler_Chat_SendMessageToPlayer)
            MenuItemActionHandler_Chat_SendMessageToPlayer;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047FFE0,
                &OpenSHC::UI::MenuItems::Chat::MenuItemRenderFunction_Chat_TauntButtons)
            MenuItemRenderFunction_Chat_TauntButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0048F590,
                &OpenSHC::UI::MenuItems::Chat::MenuItemActionHandler_Chat_MostButtons)
            MenuItemActionHandler_Chat_MostButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0048F850,
                &OpenSHC::UI::MenuItems::Chat::MenuItemActionHandler_Chat_TauntButtons)
            MenuItemActionHandler_Chat_TauntButtons;

        } // namespace Chat_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
