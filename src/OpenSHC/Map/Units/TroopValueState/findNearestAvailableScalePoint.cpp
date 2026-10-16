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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519E40
        undefined4 TroopValueState::findNearestAvailableScalePoint(int unitID)
        {
            int iVar1;
            int fromXPosition;
            int* piVar2;
            int fromYPosition;
            int local_14;
            int local_10;
            int local_8;
            iVar1 = DAT_UnitsState::instance.units[unitID].owner * 0x177bc;
            local_10 = 1000;
            local_8 = -1;
            local_14 = 0;
            if (0 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -8)) {
                piVar2 = (int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + 4);
                do {
                    if ((piVar2[1] < 5999) && (piVar2[2] == 0)) {
                        fromYPosition
                            = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[*piVar2];
                        fromXPosition
                            = *piVar2 - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)((int)(DAT_UnitsState::instance.units[unitID].y)), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < local_10) {
                            local_10 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            DAT_TroopValueState::instance.tile = piVar2[-1];
                            local_8 = local_14;
                            DAT_TroopValueState::instance.x = fromXPosition;
                            DAT_TroopValueState::instance.y = fromYPosition;
                        }
                    }
                    local_14 = local_14 + 1;
                    piVar2 = piVar2 + 4;
                } while (
                    local_14 < *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + -8));
                if (-1 < local_8) {
                    iVar1 = iVar1 + local_8 * 0x10;
                    *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + 0xc) = unitID;
                    return *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + iVar1 + 4);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
