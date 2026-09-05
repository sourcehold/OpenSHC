/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/ChooseNetworkServiceProvider.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActions.hpp"
#include "OpenSHC/UI/MenuItems/ChooseNetworkServiceProvider.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace ChooseNetworkServiceProvider_Func {

            using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActions;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0047CA80,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk)
            MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047CB30,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows)
            MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047CEE0,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels)
            MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047CF50,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay)
            MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay;

            MACRO_FUNCTION_RESOLVER(
                void(__cdecl*)(int param_1, int param_2, int* minValue, int* maxValue, int* currentValue), false,
                Address::SHC_3BB0A8C1_0x0047D070,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk)
            MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047D0E0,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows)
            MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x0047D100,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows)
            MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00487200,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows)
            MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(ChooseNetworkServiceProviderButtonActions param_1, ...), false,
                Address::SHC_3BB0A8C1_0x004909E0,
                &OpenSHC::UI::MenuItems::ChooseNetworkServiceProvider::
                    MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons)
            MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons;

        } // namespace ChooseNetworkServiceProvider_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
