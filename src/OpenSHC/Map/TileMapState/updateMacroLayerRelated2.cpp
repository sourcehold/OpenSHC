#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_SEA;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FF080
    void TileMapState::updateMacroLayerRelated2()
    {
        int block;
        int sub;
        int startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (block = this->someIndex; block <= this->someLimit; block++) {
            for (sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                int row = startRow;
                startRow = 0;
                for (; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    for (int column = 0; column < 10; column++, this->DAT_SomeX++) {
                        uint const x = this->DAT_SomeX;
                        uint const y = this->DAT_SomeY;
                        if (x > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x]
                                == 0) {
                            continue;
                        }
                        this->DAT_SomeTile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile
                            + this->DAT_SomeX;
                        if (this->ChangedLayer[this->DAT_SomeTile] != 0
                            && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                            this->MacroLayer[this->DAT_SomeTile] = 2048;
                        }
                    }
                }
            }
        }

        startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (block = this->someIndex; block <= this->someLimit; block++) {
            for (sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                int row = startRow;
                startRow = 0;
                for (; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    for (int column = 0; column < 10; column++, this->DAT_SomeX++) {
                        uint const x = this->DAT_SomeX;
                        uint const y = this->DAT_SomeY;
                        if (x > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x]
                                == 0) {
                            continue;
                        }
                        this->DAT_SomeTile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile
                            + this->DAT_SomeX;
                        if (this->MacroLayer[this->DAT_SomeTile] != 2048
                            || (this->LogicLayer[this->DAT_SomeTile] & L_SEA) == 0) {
                            continue;
                        }
                        int const corner = this->DAT_SomeTile
                            - DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile;
                        int const random = this->RandomLayer[this->DAT_SomeTile] & 0xf;
                        // a wave sprite only fits where all sixteen of its tiles are still marked
                        int i;
                        for (i = 0; i < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets); i++) {
                            int const scanTile
                                = DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[i].y
                                          + this->DAT_SomeY]
                                      .addXgetTile
                                + DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[i].x + corner;
                            if (this->MacroLayer[scanTile] != 2048) {
                                break;
                            }
                        }
                        if (i < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets)) {
                            continue;
                        }
                        for (i = 0; i < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets); i++) {
                            int const scanTile
                                = DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[i].y
                                          + this->DAT_SomeY]
                                      .addXgetTile
                                + DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[i].x + corner;
                            this->MacroLayer[scanTile] = random * 4096;
                            this->MacroLayer[scanTile] += i * 64 + 16;
                        }
                    }
                }
            }
        }

        startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (block = this->someIndex; block <= this->someLimit; block++) {
            for (sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                int row = startRow;
                startRow = 0;
                for (; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    for (int column = 0; column < 10; column++, this->DAT_SomeX++) {
                        uint const x = this->DAT_SomeX;
                        uint const y = this->DAT_SomeY;
                        if (x > MC_MAP_XY_LIMIT_MIN_1 || y > MC_MAP_XY_LIMIT_MIN_1
                            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x]
                                == 0) {
                            continue;
                        }
                        this->DAT_SomeTile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile
                            + this->DAT_SomeX;
                        if (this->MacroLayer[this->DAT_SomeTile] == 2048) {
                            this->MacroLayer[this->DAT_SomeTile] = 2;
                        }
                    }
                }
            }
        }
    }

}
}
