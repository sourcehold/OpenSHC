/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/ChooseNetworkServiceProvider.hpp'
*/

#pragma once

#include "OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActions.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace ChooseNetworkServiceProvider {

            using OpenSHC::UI::ChooseNetworkServiceProvider::ChooseNetworkServiceProviderButtonActions;

            void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderScrollbarUnk(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_ProviderTableRows(int param_1, ...);

            void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels(int param_1, ...);

            void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay(int param_1, ...);

            void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ModemScrollbarUnk(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ModemTableRows(int param_1, ...);

            void __cdecl MenuItemRenderFunction_ChooseNetworkServiceProvider_ModemTableRows(int param_1, ...);

            void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows(int param_1, ...);

            void __cdecl MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons(
                ChooseNetworkServiceProviderButtonActions param_1, ...);

        } // namespace ChooseNetworkServiceProvider
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
