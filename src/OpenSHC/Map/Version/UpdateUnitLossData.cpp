#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_UnitValueLossesPerEnemyPlayer.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044AA80
    void Version::UpdateUnitLossData(int lossValue, int playerID)
    {
        if (lossValue < 0) {
            DAT_UnitValueLossesPerEnemyPlayer::instance[playerID] -= lossValue;
        }
    }

}
}
