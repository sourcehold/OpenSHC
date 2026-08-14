/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Actions.func.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/UI/Actions.hpp"
namespace OpenSHC {
namespace UI {
    namespace Actions_Func {

        using OpenSHC::Game::Resources::ResourceType;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C620,
            &OpenSHC::UI::Actions::LaunchSinglePlayerGameUnk)
        LaunchSinglePlayerGameUnk;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004381D0, &OpenSHC::UI::Actions::PlaceUnit)
        PlaceUnit;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int whichCastle), false, Address::SHC_3BB0A8C1_0x00441270,
            &OpenSHC::UI::Actions::LaunchSkirmishGame)
        LaunchSkirmishGame;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int state, ResourceType resource), false,
            Address::SHC_3BB0A8C1_0x00465DB0, &OpenSHC::UI::Actions::SetStorageMarketFailState)
        SetStorageMarketFailState;

    } // namespace Actions_Func
} // namespace UI
} // namespace OpenSHC
