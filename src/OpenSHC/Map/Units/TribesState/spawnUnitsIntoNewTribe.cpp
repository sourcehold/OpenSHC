#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523030
        dword TribesState::spawnUnitsIntoNewTribe(undefined4 counter, int tribeType, int x, int y, int playerID,
            UnitType unitType, UnitType unitType2, int unitType1Count, int unitType2Count)
        {
            int microYPosition;
            dword _tribeID;
            int _unitID;
            uint _unitID2;
            if ((x <= 0) && (y <= 0)) {
                return (dword)(0);
            }
            _tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
            if (0 < (int)_tribeID) {
                this->tribes[_tribeID].tribeType = (AITribeTypeShort)tribeType;
                this->tribes[_tribeID].someIndex = (short)counter;
                this->tribes[_tribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.inv_count;
                if (0 < unitType1Count) {
                    tribeType = unitType1Count;
                    do {
                        _unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            playerID, playerID, x * 8, y * 8, 8, unitType);
                        if (_unitID) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(
                                _unitID, (int)(_tribeID));
                            DAT_UnitsState::instance.units[_unitID].aiUnitBehaviourType = 0;
                        }
                        tribeType = tribeType + -1;
                    } while (tribeType);
                }
                if (0 < unitType2Count) {
                    microYPosition = y * 8;
                    y = unitType2Count;
                    do {
                        _unitID2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            playerID, playerID, x * 8, microYPosition, 8, unitType2);
                        if (_unitID2) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(
                                _unitID2, (int)(_tribeID));
                            DAT_UnitsState::instance.units[_unitID2].aiUnitBehaviourType = 0;
                        }
                        y = y + -1;
                    } while (y);
                }
                this->tribes[_tribeID].pendingScatterMove = 1;
                return (dword)(_tribeID);
            }
            return (dword)(0);
        }

    }
}
}
