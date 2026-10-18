#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

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
        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BA30
        void TroopValueState::placeTunnelForEveryTunneler(int attackWave)
        {
            int _tribeID;
            int _playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[attackWave];
            int _nTunnelers = 0;
            int _nTunnels = 0;
            if (!_playerID) {
                _playerID = 2;
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                _playerID = 2;
            }
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                Unit* _pUnit = &DAT_UnitsState::instance.units[1];
                int _remainingUnits = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && _pUnit->owner == _playerID && !_pUnit->dying
                        && _pUnit->unitType == Map::Units::UT_TUNNELER) {
                        _nTunnelers = _nTunnelers + 1;
                    }
                    _pUnit = _pUnit + 1;
                    _remainingUnits = _remainingUnits + -1;
                } while (_remainingUnits);
                _nTunnels = _nTunnelers;
            }
            int _tribeArraySize = 0;
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (_tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState
                    && DAT_TribesState::instance.tribes[_tribeID].owner == _playerID
                    && DAT_TribesState::instance.tribes[_tribeID].attackWave == attackWave
                    && DAT_TribesState::instance.tribes[_tribeID].tribeType == AI::Tribes::AITT_TUNNELERS) {
                    DAT_TroopValueState::instance.attackInfo.tribeIDArray[_tribeArraySize] = _tribeID;
                    _tribeArraySize = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize + 1;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = _tribeArraySize;
                }
            }
            if (_tribeArraySize) {
                int _index = 0;
                if (0 < _tribeArraySize) {
                    do {
                        _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[_index];
                        short _tribeSize = DAT_TribesState::instance.tribes[_tribeID].size;
                        while (_tribeSize) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(
                                _tribeID);
                            _tribeSize = DAT_TribesState::instance.tribes[_tribeID].size;
                        }
                        _index = _index + 1;
                        _tribeArraySize = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize;
                    } while (_index < _tribeArraySize);
                }
                uint unitID = 0;
                attackWave = 0;
                if (0 < _nTunnels) {
                    do {
                        int _tribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                            _playerID, 0);
                        DAT_TribesState::instance.tribes[_tribe].tribeType = AI::Tribes::AITT_TUNNELERS;
                        DAT_TribesState::instance.tribes[_tribe].tribeBehaviorType = Map::Units::STBT_0x415;
                        DAT_TribesState::instance.tribes[_tribe].attackWave
                            = DAT_TribesState::instance.tribes[_tribeID].attackWave;
                        uint const _maxUnitCount = DAT_UnitsState::instance.maxUnitCount;
                        DAT_TribesState::instance.tribes[_tribe].attackInfo_someCounter1
                            = DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1;
                        if ((int)unitID >= (int)_maxUnitCount) {
                            return;
                        }
                        Unit* _pCandidateUnit = &DAT_UnitsState::instance.units[unitID];
                        while (_pCandidateUnit->logicalState != Map::Units::ULS_NORMAL
                            || _pCandidateUnit->owner != _playerID || _pCandidateUnit->dying
                            || _pCandidateUnit->unitType != Map::Units::UT_TUNNELER || _pCandidateUnit->tribeID) {
                            unitID = unitID + 1;
                            _pCandidateUnit = _pCandidateUnit + 1;
                            if ((int)unitID >= (int)_maxUnitCount) {
                                return;
                            }
                        }
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            unitID, _tribe);
                        unitID = unitID + 1;
                        if ((int)unitID >= DAT_UnitsState::instance.maxUnitCount) {
                            return;
                        }
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeTunnelEntrances, this)(_tribe);
                        attackWave = attackWave + 1;
                    } while (attackWave < _nTunnels);
                }
            }
        }

    }
}
}
