#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A330
        undefined4 TroopValueState::findEnemyTowersOrGates(int unitID)
        {
            undefined4 uVar1;
            int iVar2;
            AttackInfoSubArrayElement1* _p2;
            undefined4* puVar3;
            int iVar4;
            int iVar5;
            int local_14;
            int local_10;
            int local_8;
            AttackInfoSubArrayElement1* _p1;
            iVar4 = DAT_UnitsState::instance.units[unitID].owner * 0x177bc;
            local_10 = 1000;
            local_8 = -1;
            local_14 = 0;
            if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8)) {
                _p1 = (AttackInfoSubArrayElement1*)((int)&DAT_TroopValueState::instance.attackInfo.gateValuesArray
                    + iVar4 + 4);
                do {
                    if ((_p1->buildingID < 5999) && (!_p1->unitID)) {
                        iVar5 = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_p1->tile2];
                        iVar2 = _p1->tile2 - DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)((int)(DAT_UnitsState::instance.units[unitID].y)), iVar2, iVar5);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < local_10) {
                            local_10 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            DAT_TroopValueState::instance.tile = _p1->tile;
                            local_8 = local_14;
                            DAT_TroopValueState::instance.x = iVar2;
                            DAT_TroopValueState::instance.y = iVar5;
                        }
                    }
                    local_14 = local_14 + 1;
                    _p1 = _p1 + 4;
                } while (
                    local_14 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8));
                if (-1 < local_8) {
                    uVar1 = *(undefined4*)(iVar4 + 0x179f10c + local_8 * 0x10);
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + local_8 * 0x10
                        + 0xc) = unitID;
                    return (undefined4)(uVar1);
                }
            }
            iVar2 = 0;
            if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8)) {
                puVar3 = (undefined4*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + 0xc);
                do {
                    *puVar3 = 0;
                    iVar2 = iVar2 + 1;
                    puVar3 = puVar3 + 4;
                } while (iVar2 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8));
            }
            local_10 = 1000;
            local_14 = 0;
            if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8)) {
                _p2 = (AttackInfoSubArrayElement1*)((int)&DAT_TroopValueState::instance.attackInfo.gateValuesArray
                    + iVar4 + 4);
                do {
                    if ((_p2->buildingID < 5999) && (!_p2->unitID)) {
                        iVar5 = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_p2->tile2];
                        iVar2 = _p2->tile2 - DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)((int)(DAT_UnitsState::instance.units[unitID].y)), iVar2, iVar5);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < local_10) {
                            local_10 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            DAT_TroopValueState::instance.tile = _p2->tile;
                            local_8 = local_14;
                            DAT_TroopValueState::instance.x = iVar2;
                            DAT_TroopValueState::instance.y = iVar5;
                        }
                    }
                    local_14 = local_14 + 1;
                    _p2 = _p2 + 4;
                } while (
                    local_14 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar4 + -8));
            }
            if (local_8 < 0) {
                return (undefined4)(0);
            }
            return *(undefined4*)(local_8 * 0x10 + 0x179f10c + iVar4);
        }

    }
}
}
