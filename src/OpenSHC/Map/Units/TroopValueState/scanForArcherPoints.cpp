#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F340
        void TroopValueState::scanForArcherPoints()
        {
            BOOLEnum BVar2;
            int iVar3;
            int local_c;
            DAT_TroopValueState::instance.attackInfo.archerPoints = 0;
            if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 0) {
                local_c = 8;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 2) {
                local_c = 5;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 4) {
                local_c = 6;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 8) {
                local_c = 7;
            } else {
                local_c = (uint)(0x14 <= (int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev) * 2 + 8;
            }
            for (int iVar5 = 0; iVar5 < 80400; iVar5 = iVar5 + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[iVar5] == '') {
                    uint y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar5];
                    for (int _direction = 0; _direction < 4; _direction = _direction + 1) {
                        if ((DAT_TileMapState::instance.AIInfoLayer
                                    [DAT_TileMapState::instance.directionTranslationMatrix[y][_direction * 2] + iVar5]
                                & 0xf)
                                == 4
                            && !(DAT_TileMapState::instance.RandomLayer
                                     [DAT_TileMapState::instance.directionTranslationMatrix[y][_direction * 2] + iVar5]
                                & 3)) {
                            uint x = iVar5 - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                            BVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(local_c, x, y, 0x10);
                            if (!BVar2) {
                                DAT_TileMapState::instance.AIInfoLayer[iVar5]
                                    = DAT_TileMapState::instance.AIInfoLayer[iVar5] | 0x10;
                                iVar3 = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::findOrReserveArcherPointSlot, this)(iVar5);
                                int iVar1 = DAT_TroopValueState::instance.attackInfo.archerPointsNext;
                                if (iVar3) {
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[iVar3].lastSeenCounter
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                } else {
                                    DAT_TroopValueState::instance.attackInfo
                                        .archerPointArray[DAT_TroopValueState::instance.attackInfo.archerPointsNext]
                                        .field0_0x0 = x;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[iVar1].field1_0x4 = y;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[iVar1].tile = iVar5;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[iVar1].lastSeenCounter
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                }
                                DAT_TroopValueState::instance.attackInfo.archerPoints
                                    = DAT_TroopValueState::instance.attackInfo.archerPoints + 1;
                                if (200 <= DAT_TroopValueState::instance.attackInfo.archerPoints) {
                                    DAT_TroopValueState::instance.attackInfo.archerPointCountPrev
                                        = DAT_TroopValueState::instance.attackInfo.archerPoints;
                                    return;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            DAT_TroopValueState::instance.attackInfo.archerPointCountPrev
                = DAT_TroopValueState::instance.attackInfo.archerPoints;
        }

    }
}
}
