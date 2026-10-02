#include "../GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D5780
    int GreatestLord::ComputeSkMasterScore(int playerID)
    {
        int iVar1;
        int iVar2;
        int iVar3;
        iVar3 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsDestroyedWeighted[playerID] * 100
            + DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] / 10
            + DAT_GameSynchronyState::instance.finalResults.finalTroopsKilledWeighted[playerID];
        iVar1 = (char)DAT_GameSynchronyState::instance.finalResults.finalKilledLords[playerID] * iVar3;
        iVar2 = ((DAT_GameSynchronyState::instance.finalResults.yearEnd
                     - DAT_GameSynchronyState::instance.finalResults.yearStart)
                        * 0xc
                    - DAT_GameSynchronyState::instance.finalResults.monthStart)
            + DAT_GameSynchronyState::instance.finalResults.monthEnd;
        if (iVar2 < 1) {
            iVar2 = 1;
        }
        return ((iVar3 + ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2)) * 200) / (iVar2 + 200);
    }

}
}
