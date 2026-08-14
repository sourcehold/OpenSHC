/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish.func.hpp'
*/

#pragma once

#include "OpenSHC/Game/Skirmish.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {
    namespace Skirmish_Func {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00429710,
            &OpenSHC::Game::Skirmish::SetupSkirmishBalanceAndOrIntensity)
        SetupSkirmishBalanceAndOrIntensity;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004AC570, &OpenSHC::Game::Skirmish::RecalculateAllies)
        RecalculateAllies;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int skirmishTrailMission), false, Address::SHC_3BB0A8C1_0x004C68D0,
            &OpenSHC::Game::Skirmish::SetupSkirmishMode)
        SetupSkirmishMode;

        MACRO_FUNCTION_RESOLVER(
            int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004C6CD0, &OpenSHC::Game::Skirmish::StoreLocalTime)
        StoreLocalTime;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int score), false, Address::SHC_3BB0A8C1_0x004D1700,
            &OpenSHC::Game::Skirmish::StoreCurrentGameIntoTemporarySKMasterEntry)
        StoreCurrentGameIntoTemporarySKMasterEntry;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int score), false, Address::SHC_3BB0A8C1_0x004D52A0,
            &OpenSHC::Game::Skirmish::StoreGameIntoSKMasters)
        StoreGameIntoSKMasters;

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
