/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Actions.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
namespace OpenSHC {
namespace UI {
    namespace Actions {

        using OpenSHC::Game::Resources::ResourceType;

        void __cdecl LaunchSinglePlayerGameUnk(int param_1);

        void __stdcall PlaceUnit();

        void __cdecl LaunchSkirmishGame(int whichCastle);

        void __cdecl SetStorageMarketFailState(int state, ResourceType resource);

    } // namespace Actions
} // namespace UI
} // namespace OpenSHC
