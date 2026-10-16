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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F4B0
        void TroopValueState::scanForSupportPoints()
        {
            BOOLEnum BVar2;
            int iVar3;
            int (*paiVar4)[8];
            uint y;
            uint x;
            int tile;
            int local_8;
            tile = 0;
            DAT_TroopValueState::instance.attackInfo.supportPoints = 0;
            do {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x01') {
                    y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    local_8 = 0;
                    paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + y;
                    do {
                        if ((*(byte*)((*paiVar4)[0] + 0x1ea7b68 + tile) & 0xf) == 2
                            && !(DAT_TileMapState::instance.RandomLayer[(*paiVar4)[0] + tile] & 3)) {
                            x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                            BVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(8, x, y, 0x40);
                            if (!BVar2) {
                                DAT_TileMapState::instance.AIInfoLayer[tile]
                                    = DAT_TileMapState::instance.AIInfoLayer[tile] | 0x40;
                                iVar3 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getSupportPointIndex, this)(
                                    tile);
                                int iVar1 = DAT_TroopValueState::instance.attackInfo.supportPointsNext;
                                if (!iVar3) {
                                    DAT_TroopValueState::instance.attackInfo
                                        .supportPointsArray[DAT_TroopValueState::instance.attackInfo.supportPointsNext]
                                        .x = x;
                                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar1].y = y;
                                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar1].tile = tile;
                                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar1].someCounter
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                } else {
                                    DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar3].someCounter
                                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                }
                                DAT_TroopValueState::instance.attackInfo.supportPoints
                                    = DAT_TroopValueState::instance.attackInfo.supportPoints + 1;
                                if (199 < DAT_TroopValueState::instance.attackInfo.supportPoints) {}
                                break;
                            }
                        }
                        local_8 = local_8 + 1;
                        paiVar4 = (int (*)[8])(*paiVar4 + 2);
                    } while (local_8 < 4);
                }
                tile = tile + 1;
                if (0x13a0f < tile) {}
            } while (true);
        }

    }
}
}
