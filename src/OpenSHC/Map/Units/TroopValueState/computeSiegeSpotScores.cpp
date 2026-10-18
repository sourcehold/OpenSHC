#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00519990
        void TroopValueState::computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID)
        {
            int _index;
            uint* _pScore;
            uint _pathFindingCost;
            BOOLEnum isAtThreshold;
            BOOLEnum isBelowThreshold;
            int _attackedPlayerID;
            uint _tile2;
            uint _tile;
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.id != 0) {
                int _offset = attackingPlayerID * 96188;
                int _hack2 = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack2;
                int _counterTillHack2 = 0;
                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].someMinimumDistance = 10000;
                if (0 < _hack2) {
                    int* _pTileArray = (int*)(DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                            .hackValuesArray);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[attackedPlayerID][*_pTileArray];
                        if ((int)_pathFindingCost
                            < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                .someMinimumDistance) {
                            DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                .someMinimumDistance = _pathFindingCost;
                        }
                        _counterTillHack2 = _counterTillHack2 + 1;
                        _pTileArray = _pTileArray + 4;
                    } while (_counterTillHack2 < _hack2);
                }
                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack3 = 0;
                int _counter2 = 0;
                if (0 < _hack2) {
                    _pScore = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                          .hackValuesArray
                        + 8);
                    do {
                        uint _tile3 = _pScore[-2];
                        _pathFindingCost
                            = (uint)DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile3];
                        _index = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadderInRightDirection,
                            DAT_UnitsState::ptr)(
                            _tile3, (int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile3]));
                        if (_index) {
                            *_pScore = 9999;
                        } else if ((int)_pathFindingCost <= 0) {
                            *_pScore = 9999;
                        } else {
                            _index = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .someMinimumDistance;
                            if (0x32 <= _index) {
                                *_pScore = 9999;
                            } else if ((int)_pathFindingCost >= _index + 0xf) {
                                *_pScore = 9999;
                            } else {
                                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack3
                                    = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack3
                                    + 1;
                                *_pScore = _pathFindingCost;
                            }
                        }
                        _counter2 = _counter2 + 1;
                        _pScore = _pScore + 4;
                    } while (
                        _counter2 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack2);
                }
                int _entryCountOrBias = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].scale2) {
                    _pScore = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                          .scaleValuesArray
                        + 8);
                    do {
                        *_pScore = (5 < DAT_TileMapState::instance
                                           .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                   .playerInfo[attackingPlayerID - 1]
                                                   .currentPlayerID_OR_attackedPlayerID_OR_one][_pScore[-2]])
                            ? 9999
                            : 0;
                        _entryCountOrBias = _entryCountOrBias + 1;
                        _pScore = _pScore + 4;
                    } while (_entryCountOrBias
                        < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].scale2);
                }
                _entryCountOrBias = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].town2) {
                    _pScore = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                          .townValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][_pScore[-2]];
                        if ((int)_pathFindingCost <= 0) {
                            *_pScore = 100;
                        } else {
                            *_pScore = _pathFindingCost;
                        }
                        _entryCountOrBias = _entryCountOrBias + 1;
                        _pScore = _pScore + 4;
                    } while (_entryCountOrBias
                        < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].town2);
                }
                _entryCountOrBias
                    = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].some1000ArrayIndex_2;
                _index = 0;
                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4 = 10000;
                if (0 < _entryCountOrBias) {
                    int _attackedPlayer = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                              .currentPlayerID_OR_attackedPlayerID_OR_one;
                    int* _pGateTile = (int*)(DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                            .gateValuesArray);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[_attackedPlayer][*_pGateTile];
                        if ((int)_pathFindingCost
                            < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                .field22_0x3ea4) {
                            DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4
                                = _pathFindingCost;
                        }
                        _index = _index + 1;
                        _pGateTile = _pGateTile + 4;
                    } while (_index < _entryCountOrBias);
                }
                _index = 0;
                if (0 < _entryCountOrBias) {
                    _pScore = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                          .gateValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][_pScore[-2]];
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4
                            < 0xb) {
                            isBelowThreshold = (_pathFindingCost < 10);
                            _entryCountOrBias = -10;
                            isAtThreshold = _pathFindingCost == 10;
                        } else {
                            isBelowThreshold = (_pathFindingCost < 0x14);
                            _entryCountOrBias = -0x14;
                            isAtThreshold = _pathFindingCost == 0x14;
                        }
                        _index = _index + 1;
                        *_pScore
                            = (isAtThreshold || isBelowThreshold != (int)(_pathFindingCost + _entryCountOrBias) < 0)
                            ? 0
                            : 9999;
                        _pScore = _pScore + 4;
                    } while (_index < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                 .some1000ArrayIndex_2);
                }
                int _counter = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].wide2) {
                    AttackInfoSubElement* _pWideEntry
                        = (AttackInfoSubElement*)((int)&DAT_TroopValueState::instance.attackInfo.wideValuesArray
                            + _offset + 8);
                    do {
                        ((int*)_pWideEntry->hackValuesArray)[2]
                            = (5 < DAT_TileMapState::instance
                                      .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                              .playerInfo[attackingPlayerID - 1]
                                              .currentPlayerID_OR_attackedPlayerID_OR_one]
                                                                     [((int*)_pWideEntry->hackValuesArray)[0]])
                            ? 9999
                            : 0;
                        _counter = _counter + 1;
                        _pWideEntry = (AttackInfoSubElement*)(((int*)_pWideEntry->hackValuesArray) + 6);
                    } while (
                        _counter < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].wide2);
                }
                _entryCountOrBias = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].moat2) {
                    _pScore = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                          .moatValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][_pScore[-2]];
                        if ((int)_pathFindingCost <= 0) {
                            *_pScore = 9999;
                        } else if ((int)_pathFindingCost <= 10) {
                            *_pScore = _pathFindingCost;
                        } else if ((int)_pathFindingCost <= 0xf) {
                            *_pScore = _pathFindingCost * 2;
                        } else if ((int)_pathFindingCost <= 0x14) {
                            *_pScore = _pathFindingCost * 3;
                        } else if ((int)_pathFindingCost <= 0x19) {
                            *_pScore = _pathFindingCost * 4;
                        } else if ((int)_pathFindingCost <= 0x32) {
                            *_pScore = _pathFindingCost * 5;
                        } else if ((int)_pathFindingCost <= 0x46) {
                            *_pScore = _pathFindingCost * 6;
                        } else {
                            *_pScore = 9999;
                        }
                        _entryCountOrBias = _entryCountOrBias + 1;
                        _pScore = _pScore + 4;
                    } while (_entryCountOrBias
                        < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].moat2);
                }
            }
        }

    }
}
}
