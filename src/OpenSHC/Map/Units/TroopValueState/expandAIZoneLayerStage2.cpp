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
            int tile;
            for (tile = 0; tile < 80400; tile = tile + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x02') {
                    int const y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    int direction = 0;
                    int const _x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    do {
                        if (!(DAT_TileMapState::instance.AIInfoLayer[tile
                                  + DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]]
                                & 0xf)) {
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                DAT_PathFindingState::ptr)(0xf,
                                (uint)((int)(DAT_TerrainDefinedData::instance
                                                 .clockwiseCardinalTranslationMatrix[direction * 2]
                                                 .int_.xOffset
                                    + _x)),
                                (uint)(DAT_TerrainDefinedData::instance
                                           .clockwiseCardinalTranslationMatrix[direction * 2]
                                           .int_.yOffset
                                    + y),
                                4);
                            break;
                        }
                        direction = direction + 1;
                    } while (direction < 4);
                }
            }
        }

    }
}
}
