#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519CC0
        undefined4 TroopValueState::findEnemyWalls(int unitID)
        {
            int _offset;
            int iVar1;
            int fromYPosition;
            AttackInfoSubArrayElement2* piVar2;
            int local_14;
            int local_10;
            int local_8;
            _offset = DAT_UnitsState::instance.units[unitID].owner * 0x177bc;
            local_10 = 1000;
            local_8 = -1;
            local_14 = 0;
            if (0 < *(int*)((int)this->attackInfo.hackValuesArray + _offset + -8)) {
                piVar2 = (AttackInfoSubArrayElement2*)((int)&this->attackInfo.hackValuesArray + _offset + 4);
                do {
                    if ((piVar2->size < 9999) && (!piVar2->unitID)) {
                        fromYPosition
                            = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[piVar2->tile2];
                        iVar1 = piVar2->tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)((int)(DAT_UnitsState::instance.units[unitID].y)), iVar1, fromYPosition);
                        DAT_DirectionAlgorithmState::instance.distanceHigh
                            = DAT_DirectionAlgorithmState::instance.distanceHigh + piVar2->size * 8;
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < local_10) {
                            this->tile = piVar2->tile;
                            local_8 = local_14;
                            local_10 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->x = iVar1;
                            this->y = fromYPosition;
                        }
                    }
                    local_14 = local_14 + 1;
                    piVar2 = piVar2 + 4;
                } while (local_14 < *(int*)((int)this->attackInfo.hackValuesArray + _offset + -8));
                if (-1 < local_8) {
                    iVar1 = _offset + local_8 * 0x10;
                    *(int*)((int)this->attackInfo.hackValuesArray + iVar1 + 0xc) = unitID;
                    return *(undefined4*)((int)this->attackInfo.hackValuesArray + iVar1 + 4);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
