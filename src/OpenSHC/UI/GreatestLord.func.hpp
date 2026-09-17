/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/GreatestLord.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/GreatestLord.hpp"
namespace OpenSHC {
namespace UI {
    namespace GreatestLord_Func {

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int rankingPosition), false, Address::SHC_3BB0A8C1_0x0044B760,
            &OpenSHC::UI::GreatestLord::GetPlayerAtRank)
        GetPlayerAtRank;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0044B7D0,
            &OpenSHC::UI::GreatestLord::IfAiGreatestLordGetAiType)
        IfAiGreatestLordGetAiType;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0044B800,
            &OpenSHC::UI::GreatestLord::GetLowestRankedAlivePlayer)
        GetLowestRankedAlivePlayer;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x004D5780,
            &OpenSHC::UI::GreatestLord::ComputeSkMasterScore)
        ComputeSkMasterScore;

    } // namespace GreatestLord_Func
} // namespace UI
} // namespace OpenSHC
