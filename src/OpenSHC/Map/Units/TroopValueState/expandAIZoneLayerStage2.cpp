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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AE00
        void TroopValueState::expandAIZoneLayerStage2()
        {
            int iVar4;
            for (iVar4 = 0; iVar4 < 80400; iVar4 = iVar4 + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[iVar4] == '\x02') {
                    int iVar3 = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar4];
                    int iVar1 = 0;
                    int _x = iVar4 - DAT_ViewportRenderState::instance.translationMatrix[iVar3].addXgetTile;
                    do {
                        if (!(DAT_TileMapState::instance.AIInfoLayer[iVar4
                                  + DAT_TileMapState::instance.directionTranslationMatrix[iVar3][iVar1 * 2]]
                                & 0xf)) {
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                DAT_PathFindingState::ptr)(0xf,
                                (uint)((
                                    int)(DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar1 * 2]
                                             .int_.xOffset
                                    + _x)),
                                (uint)(DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar1 * 2]
                                           .int_.yOffset
                                    + iVar3),
                                4);
                            break;
                        }
                        iVar1 = iVar1 + 1;
                    } while (iVar1 < 4);
                }
            }
        }

    }
}
}
