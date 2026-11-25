#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005237F0
        void TribesState::aiAssignNewUnitToTribe(int playerID, int unitType, int unitID)
        {
            int _index = 0;
            if (unitType == Map::Units::UT_E_ENGINEER) {
                _index = 1;
            } else if (unitType == Map::Units::UT_TUNNELER) {
                _index = 2;
            } else if (unitType == Map::Units::UT_E_LADDER) {
                _index = 3;
            } else if (unitType == Map::Units::UT_E_MONK) {
                int _monkTribe = DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk;
                if (!_monkTribe || this->tribes[_monkTribe].tribeState == 0
                    || this->tribes[_monkTribe].uid
                        != DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk) {
                    _monkTribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk = _monkTribe;
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk = this->tribes[_monkTribe].uid;
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _monkTribe);
                return;
            }
            int _tribe = DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeIDs[_index];
            if (!_tribe || this->tribes[_tribe].tribeState == 0
                || this->tribes[_tribe].uid
                    != DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index]) {
                _tribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeIDs[_index] = _tribe;
                DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index] = this->tribes[_tribe].uid;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _tribe);
        }

    }
}
}
