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
            int iVar1;
            BOOLEnum BVar2;
            int iVar3;
            int (*paiVar4)[8];
            uint y;
            uint x;
            int iVar5;
            int local_c;
            int local_8;
            iVar5 = 0;
            DAT_TroopValueState::instance.attackInfo.archerPoints = 0;
            if ((int)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 0) {
                local_c = 8;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 2) {
                local_c = 5;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 4) {
                local_c = 6;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 8) {
                local_c = 7;
            } else {
                local_c = (uint)(0x13 < (int)DAT_TroopValueState::instance.attackInfo.field_0x20e00) * 2 + 8;
            }
            do {
                if (DAT_TileMapState::instance.AIInfoLayer[iVar5] == '\x02') {
                    y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar5];
                    local_8 = 0;
                    paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + y;
                    do {
                        if (((*(byte*)((*paiVar4)[0] + 0x1ea7b68 + iVar5) & 0xf) == 4)
                            && (!(DAT_TileMapState::instance.RandomLayer[(*paiVar4)[0] + iVar5] & 3))) {
                            x = iVar5 - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                            BVar2 = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(local_c, x, y, 0x10);
                            if (!BVar2) {
                                DAT_TileMapState::instance.AIInfoLayer[iVar5]
                                    = DAT_TileMapState::instance.AIInfoLayer[iVar5] | 0x10;
                                iVar3 = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::findOrReserveArcherPointSlot, this)(
                                    iVar5);
                                iVar1 = DAT_TroopValueState::instance.attackInfo.archerPointsNext;
                                if (!iVar3) {
                                    DAT_TroopValueState::instance.attackInfo
                                        .arch2ValuesArray[DAT_TroopValueState::instance.attackInfo.archerPointsNext * 2
                                            + 0x3e9]
                                        .buildingID = x;
                                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar1 * 2 + 0x3e9].unitID
                                        = y;
                                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar1 * 2 + 0x3ea].tile
                                        = iVar5;
                                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar1 * 2 + 0x3ea].tile2
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                } else {
                                    DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar3 * 2 + 0x3ea].tile2
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                }
                                DAT_TroopValueState::instance.attackInfo.archerPoints
                                    = DAT_TroopValueState::instance.attackInfo.archerPoints + 1;
                                if (199 < DAT_TroopValueState::instance.attackInfo.archerPoints) {}
                                break;
                            }
                        }
                        local_8 = local_8 + 1;
                        paiVar4 = (int (*)[8])(*paiVar4 + 2);
                    } while (local_8 < 4);
                }
                iVar5 = iVar5 + 1;
                if (0x13a0f < iVar5) {
                    DAT_TroopValueState::instance.attackInfo.field_0x20e00
                        = DAT_TroopValueState::instance.attackInfo.archerPoints;
                }
            } while (true);
        }

    }
}
}
