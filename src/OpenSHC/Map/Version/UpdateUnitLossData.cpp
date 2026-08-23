#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_UnitValueLossesPerEnemyPlayer.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x0044AA80
    void __cdecl Version::UpdateUnitLossData(int lossValue, int playerID)

    {
        if (lossValue < 0) {
            DAT_UnitValueLossesPerEnemyPlayer::instance[playerID]
                = DAT_UnitValueLossesPerEnemyPlayer::instance[playerID] - lossValue;
        }
        return;
    }

}
}
