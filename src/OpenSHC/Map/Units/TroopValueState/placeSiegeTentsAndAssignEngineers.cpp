#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B710
        void TroopValueState::placeSiegeTentsAndAssignEngineers(int param_1, int param_2)
        {
            int _engineerCount;
            int _tribeID2;
            int _index;
            int _subCount;
            int _totalEngineers;
            int _extraCount;
            Unit* _ptrPlayerID;
            int _unitID;
            int _playerID;
            int _tribeID;
            int _unitCount;
            _playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            if (!_playerID) {
                _playerID = 2;
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                _playerID = 2;
            }
            int _queueSize = 0;
            byte(*_pScoreRow)[10] = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore + param_1;
            _totalEngineers = 0;
            DAT_TroopValueState::instance.attackInfo.createTribeAmount = 0;
            _index = 0;
            do {
                int const _count = (int)(char)(*_pScoreRow)[0];
                MappersEnum _buildingType
                    = *(MappersEnum*)((int)DAT_AttackInfoDefinedData::instance.field5_0xc8 + _index);
                _engineerCount = *(int*)((int)DAT_AttackInfoDefinedData::instance.field39_0x9ec + _index);
                _subCount = 0;
                if (0 < _count) {
                    do {
                        DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[_queueSize].engineerBuildingType
                            = _buildingType;
                        DAT_TroopValueState::instance.attackInfo
                            .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                            .engineerCount = _engineerCount;
                        _queueSize = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                        _totalEngineers = _totalEngineers + _engineerCount;
                        DAT_TroopValueState::instance.attackInfo.createTribeAmount = _queueSize;
                        if (0xfa <= _queueSize) {
                            break;
                        }
                        _subCount = _subCount + 1;
                    } while (_subCount < _count);
                }
                _pScoreRow = (byte(*)[10])(*_pScoreRow + 1);
                _index = _index + 4;
            } while (_index <= 16);
            _subCount = DAT_AttackInfoDefinedData::instance.field52_0xa0c;
            _engineerCount = DAT_AttackInfoDefinedData::instance.field9_0xe8;
            _extraCount = (int)(char)DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore[param_1][8];
            _index = 0;
            if (0 < _extraCount) {
                do {
                    if (0xfa <= _queueSize) {
                        break;
                    }
                    DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[_queueSize].engineerBuildingType
                        = (Commands::MappersEnum)(_engineerCount);
                    DAT_TroopValueState::instance.attackInfo
                        .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerCount = _subCount;
                    _queueSize = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                    _index = _index + 1;
                    _totalEngineers = _totalEngineers + _subCount;
                    DAT_TroopValueState::instance.attackInfo.createTribeAmount = _queueSize;
                } while (_index < _extraCount);
            }
            _queueSize = 0;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (_tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState
                    && DAT_TribesState::instance.tribes[_tribeID].owner == _playerID
                    && DAT_TribesState::instance.tribes[_tribeID].attackWave == param_1
                    && DAT_TribesState::instance.tribes[_tribeID].tribeType == AI::Tribes::AITT_ENGINEERS) {
                    DAT_TroopValueState::instance.attackInfo.tribeIDArray[_queueSize] = _tribeID;
                    _queueSize = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize + 1;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = _queueSize;
                }
            }
            if (_queueSize) {
                for (_index = 0; _index < _queueSize; _index++) {
                    _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[_index];
                    short _tribeSize = DAT_TribesState::instance.tribes[_tribeID].size;
                    for (; (_tribeSize
                             && (_queueSize = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize,
                                0 < _totalEngineers));
                        _totalEngineers = _totalEngineers + -1) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(
                            _tribeID);
                        _tribeSize = DAT_TribesState::instance.tribes[_tribeID].size;
                    }
                }
                _unitID = 0;
                param_1 = 0;
                while (param_1 < DAT_TroopValueState::instance.attackInfo.createTribeAmount) {
                    _unitCount = DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerCount;
                    _tribeID2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.tribes[_tribeID].owner, 0);
                    _totalEngineers = DAT_UnitsState::instance.maxUnitCount;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeType = 11;
                    DAT_TribesState::instance.tribes[_tribeID2].tribeBehaviorType = 1040;
                    DAT_TribesState::instance.tribes[_tribeID2].attackWave
                        = DAT_TribesState::instance.tribes[_tribeID].attackWave;
                    DAT_TribesState::instance.tribes[_tribeID2].attackInfo_someCounter1
                        = DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1;
                    if (_totalEngineers <= _unitID) {
                        return;
                    }
                    _ptrPlayerID = &DAT_UnitsState::instance.units[_unitID];
                    do {
                        if (_ptrPlayerID->logicalState == Map::Units::ULS_NORMAL && _ptrPlayerID->owner == _playerID
                            && !_ptrPlayerID->dying && _ptrPlayerID->unitType == Map::Units::UT_E_ENGINEER
                            && !_ptrPlayerID->tribeID) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                                _unitID, _tribeID2);
                            _unitCount = _unitCount + -1;
                            if (_unitCount < 1) {
                                break;
                            }
                        }
                        _unitID = _unitID + 1;
                        _ptrPlayerID = _ptrPlayerID + 1;
                        if (DAT_UnitsState::instance.maxUnitCount <= _unitID) {
                            return;
                        }
                    } while (true);
                    _unitID = _unitID + 1;
                    if (DAT_UnitsState::instance.maxUnitCount <= _unitID) {
                        return;
                    }
                    if (!param_2) {
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::
                                              placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                            this)(_tribeID2,
                            DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerBuildingType,
                            0, Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED);
                    } else {
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentAtAttackAngle, this)(
                            _tribeID2,
                            DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[param_1].engineerBuildingType);
                    }
                    param_1 = param_1 + 1;
                }
            }
        }

    }
}
}
