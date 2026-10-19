#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523190
        dword TribesState::createTribeWithSpawnedUnit(
            short someIndex, undefined4 tribeType, int x, int y, int playerID, UnitType unitType, int count)
        {
            if ((x <= 0) && (y <= 0)) {
                return (dword)(0);
            }
            dword _tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if ((int)_tribeID <= 0) {
                return (dword)(0);
            }
            this->tribes[_tribeID].tribeType = (AITribeTypeShort)tribeType;
            this->tribes[_tribeID].someIndex = someIndex;
            this->tribes[_tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.inv_count;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                DAT_PathFindingState::ptr)(x, y, -1, -1, 2000, 0);
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::spawnUnitAndAddToTribe,
                DAT_PathFindingState::ptr)(playerID, playerID, count, unitType, (undefined4)((int)(_tribeID)));
            this->tribes[_tribeID].pendingScatterMove = 1;
            return (dword)(_tribeID);
        }

    }
}
}
