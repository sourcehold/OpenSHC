/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish.func.hpp'
*/

#pragma once

#include "OpenSHC/Game/Skirmish.hpp"
namespace OpenSHC {
namespace Game {
    namespace Skirmish_Func {

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AC570, &OpenSHC::Game::Skirmish::RecalculateAllies)
        RecalculateAllies;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int index), false, Address::SHC_3BB0A8C1_0x004D5370,
            &OpenSHC::Game::Skirmish::SkirmishLeaderboard_DeleteEntry)
        SkirmishLeaderboard_DeleteEntry;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int reverseOrder), false, Address::SHC_3BB0A8C1_0x004D9290,
            &OpenSHC::Game::Skirmish::Skirmish_SortAIOpponentOrder)
        Skirmish_SortAIOpponentOrder;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D9400,
            &OpenSHC::Game::Skirmish::Skirmish_PrepareLeaderboardView)
        Skirmish_PrepareLeaderboardView;

    } // namespace Skirmish_Func
} // namespace Game
} // namespace OpenSHC
