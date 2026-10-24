#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005237F0
        void TribesState::aiAssignNewUnitToTribe(int playerID, int unitType, int unitID)
        {
            int _index = 0;
            if (unitType == 0x1e) {
                /*
                  is engineer
                 */
                _index = 1;
            } else if (unitType == 5) {
                /*
                  is tunneler
                 */
                _index = 2;
            } else if (unitType == 0x1d) {
                /*
                  is ladderman
                 */
                _index = 3;
            } else if (unitType == 0x25) {
                /*
                  is monk
                 */
                int _monkTribe = DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk;
                if (!_monkTribe || this->tribes[_monkTribe].tribeState == 0
                    || this->tribes[_monkTribe].uid
                        != DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk) {
                    _monkTribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeIDUnk = _monkTribe;
                    DAT_GameState::instance.playerDataArray[playerID].monkTribeUIDUnk
                        = this->tribes[_monkTribe].uid;
                }
                /*
                  The monk arm is a block of its own in the disassembly, from 0x5238ac to
                  its own `ret 0xc` at 0x52390f: it never reaches the shared path below, so
                  a monk is added to one tribe rather than two.
                 */
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _monkTribe);
                return;
            }
            short* psVar1 = DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeIDs + _index;
            int _tribe = (int)*psVar1;
            if (!_tribe || this->tribes[_tribe].tribeState == 0
                || this->tribes[_tribe].uid
                    != DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index]) {
                _tribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(playerID, 0);
                *psVar1 = (short)_tribe;
                DAT_GameState::instance.playerDataArray[playerID].freshUnitTribeUIDs[_index]
                    = this->tribes[_tribe].uid;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _tribe);
        }

    }
}
}
