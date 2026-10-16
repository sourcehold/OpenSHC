#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519990
        void TroopValueState::computeSiegeSpotScores(int attackedPlayerID, int attackingPlayerID)
        {
            int iVar1;
            int* _pTileArray;
            int iVar2;
            uint* puVar3;
            AttackInfoSubElement* puVar4;
            int iVar4;
            int* piVar5;
            int _counter;
            int _counterTillHack2;
            uint _pathFindingCost;
            int _offset;
            bool bVar6;
            bool bVar7;
            uint _tile3;
            int _attackedPlayerID;
            int _hack2;
            uint _tile2;
            uint _tile;
            iVar4 = attackedPlayerID;
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.id != 0) {
                _offset = attackingPlayerID * 96188;
                _hack2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -8);
                _counterTillHack2 = 0;
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x1c) = 10000;
                if (0 < _hack2) {
                    _pTileArray = (int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset);
                    do {
                        _pathFindingCost = (uint) * (byte*)(attackedPlayerID * 80400 + 0x1ee2998 + *_pTileArray);
                        if ((int)_pathFindingCost < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x1c)) {
                            *(uint*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x1c) = _pathFindingCost;
                        }
                        _counterTillHack2 = _counterTillHack2 + 1;
                        _pTileArray = _pTileArray + 4;
                    } while (_counterTillHack2 < _hack2);
                }
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -4) = 0;
                /*
                  warning:
                 */
                attackedPlayerID = 0;
                if (0 < _hack2) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + 8);
                    do {
                        _tile3 = puVar3[-2];
                        _pathFindingCost = (uint) * (byte*)(_tile3 + iVar4 * 0x13a10 + 0x1ee2998);
                        iVar2 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadderInRightDirection,
                            DAT_UnitsState::ptr)(_tile3,
                            (int)((int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile3])));
                        if (!iVar2) {
                            if (!_pathFindingCost) {
                                *puVar3 = 9999;
                            } else {
                                iVar2 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x1c);
                                if (iVar2 < 0x32) {
                                    if ((int)_pathFindingCost < iVar2 + 0xf) {
                                        piVar5 = (int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -4);
                                        *piVar5 = *piVar5 + 1;
                                        *puVar3 = _pathFindingCost;
                                    } else {
                                        *puVar3 = 9999;
                                    }
                                } else {
                                    *puVar3 = 9999;
                                }
                            }
                        } else {
                            *puVar3 = 9999;
                        }
                        attackedPlayerID = attackedPlayerID + 1;
                        puVar3 = puVar3 + 4;
                    } while (attackedPlayerID < *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -8));
                }
                iVar4 = 0;
                if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -8)) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + 8);
                    do {
                        *puVar3 = -(uint)(5 < *(byte*)(*(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10)
                                                  * 0x13a10
                                              + 0x1ee2998 + puVar3[-2]))
                            & 9999;
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -8));
                }
                iVar4 = 0;
                if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _offset + -8)) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _offset + 8);
                    do {
                        _pathFindingCost = (uint)
                            * (byte*)(puVar3[-2] + 0x1ee2998
                                + *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10) * 0x13a10);
                        if (!_pathFindingCost) {
                            *puVar3 = 100;
                        } else {
                            *puVar3 = _pathFindingCost;
                        }
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + _offset + -8));
                }
                iVar4 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _offset + -8);
                iVar2 = 0;
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x18) = 10000;
                if (0 < iVar4) {
                    iVar1 = *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10);
                    piVar5 = (int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _offset);
                    do {
                        _pathFindingCost = (uint) * (byte*)(iVar1 * 0x13a10 + 0x1ee2998 + *piVar5);
                        if ((int)_pathFindingCost < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x18)) {
                            *(uint*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x18) = _pathFindingCost;
                        }
                        iVar2 = iVar2 + 1;
                        piVar5 = piVar5 + 4;
                    } while (iVar2 < iVar4);
                }
                iVar2 = 0;
                if (0 < iVar4) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _offset + 8);
                    do {
                        _pathFindingCost = (uint)
                            * (byte*)(puVar3[-2] + 0x1ee2998
                                + *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10) * 0x13a10);
                        if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x18) < 0xb) {
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
                    } while (iVar2 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + _offset + -8));
                }
                _counter = 0;
                if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + _offset + -8)) {
                    puVar4 = (AttackInfoSubElement*)((int)&DAT_TroopValueState::instance.attackInfo.wideValuesArray + _offset + 8);
                    do {
                        puVar4->field4_0x10[2]
                            = -(uint)(5 < *(byte*)(puVar4->field4_0x10[0] + 0x1ee2998
                                          + *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10) * 80400))
                            & 9999;
                        _counter = _counter + 1;
                        puVar4 = (AttackInfoSubElement*)(puVar4->field4_0x10 + 6);
                    } while (_counter < *(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + _offset + -8));
                }
                iVar4 = 0;
                if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -8)) {
                    puVar3 = (uint*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + 8);
                    do {
                        _pathFindingCost = (uint)
                            * (byte*)(puVar3[-2] + 0x1ee2998
                                + *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0x10) * 0x13a10);
                        if (!_pathFindingCost) {
                        LAB_00519ca1:
                            *puVar3 = 9999;
                        } else if (_pathFindingCost < 0xb) {
                            *puVar3 = _pathFindingCost;
                        } else if (_pathFindingCost < 0x10) {
                            *puVar3 = _pathFindingCost * 2;
                        } else if (_pathFindingCost < 0x15) {
                            *puVar3 = _pathFindingCost * 3;
                        } else if (_pathFindingCost < 0x1a) {
                            *puVar3 = _pathFindingCost * 4;
                        } else if (_pathFindingCost < 0x33) {
                            *puVar3 = _pathFindingCost * 5;
                        } else {
                            if (0x46 < _pathFindingCost)
                                goto LAB_00519ca1;
                            *puVar3 = _pathFindingCost * 6;
                        }
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + _offset + -8));
                }
            }
        }

    }
}
}
