#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
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
            for (int tile = 0; tile < countof(DAT_TileMapState::instance.AIInfoLayer); ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 4) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                // direction is declared before x on purpose: declaring it in the for changes the register allocation
                int direction = 0;
                int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                for (; direction < 4; ++direction) {
                    if (!(DAT_TileMapState::instance.AIInfoLayer[tile
                              + DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]]
                            & 15)) {
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                            DAT_PathFindingState::ptr)(15,
                            DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction * 2]
                                    .int_.xOffset
                                + x,
                            DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction * 2]
                                    .int_.yOffset
                                + y,
                            8);
                        break;
                    }
                }
            }
        }

    }
}
}
