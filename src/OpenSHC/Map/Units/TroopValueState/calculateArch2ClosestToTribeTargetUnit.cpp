#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AB60
        int TroopValueState::calculateArch2ClosestToTribeTargetUnit(int tribeID)
        {
            int fromXPosition;
            int iVar1;
            AttackInfoSubArrayElement1* piVar2;
            int fromYPosition;
            int local_c;
            int local_8;
            iVar1 = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            local_c = 1000;
            local_8 = -1;
            tribeID = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.arch2) {
                piVar2 = &DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[0];
                do {
                    if ((DAT_BuildingsState::instance.buildings[piVar2->buildingID].unknownCounterTo10000_0x2b4 < 9999)
                        && (!piVar2->unitID)) {
                        fromYPosition
                            = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[piVar2->tile2];
                        fromXPosition = piVar2->tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[iVar1].x,
                            (int)((int)(DAT_UnitsState::instance.units[iVar1].y)), fromXPosition, fromYPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < local_c) {
                            DAT_TroopValueState::instance.tile = piVar2->tile;
                            local_c = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            local_8 = tribeID;
                            DAT_TroopValueState::instance.x = fromXPosition;
                            DAT_TroopValueState::instance.y = fromYPosition;
                        }
                    }
                    tribeID = tribeID + 1;
                    piVar2 = piVar2 + 4;
                } while (tribeID < DAT_TroopValueState::instance.attackInfo.arch2);
                if (-1 < local_8) {
                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[local_8].unitID = iVar1;
                    return DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[local_8].tile2;
                }
            }
            return 0;
        }

    }
}
}
