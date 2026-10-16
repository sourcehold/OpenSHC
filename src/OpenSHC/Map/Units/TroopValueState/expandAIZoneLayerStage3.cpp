#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AE90
        void TroopValueState::expandAIZoneLayerStage3()
        {
            int iVar1;
            int (*paiVar2)[8];
            int iVar3;
            int iVar4;
            iVar4 = 0;
            do {
                if (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\x04') {
                    iVar3 = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar4];
                    iVar1 = 0;
                    paiVar2 = DAT_TileMapState::instance.directionTranslationMatrix + iVar3;
                    do {
                        if (!(*(byte*)(iVar4 + 0x1ea7b68 + (*paiVar2)[0]) & 0xf)) {
                            MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                DAT_PathFindingState::ptr)(0xf,
                                (uint)((
                                    int)(DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar1 * 2]
                                             .int_.xOffset
                                    + (iVar4
                                        - DAT_ViewportRenderState::instance.translationMatrix[iVar3].addXgetTile))),
                                (uint)((int)(*(int*)((int)DAT_TerrainDefinedData::instance
                                                         .clockwiseCardinalTranslationMatrix
                                                 + iVar1 * 0x10 + 4)
                                    + iVar3)),
                                8);
                            break;
                        }
                        iVar1 = iVar1 + 1;
                        paiVar2 = (int (*)[8])(*paiVar2 + 2);
                    } while (iVar1 < 4);
                }
                iVar4 = iVar4 + 1;
                if (0x13a0f < iVar4) {
                    return;
                }
            } while (true);
        }

    }
}
}
