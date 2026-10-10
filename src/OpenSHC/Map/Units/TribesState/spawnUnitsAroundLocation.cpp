#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523240
        dword TribesState::spawnUnitsAroundLocation(
            undefined4 param_1, int aroundX, int aroundY, int playerID, UnitType unitType, int count)
        {
            dword _tribeID;
            if ((aroundX <= 0) && (aroundY <= 0)) {
                return (dword)(0);
            }
            _tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if ((int)_tribeID <= 0) {
                return (dword)(0);
            }
            this->tribes[_tribeID].someIndex = 0;
            this->tribes[_tribeID].attackWave = 0;
            this->tribes[_tribeID].tribeType = (AITribeTypeShort)param_1;
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                DAT_PathFindingState::ptr)(aroundX, aroundY, -1, -1, 2000, 0);
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::spawnUnitAndAddToTribe,
                DAT_PathFindingState::ptr)(playerID, playerID, count, unitType, (undefined4)((int)(_tribeID)));
            this->tribes[_tribeID].pendingScatterMove = 1;
            return (dword)(_tribeID);
        }

    }
}
}
