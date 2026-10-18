#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051ACE0
        void TroopValueState::expandAIZoneLayerStage1()
        {
            int direction;
            int y;
            int tile;
            for (tile = 0; tile < 80400; tile = tile + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x01') {
                    y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    direction = 0;
                    int _x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    do {
                        if (!(DAT_TileMapState::instance.AIInfoLayer[tile
                                  + DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]]
                                & 0xf)) {
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                DAT_PathFindingState::ptr)(6,
                                (uint)(DAT_TerrainDefinedData::instance
                                           .clockwiseCardinalTranslationMatrix[direction * 2]
                                           .int_.xOffset
                                    + _x),
                                (uint)(DAT_TerrainDefinedData::instance
                                           .clockwiseCardinalTranslationMatrix[direction * 2]
                                           .int_.yOffset
                                    + y),
                                2);
                            break;
                        }
                        direction = direction + 1;
                    } while (direction < 4);
                }
            }
            for (tile = 0; tile < 80400; tile = tile + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x02') {
                    DAT_TileMapState::instance.AIInfoLayer[tile] = '\x01';
                }
            }
            for (tile = 0; tile < 80400; tile = tile + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '\x01') {
                    direction = 0;
                    y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    int _x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    do {
                        if (!(DAT_TileMapState::instance.AIInfoLayer[tile
                                  + DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]]
                                & 0xf)) {
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::recomputeALGPathFindingTileMapUnk,
                                DAT_PathFindingState::ptr)(10,
                                (uint)(DAT_TerrainDefinedData::instance
                                           .clockwiseCardinalTranslationMatrix[direction * 2]
                                           .int_.xOffset
                                    + _x),
                                (uint)(DAT_TerrainDefinedData::instance
                                           .clockwiseCardinalTranslationMatrix[direction * 2]
                                           .int_.yOffset
                                    + y),
                                2);
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
