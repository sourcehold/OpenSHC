#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005237F0
        void TribesState::aiAssignNewUnitToTribe(int playerID, int unitType, int unitID)
        {
            short* psVar1;
            int _tribe;
            int _index;
            _index = 0;
            /*
              is engineer
             */
            if (unitType == 0x1e) {
                _index = 1;
            } else {
                /*
                  is tunneler
                 */
                if (unitType == 5) {
                    _index = 2;
                } else {
                    /*
                      is ladderman
                     */
                    if (unitType == 0x1d) {
                        _index = 3;
                    } else {
                        /*
                          is monk
                         */
                        if (unitType == 0x25) {
                            _tribe = DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk;
                            if (!_tribe || this->tribes[_tribe].tribeState == 0
                                || this->tribes[_tribe].uid
                                    != DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk) {
                                _tribe
                                    = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                                DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk = _tribe;
                                DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk
                                    = this->tribes[_tribe].uid;
                            }
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _tribe);
                        }
                    }
                }
            }
            psVar1 = DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeIDs + _index;
            _tribe = (int)*psVar1;
            if (!_tribe || this->tribes[_tribe].tribeState == 0
                || this->tribes[_tribe].uid
                    != DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index]) {
                _tribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                *psVar1 = (short)_tribe;
                DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index] = this->tribes[_tribe].uid;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _tribe);
        }

    }
}
}
