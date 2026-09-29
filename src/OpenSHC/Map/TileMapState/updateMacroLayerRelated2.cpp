#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_SEA;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF080
    void TileMapState::updateMacroLayerRelated2()
    {
        int startRow;
        startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (int block = this->someIndex; block <= this->someLimit; block++) {
            for (int sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (this->mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    int group = 2;
                    do {
                    if ((uint)this->DAT_SomeX < 400 && (uint)this->DAT_SomeY < 400
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + this->DAT_SomeX] != 0) {
                        this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + this->DAT_SomeX;
                        if (this->ChangedLayer[this->DAT_SomeTile] != 0
                        && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                            this->MacroLayer[this->DAT_SomeTile] = 0x800;
                        }
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->ChangedLayer[this->DAT_SomeTile] != 0
                        && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 0x800;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->ChangedLayer[this->DAT_SomeTile] != 0
                        && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 0x800;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->ChangedLayer[this->DAT_SomeTile] != 0
                        && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 0x800;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->ChangedLayer[this->DAT_SomeTile] != 0
                        && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 0x800;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                        this->DAT_SomeX = this->DAT_SomeX + 1;
                        group = group + -1;
                    } while (group != 0);
                }
                startRow = 0;
            }
        }

        startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (int block = this->someIndex; block <= this->someLimit; block++) {
            for (int sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (this->mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    int column = 10;
                    do {
                        if ((uint)this->DAT_SomeX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + this->DAT_SomeX] != 0) {
                            this->DAT_SomeTile = this->DAT_SomeX
                                + DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile;
                            if (this->MacroLayer[this->DAT_SomeTile] == 0x800
                                && (this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                ushort random = this->RandomLayer[this->DAT_SomeTile];
                                int corner = this->DAT_SomeTile
                                    - DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile;
                                /* a wave sprite only fits where all sixteen of its tiles are still marked */
                                bool complete = true;
                                for (int i = 0; i < 0x10; i++) {
                                    if (this->MacroLayer[DAT_ViewportRenderState::instance
                                                             .translationMatrix[DAT_TerrainDefinedData::instance.field2292_0x19d4[i].y
                                                                 + this->DAT_SomeY]
                                                             .addXgetTile
                                            + DAT_TerrainDefinedData::instance.field2292_0x19d4[i].x + corner]
                                        != 0x800) {
                                        complete = false;
                                        break;
                                    }
                                }
                                if (complete) {
                                    for (int i = 0; i < 0x10; i++) {
                                        this->MacroLayer[DAT_ViewportRenderState::instance
                                                             .translationMatrix[DAT_TerrainDefinedData::instance.field2292_0x19d4[i].y
                                                                 + this->DAT_SomeY]
                                                             .addXgetTile
                                            + DAT_TerrainDefinedData::instance.field2292_0x19d4[i].x + corner]
                                            = (ushort)(byte)random * 0x1000 + 0x10 + (short)(i << 6);
                                    }
                                }
                            }
                        }
                        this->DAT_SomeX = this->DAT_SomeX + 1;
                        column = column + -1;
                    } while (column != 0);
                }
                startRow = 0;
            }
        }

        startRow = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (int block = this->someIndex; block <= this->someLimit; block++) {
            for (int sub = this->someYLike; sub <= this->someYLikeLimit; sub++) {
                if (this->mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->DAT_SomeY = block * 10 + row;
                    this->DAT_SomeX = sub * 10;
                    int group = 2;
                    do {
                    if ((uint)this->DAT_SomeX < 400 && (uint)this->DAT_SomeY < 400
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + this->DAT_SomeX] != 0) {
                        this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + this->DAT_SomeX;
                        if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                            this->MacroLayer[this->DAT_SomeTile] = 2;
                        }
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                this->MacroLayer[this->DAT_SomeTile] = 2;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                this->MacroLayer[this->DAT_SomeTile] = 2;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                this->MacroLayer[this->DAT_SomeTile] = 2;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                    {
                        uint nextX = this->DAT_SomeX + 1;
                        if (nextX < 400 && (uint)this->DAT_SomeY < 400
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->DAT_SomeY * 400 + nextX] != 0) {
                            this->DAT_SomeTile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_SomeY].addXgetTile + nextX;
                            if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                this->MacroLayer[this->DAT_SomeTile] = 2;
                            }
                        }
                        this->DAT_SomeX = nextX;
                    }
                        this->DAT_SomeX = this->DAT_SomeX + 1;
                        group = group + -1;
                    } while (group != 0);
                }
                startRow = 0;
            }
        }
    }

}
}
