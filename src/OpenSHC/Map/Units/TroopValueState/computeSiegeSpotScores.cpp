#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519990
        void TroopValueState::computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID)
        {
            int* _pTileArray;
            int iVar2;
            uint* puVar3;
            AttackInfoSubElement* puVar4;
            int iVar4;
            int _counter2;
            int* piVar5;
            int _counter;
            int _counterTillHack2;
            uint _pathFindingCost;
            int _offset;
            int bVar6;
            int bVar7;
            uint _tile3;
            int _attackedPlayerID;
            int _hack2;
            uint _tile2;
            uint _tile;
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.id != 0) {
                _offset = attackingPlayerID * 96188;
                _hack2 = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack2;
                _counterTillHack2 = 0;
                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].someMinimumDistance = 10000;
                if (0 < _hack2) {
                    _pTileArray = (int*)(DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
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
                _counter2 = 0;
                if (0 < _hack2) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .hackValuesArray
                        + 8);
                    do {
                        _tile3 = puVar3[-2];
                        _pathFindingCost
                            = (uint)DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[attackedPlayerID][_tile3];
                        iVar2 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadderInRightDirection,
                            DAT_UnitsState::ptr)(
                            _tile3, (int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile3]));
                        if (iVar2) {
                            *puVar3 = 9999;
                            goto LAB_0051aae8;
                        }
                        if ((int)_pathFindingCost <= 0) {
                            *puVar3 = 9999;
                            goto LAB_0051aae8;
                        }
                        iVar2 = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].someMinimumDistance;
                        if (0x32 <= iVar2) {
                            *puVar3 = 9999;
                            goto LAB_0051aae8;
                        }
                        if (iVar2 + 0xf <= (int)_pathFindingCost) {
                            *puVar3 = 9999;
                            goto LAB_0051aae8;
                        }
                        DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack3
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack3 + 1;
                        *puVar3 = _pathFindingCost;
                        LAB_0051aae8:
                        _counter2 = _counter2 + 1;
                        puVar3 = puVar3 + 4;
                    } while (_counter2
                        < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].hack2);
                }
                iVar4 = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].scale2) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .scaleValuesArray
                        + 8);
                    do {
                        *puVar3 = -(uint)(5 < DAT_TileMapState::instance
                                              .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                      .playerInfo[attackingPlayerID - 1]
                                                      .currentPlayerID_OR_attackedPlayerID_OR_one][puVar3[-2]])
                            & 9999;
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].scale2);
                }
                iVar4 = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].town2) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .townValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][puVar3[-2]];
                        if ((int)_pathFindingCost <= 0) {
                            *puVar3 = 100;
                        } else {
                            *puVar3 = _pathFindingCost;
                        }
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].town2);
                }
                iVar4 = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].some1000ArrayIndex_2;
                iVar2 = 0;
                DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4 = 10000;
                if (0 < iVar4) {
                    int iVar1 = DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                    .currentPlayerID_OR_attackedPlayerID_OR_one;
                    piVar5 = (int*)(DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                            .gateValuesArray);
                    do {
                        _pathFindingCost
                            = (uint)DAT_TileMapState::instance.SEC_PathfindingCostTileMap1105[iVar1][*piVar5];
                        if ((int)_pathFindingCost
                            < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                .field22_0x3ea4) {
                            DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4
                                = _pathFindingCost;
                        }
                        iVar2 = iVar2 + 1;
                        piVar5 = piVar5 + 4;
                    } while (iVar2 < iVar4);
                }
                iVar2 = 0;
                if (0 < iVar4) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .gateValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][puVar3[-2]];
                        if (DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].field22_0x3ea4
                            < 0xb) {
                            bVar7 = (_pathFindingCost < 10);
                            iVar4 = -10;
                            bVar6 = _pathFindingCost == 10;
                        } else {
                            bVar7 = (_pathFindingCost < 0x14);
                            iVar4 = -0x14;
                            bVar6 = _pathFindingCost == 0x14;
                        }
                        iVar2 = iVar2 + 1;
                        *puVar3 = (bVar6 || bVar7 != (int)(_pathFindingCost + iVar4) < 0) - 1 & 9999;
                        puVar3 = puVar3 + 4;
                    } while (iVar2 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                 .some1000ArrayIndex_2);
                }
                _counter = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].wide2) {
                    puVar4 = (AttackInfoSubElement*)((int)&DAT_TroopValueState::instance.attackInfo.wideValuesArray
                        + _offset + 8);
                    do {
                        ((int*)puVar4->hackValuesArray)[2]
                            = -(uint)(5 < DAT_TileMapState::instance
                                          .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                  .playerInfo[attackingPlayerID - 1]
                                                  .currentPlayerID_OR_attackedPlayerID_OR_one]
                                                                         [((int*)puVar4->hackValuesArray)[0]])
                            & 9999;
                        _counter = _counter + 1;
                        puVar4 = (AttackInfoSubElement*)(((int*)puVar4->hackValuesArray) + 6);
                    } while (
                        _counter < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].wide2);
                }
                iVar4 = 0;
                if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].moat2) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1]
                                         .moatValuesArray
                        + 8);
                    do {
                        _pathFindingCost = (uint)DAT_TileMapState::instance
                                               .SEC_PathfindingCostTileMap1105[DAT_TroopValueState::instance.attackInfo
                                                       .playerInfo[attackingPlayerID - 1]
                                                       .currentPlayerID_OR_attackedPlayerID_OR_one][puVar3[-2]];
                        if ((int)_pathFindingCost <= 0) {
                        LAB_00519ca1:
                            *puVar3 = 9999;
                        } else if ((int)_pathFindingCost <= 10) {
                            *puVar3 = _pathFindingCost;
                        } else if ((int)_pathFindingCost <= 0xf) {
                            *puVar3 = _pathFindingCost * 2;
                        } else if ((int)_pathFindingCost <= 0x14) {
                            *puVar3 = _pathFindingCost * 3;
                        } else if ((int)_pathFindingCost <= 0x19) {
                            *puVar3 = _pathFindingCost * 4;
                        } else if ((int)_pathFindingCost <= 0x32) {
                            *puVar3 = _pathFindingCost * 5;
                        } else if ((int)_pathFindingCost <= 0x46) {
                            *puVar3 = _pathFindingCost * 6;
                        } else {
                            *puVar3 = 9999;
                        }
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < DAT_TroopValueState::instance.attackInfo.playerInfo[attackingPlayerID - 1].moat2);
                }
            }
        }

    }
}
}
