/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/FindingNetworkSessions.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/MenuItems/FindingNetworkSessions.hpp"
#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParameters.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions_Func {

            using OpenSHC::UI::Multiplayer::FindingNetworkSessions_ButtonParameters;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0047D330,
                &OpenSHC::UI::MenuItems::FindingNetworkSessions::MenuItemActionHandler_FindingNetworkSessions_Scrollbar)
            MenuItemActionHandler_FindingNetworkSessions_Scrollbar;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047D3F0,
                &OpenSHC::UI::MenuItems::FindingNetworkSessions::MenuItemActionHandler_FindingNetworkSessions_TableRows)
            MenuItemActionHandler_FindingNetworkSessions_TableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047D410,
                &OpenSHC::UI::MenuItems::FindingNetworkSessions::
                    MenuItemRenderFunction_FindingNetworkSessions_TableRows)
            MenuItemRenderFunction_FindingNetworkSessions_TableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0048BF70,
                &OpenSHC::UI::MenuItems::FindingNetworkSessions::
                    MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions)
            MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(FindingNetworkSessions_ButtonParameters param_1, ...), false,
                Address::SHC_3BB0A8C1_0x00490D90,
                &OpenSHC::UI::MenuItems::FindingNetworkSessions::MenuItemActionHandler_FindingNetworkSessions_Buttons)
            MenuItemActionHandler_FindingNetworkSessions_Buttons;

        } // namespace FindingNetworkSessions_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
