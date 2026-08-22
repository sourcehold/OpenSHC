#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCAF0
    int AICState ::getSmallestPatrolTribe(int playerID, int tribeCount)
    {
        int _selectedTribeID = 0;
        int _tribeNumber = 0;
        int _selectedTribeNumber = 0;
        short _lowestTribeUnitCount = 1000;

        if (0 < tribeCount) {
            short* _pTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xaa;
            do {
                int _tribeID = (int)*_pTribeID;
                if ((_tribeID == 0)
                    || (DAT_TribesState::instance.tribes[_tribeID].uid
                        != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_tribeNumber + 0xaa])) {
                    _selectedTribeID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                    _selectedTribeNumber = _tribeNumber;
                    DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[_selectedTribeNumber + 0xaa]
                        = (short)_selectedTribeID;
                    DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_selectedTribeNumber + 0xaa]
                        = DAT_TribesState::instance.tribes[_selectedTribeID].uid;
                    return _selectedTribeID;
                }
                short _tribeSize = DAT_TribesState::instance.tribes[_tribeID].size;
                if (_tribeSize < _lowestTribeUnitCount) {
                    _selectedTribeID = _tribeID;
                    _selectedTribeNumber = _tribeNumber;
                    _lowestTribeUnitCount = _tribeSize;
                }
                _tribeNumber = _tribeNumber + 1;
                _pTribeID = _pTribeID + 1;
            } while (_tribeNumber < tribeCount);

            if (_selectedTribeID != 0) {
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[_selectedTribeNumber + 0xaa]
                    = (short)_selectedTribeID;
                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_selectedTribeNumber + 0xaa]
                    = DAT_TribesState::instance.tribes[_selectedTribeID].uid;
                return _selectedTribeID;
            }
        }
        return 0;
    }
}
}
