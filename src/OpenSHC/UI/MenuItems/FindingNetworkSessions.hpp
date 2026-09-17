/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/FindingNetworkSessions.hpp'
*/

#pragma once

#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParameters.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace FindingNetworkSessions {

            using OpenSHC::UI::Multiplayer::FindingNetworkSessions_ButtonParameters;

            void __cdecl MenuItemActionHandler_FindingNetworkSessions_Scrollbar(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_FindingNetworkSessions_TableRows(int param_1, ...);

            void __cdecl MenuItemRenderFunction_FindingNetworkSessions_TableRows(int param_1, ...);

            void __cdecl MenuItemActionHandler_FindingNetworkSessions_EnumerateDPlaySessions(int param_1, ...);

            void __cdecl MenuItemActionHandler_FindingNetworkSessions_Buttons(
                FindingNetworkSessions_ButtonParameters param_1, ...);

        } // namespace FindingNetworkSessions
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
