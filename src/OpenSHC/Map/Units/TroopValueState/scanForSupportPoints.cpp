#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F4B0
        void TroopValueState::scanForSupportPoints()
        {
            int iVar1;
            BOOLEnum BVar2;
            int iVar3;
            int (*paiVar4)[8];
            uint y;
            uint x;
            int tile;
            int local_8;
            tile = 0;
            this->attackInfo.supportPoints = 0;
            do {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x01') {
                    y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    local_8 = 0;
                    paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + y;
                    do {
                        if (((*(byte*)((*paiVar4)[0] + 0x1ea7b68 + tile) & 0xf) == 2)
                            && (!(DAT_TileMapState::instance.RandomLayer[(*paiVar4)[0] + tile] & 3))) {
                            x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                            BVar2 = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(8, x, y, 0x40);
                            if (!BVar2) {
                                DAT_TileMapState::instance.AIInfoLayer[tile]
                                    = DAT_TileMapState::instance.AIInfoLayer[tile] | 0x40;
                                iVar3 = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::getSupportPointIndex, this)(tile);
                                iVar1 = this->attackInfo.supportPointsNext;
                                if (!iVar3) {
                                    this->attackInfo.supportPointsArray[this->attackInfo.supportPointsNext].x = x;
                                    this->attackInfo.supportPointsArray[iVar1].y = y;
                                    this->attackInfo.supportPointsArray[iVar1].tile = tile;
                                    this->attackInfo.supportPointsArray[iVar1].someCounter
                                        = this->attackInfo.someCounter1;
                                } else {
                                    this->attackInfo.supportPointsArray[iVar3].someCounter
                                        = this->attackInfo.someCounter1;
                                }
                                this->attackInfo.supportPoints = this->attackInfo.supportPoints + 1;
                                if (199 < this->attackInfo.supportPoints) {}
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
