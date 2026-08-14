/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/GreatestLord.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace GreatestLord {

        int __cdecl GetPlayerAtRank(int rankingPosition);

        int __stdcall IfAiGreatestLordGetAiType();

        int __stdcall GetLowestRankedAlivePlayer();

        int __cdecl ComputeSkMasterScore(int playerID);

    } // namespace GreatestLord
} // namespace UI
} // namespace OpenSHC
