#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH 0x8000 // L_DEFAULT_EARTH_OR_TEXTURE
#define NEIGHBOUR_FLAGS_MASK_MARSH 0x20000000 // L_MARSH
#define NEIGHBOUR_FLAGS_MASK_SEA 0x1 // L_SEA
#define NEIGHBOUR_FLAGS_MASK_L2_SCRUB 0x1 // L2_SCRUB
#define NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES 0x2 // L2_EARTH_AND_STONES
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM 0x4 // L2_PLATEAU_MEDIUM
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH 0x8 // L2_PLATEAU_HIGH
#define NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS 0x10 // L2_OASIS_GRASS
#define NEIGHBOUR_FLAGS_MASK_L2_BEACH 0x20 // L2_BEACH
#define NEIGHBOUR_FLAGS_MASK_L2_STONES 0x40 // L2_STONES_OR_DRIVEN_SANDUnk
#define NEIGHBOUR_FLAGS_MASK_L2_THICK_SCRUB 0x80 // L2_THICK_SCRUB

#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_OIL;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FDB00
    void TileMapState::updateMacroLayerRelated(uint logic1, uint logic2, int clearMacroFirst)
    {
        // Five copies of the same block/sub-tile loop skeleton, and eleven expansions of the
        // handwritten neighbour-flag macro (see NeighbourFlagsGlobalAsm.hpp). The original was built
        // without optimisation, so the pragma above is needed to reproduce its frame-pointer,
        // reload-per-access code shape.
        //
        // At /Od MSVC lays the locals out by a hash of their NAME (16 buckets, walked in order;
        // inside one bucket the later declaration gets the higher slot), not by declaration order.
        // The names and their order below were chosen so the slots land where the original has them
        // (oldMacro at ebp-4 down to savedBitFlag at ebp-0x34); renaming any of them moves the slots.
        int oldMacro;
        int rotation;
        int sectorColumn;
        int tileRow;
        int offsetTile;
        int sectorRow;
        int scanIndex;
        int savedBitFlag;
        int tileX;
        int offsetX;
        int randomVal;
        int tableY;
        int tileColumn;

        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (sectorRow = this->someIndex; sectorRow <= this->someLimit; sectorRow++) {
            for (sectorColumn = this->someYLike; sectorColumn <= this->someYLikeLimit; sectorColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[sectorRow][sectorColumn] != 0) {
                    tileRow = rotation;
                    rotation = 0;
                    for (; tileRow < 10; tileRow++) {
                        for (tileColumn = 0, this->DAT_SomeY = sectorRow * 10 + tileRow,
                            this->DAT_SomeX = sectorColumn * 10;
                            tileColumn < 10; tileColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if ((char)this->ChangedLayer[this->DAT_SomeTile] == 0) {
                                continue;
                            }
                            oldMacro = this->MacroLayer[this->DAT_SomeTile];
                            if (clearMacroFirst != 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 0;
                            }
                            // the original tests each layer separately and skips the tile only when neither matches
                            if ((this->LogicLayer[this->DAT_SomeTile] & logic1) != 0) {
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & logic2) != 0) {
                            } else {
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                                this->bitFlag = 0;
                            } else if (logic1 == L_DEFAULT_EARTH_OR_TEXTURE) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(1, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                            } else if (logic1 == L_MARSH) {
                                if ((this->LogicLayer[this->DAT_SomeTile] & L_OIL) != 0) {
                                    continue;
                                }
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(2, NEIGHBOUR_FLAGS_MASK_MARSH)
                            } else if (logic2 == L2_EARTH_AND_STONES) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(3, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                            } else if (logic2 == L2_OASIS_GRASS) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(4, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                            } else if (logic2 == L2_SCRUB) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                            } else if (logic2 == L2_THICK_SCRUB) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(6, NEIGHBOUR_FLAGS_MASK_L2_THICK_SCRUB)
                            } else if (logic2 == L2_STONES_OR_DRIVEN_SANDUnk) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(7, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                            } else if (logic2 == L2_BEACH) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(8, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                savedBitFlag = this->bitFlag;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(9, NEIGHBOUR_FLAGS_MASK_SEA)
                                this->bitFlag |= savedBitFlag;
                            } else if (logic2 == L2_PLATEAU_MEDIUM) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(10, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                            } else if (logic2 == L2_PLATEAU_HIGH) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(11, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                            } else {
                                this->bitFlag = 0;
                            }
                            if (this->bitFlag != 0xff) {
                                this->MacroLayer[this->DAT_SomeTile] = 1;
                            } else if (((short)this->RandomLayer[this->DAT_SomeTile] & 0xf) == 0) {
                                this->MacroLayer[this->DAT_SomeTile] = 2;
                            } else {
                                this->MacroLayer[this->DAT_SomeTile] = 2048;
                            }
                            if (oldMacro != this->MacroLayer[this->DAT_SomeTile]) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                                    &DAT_PathFindingState::instance)(1, this->DAT_SomeX, this->DAT_SomeY);
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (sectorRow = this->someIndex; sectorRow <= this->someLimit; sectorRow++) {
            for (sectorColumn = this->someYLike; sectorColumn <= this->someYLikeLimit; sectorColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[sectorRow][sectorColumn] != 0) {
                    tileRow = rotation;
                    rotation = 0;
                    for (; tileRow < 10; tileRow++) {
                        for (tileColumn = 0, this->DAT_SomeY = sectorRow * 10 + tileRow,
                            this->DAT_SomeX = sectorColumn * 10;
                            tileColumn < 10; tileColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if (this->MacroLayer[this->DAT_SomeTile] != 2048) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->DAT_SomeTile, this->DAT_SomeY);
                            randomVal = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                            for (scanIndex = 0;
                                scanIndex < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                if (this->MacroLayer[offsetTile] != 2048) {
                                    break;
                                }
                            }
                            if (scanIndex < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets)) {
                                continue;
                            }
                            for (scanIndex = 0;
                                scanIndex < countof(DAT_TerrainDefinedData::instance.MacroLayerScanOffsets);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.MacroLayerScanOffsets[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                this->MacroLayer[offsetTile] = 16;
                                this->MacroLayer[offsetTile] += scanIndex << 6;
                                this->MacroLayer[offsetTile] += randomVal * 4096;
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (sectorRow = this->someIndex; sectorRow <= this->someLimit; sectorRow++) {
            for (sectorColumn = this->someYLike; sectorColumn <= this->someYLikeLimit; sectorColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[sectorRow][sectorColumn] != 0) {
                    tileRow = rotation;
                    rotation = 0;
                    for (; tileRow < 10; tileRow++) {
                        for (tileColumn = 0, this->DAT_SomeY = sectorRow * 10 + tileRow,
                            this->DAT_SomeX = sectorColumn * 10;
                            tileColumn < 10; tileColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if (this->MacroLayer[this->DAT_SomeTile] != 2048) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->DAT_SomeTile, this->DAT_SomeY);
                            randomVal = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                            for (scanIndex = 0; scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x198c);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.field_0x198c[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.field_0x198c[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                if (this->MacroLayer[offsetTile] != 2048) {
                                    break;
                                }
                            }
                            if (scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x198c)) {
                                continue;
                            }
                            for (scanIndex = 0; scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x198c);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.field_0x198c[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.field_0x198c[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                this->MacroLayer[offsetTile] = 8;
                                this->MacroLayer[offsetTile] += scanIndex << 6;
                                this->MacroLayer[offsetTile] += randomVal * 4096;
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (sectorRow = this->someIndex; sectorRow <= this->someLimit; sectorRow++) {
            for (sectorColumn = this->someYLike; sectorColumn <= this->someYLikeLimit; sectorColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[sectorRow][sectorColumn] != 0) {
                    tileRow = rotation;
                    rotation = 0;
                    for (; tileRow < 10; tileRow++) {
                        for (tileColumn = 0, this->DAT_SomeY = sectorRow * 10 + tileRow,
                            this->DAT_SomeX = sectorColumn * 10;
                            tileColumn < 10; tileColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if (this->MacroLayer[this->DAT_SomeTile] != 2048) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->DAT_SomeTile, this->DAT_SomeY);
                            randomVal = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                            for (scanIndex = 0; scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x196c);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.field_0x196c[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.field_0x196c[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                if (this->MacroLayer[offsetTile] != 2048) {
                                    break;
                                }
                            }
                            if (scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x196c)) {
                                continue;
                            }
                            for (scanIndex = 0; scanIndex < countof(DAT_TerrainDefinedData::instance.field_0x196c);
                                scanIndex++) {
                                offsetX = DAT_TerrainDefinedData::instance.field_0x196c[scanIndex].x;
                                tableY = DAT_TerrainDefinedData::instance.field_0x196c[scanIndex].y;
                                offsetTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        &DAT_ViewportRenderState::instance)(tileX + offsetX, this->DAT_SomeY + tableY);
                                this->MacroLayer[offsetTile] = 4;
                                this->MacroLayer[offsetTile] += scanIndex << 6;
                                this->MacroLayer[offsetTile] += randomVal * 4096;
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (sectorRow = this->someIndex; sectorRow <= this->someLimit; sectorRow++) {
            for (sectorColumn = this->someYLike; sectorColumn <= this->someYLikeLimit; sectorColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[sectorRow][sectorColumn] != 0) {
                    tileRow = rotation;
                    rotation = 0;
                    for (; tileRow < 10; tileRow++) {
                        for (tileColumn = 0, this->DAT_SomeY = sectorRow * 10 + tileRow,
                            this->DAT_SomeX = sectorColumn * 10;
                            tileColumn < 10; tileColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if (this->MacroLayer[this->DAT_SomeTile] != 2048) {
                                continue;
                            }
                            this->MacroLayer[this->DAT_SomeTile] = 2;
                        }
                    }
                }
            }
        }
    }

}
}

#pragma optimize("", on)
