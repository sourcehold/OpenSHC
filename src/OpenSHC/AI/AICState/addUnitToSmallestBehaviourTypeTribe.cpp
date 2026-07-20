#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCD20
    int AICState::addUnitToSmallestBehaviourTypeTribe(
        undefined4 playerID, undefined4 param_2, undefined4 aiUnitBehaviourType)
    {
        int _playerID = (int)playerID;
        int AVar1 = DAT_GameState::instance.playerDataArray[_playerID].aiType;
        if (AVar1 == AITA_NULL) {
            return 0;
        }
        int _tribeTypeOffset
            = DAT_SkirmishDefinedData::instance.DAT_AIUnitBehaviourTypeMapping[(int)aiUnitBehaviourType + -10];
        int _smallestTribe = 0;
        int _smallestTribeOffset = 0;
        short _smallestTribeSize = 1000;
        dword _groupsCount;
        switch (_tribeTypeOffset) {
        case 0xf:
            _groupsCount = this->aics[AVar1 - 1].AttUnitPatrolGroupsCount;
            break;
        default:
            goto switchD_004ccd78_caseD_10;
        case 0xba:
            _groupsCount = this->aics[AVar1 - 1].AttUnitBackupGroupsCount;
            break;
        case 0xbe:
            _groupsCount = this->aics[AVar1 - 1].AttUnitSiegeDefGroupsCount;
            break;
        case 0xc0:
            _groupsCount = this->aics[AVar1 - 1].AttMainGroupsCount;
        }
        int _selectedTribe;
        int _selectedSlot;
        if (((int)_groupsCount < 1) || (_groupsCount == 1)) {
        switchD_004ccd78_caseD_10:
            int _tribeID_groupsCount1
                = (int)DAT_GameState::instance.playerDataArray[_playerID].aiTribeIDs[_tribeTypeOffset];
            if ((_tribeID_groupsCount1 != 0)
                && (DAT_TribesState::instance.tribes[_tribeID_groupsCount1].uid
                    == DAT_GameState::instance.playerDataArray[_playerID].aiTribeUIDs[_tribeTypeOffset])) {
                return _tribeID_groupsCount1;
            }
            _selectedTribe = MACRO_CALL_MEMBER(
                Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(_playerID);
            _selectedSlot = _tribeTypeOffset;
        } else {
            int _maxOffset = _groupsCount + _tribeTypeOffset;
            _selectedTribe = 0;
            _selectedSlot = 0;
            short* _pTribeIDs = DAT_GameState::instance.playerDataArray[_playerID].aiTribeIDs + _tribeTypeOffset;
            if (_tribeTypeOffset < _maxOffset) {
                do {
                    int _tribeID_2 = (int)*_pTribeIDs;
                    if ((_tribeID_2 == 0)
                        || (DAT_TribesState::instance.tribes[_tribeID_2].uid
                            != DAT_GameState::instance.playerDataArray[_playerID].aiTribeUIDs[_tribeTypeOffset])) {
                        _selectedTribe = MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(_playerID);
                        _selectedSlot = _tribeTypeOffset;
                        break;
                    }
                    short _tribeSize = DAT_TribesState::instance.tribes[_tribeID_2].size;
                    if (_tribeSize < _smallestTribeSize) {
                        _smallestTribeOffset = _tribeTypeOffset;
                        _smallestTribe = _tribeID_2;
                        _smallestTribeSize = _tribeSize;
                    }
                    _pTribeIDs = _pTribeIDs + 1;
                    _tribeTypeOffset = _tribeTypeOffset + 1;
                    _selectedTribe = _smallestTribe;
                    _selectedSlot = _smallestTribeOffset;
                } while (_tribeTypeOffset < _maxOffset);
            }
        }
        if (0 < _selectedTribe) {
            DAT_GameState::instance.playerDataArray[_playerID].aiTribeIDs[_selectedSlot] = (short)_selectedTribe;
            DAT_GameState::instance.playerDataArray[_playerID].aiTribeUIDs[_selectedSlot]
                = DAT_TribesState::instance.tribes[_selectedTribe].uid;
            return _selectedTribe;
        }
        return 0;
    }
}
}
