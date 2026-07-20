#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCBF0
    int AICState::getDefensiveTribeForUnit(int playerID, int unitID)
    {
        int _index = 0;
        int _unitType = (int)(short)DAT_UnitsState::instance.units[unitID].unitType;
        int _unitType2;
        do {
            if ((_unitType == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index]) ||
                (_unitType2 = (int)(short)DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto,
                 _unitType2 == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index])) break;
            if ((_unitType == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 1]) ||
                (_unitType2 == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 1])) {
                _index = _index + 1;
                break;
            }
            if ((_unitType == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 2]) ||
                (_unitType2 == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 2])) {
                _index = _index + 2;
                break;
            }
            if ((_unitType == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 3]) ||
                (_unitType2 == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 3])) {
                _index = _index + 3;
                break;
            }
            if ((_unitType == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 4]) ||
                (_unitType2 == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[_index + 4])) {
                _index = _index + 4;
                break;
            }
            _index = _index + 5;
        } while (_index < 0x14);
        int _tribeIndex;
        if (_index < 1) {
            _tribeIndex = 0xb4;
        }
        else if (_index < 2) {
            _tribeIndex = 0xb5;
        }
        else if (_index < 7) {
            _tribeIndex = 0xb6;
        }
        else if (_index < 0xc) {
            _tribeIndex = 0xb7;
        }
        else if (_index < 0xf) {
            _tribeIndex = 0xb8;
        }
        else {
            if (19 < _index) {
                return 0;
            }
            _tribeIndex = 0xb9;
        }
        short* _pTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + _tribeIndex;
        int _tribeID = (int)*_pTribeID;
        if ((_tribeID == 0) ||
            (DAT_TribesState::instance.tribes[_tribeID].uid != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_tribeIndex])) {
            _tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            int _tribeUID = DAT_TribesState::instance.tribes[_tribeID].uid;
            *_pTribeID = (short)_tribeID;
            DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_tribeIndex] = _tribeUID;
        }
        return _tribeID;
    }
}
}
