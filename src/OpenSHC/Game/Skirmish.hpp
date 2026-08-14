/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __stdcall SetupSkirmishBalanceAndOrIntensity();

        void __cdecl RecalculateAllies();

        void __cdecl SetupSkirmishMode(int skirmishTrailMission);

        int __stdcall StoreLocalTime();

        BOOLEnum __cdecl StoreCurrentGameIntoTemporarySKMasterEntry(int score);

        void __cdecl StoreGameIntoSKMasters(int score);

        void __cdecl SkirmishLeaderboard_DeleteEntry(int index);

        void __cdecl Skirmish_SortAIOpponentOrder(int reverseOrder);

        void __cdecl Skirmish_PrepareLeaderboardView();

    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
