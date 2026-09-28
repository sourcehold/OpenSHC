#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
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

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_OIL;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FDB00
    void TileMapState::updateMacroLayerRelated(uint logic1, uint logic2, int clearMacroFirst)
    {
        /*
          Five copies of the same block/sub-tile loop skeleton, and eleven expansions of the
          handwritten neighbour-flag macro (see NeighbourFlagsAsm.hpp). The original was built
          without optimisation, so the pragma above is needed to reproduce its frame-pointer,
          reload-per-access code shape; the locals are declared together, in this order, because
          at /Od the stack slots are observable and MSVC assigns them per function, not per scope.
        */
        int previousMacro;
        int rotation;
        int blockColumn;
        int index;
        int blockRow;
        int neighbourTile;
        int subRow;
        int subColumn;
        int tableY;
        int randomValue;
        int tableX;
        int tileXOffset;
        int savedBitFlag;

        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (this->mapping40x40[blockRow][blockColumn] != 0) {
                    subRow = rotation;
                    rotation = 0;
                    for (; subRow < 10; subRow++) {
                        this->DAT_SomeY = blockRow * 10 + subRow;
                        this->DAT_SomeX = blockColumn * 10;
                        for (subColumn = 0; subColumn < 10; subColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY)
                                != FALSE) {
                                this->DAT_SomeTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY);
                                if (this->ChangedLayer[this->DAT_SomeTile] != 0) {
                                    previousMacro = this->MacroLayer[this->DAT_SomeTile];
                                    if (clearMacroFirst != 0) {
                                        this->MacroLayer[this->DAT_SomeTile] = 0;
                                    }
                                    if ((this->LogicLayer[this->DAT_SomeTile] & logic1) != 0
                                        || (this->Logic2Layer[this->DAT_SomeTile] & logic2) != 0) {
                                        if ((this->LogicLayer[this->DAT_SomeTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                                            this->bitFlag = 0;
                                        } else if (logic1 == 0x8000) {
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_8(1, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                                        } else if (logic1 == 0x20000000) {
                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_OIL) == 0) {
                                                MACRO_NEIGHBOUR_FLAGS_LOGIC_8(2, NEIGHBOUR_FLAGS_MASK_MARSH)
                                                if (this->bitFlag != 0xff) {
                                                    this->MacroLayer[this->DAT_SomeTile] = 1;
                                                } else if ((this->RandomLayer[this->DAT_SomeTile] & 0xf) == 0) {
                                                    this->MacroLayer[this->DAT_SomeTile] = 2;
                                                } else {
                                                    this->MacroLayer[this->DAT_SomeTile] = 0x800;
                                                }
                                                if (previousMacro != this->MacroLayer[this->DAT_SomeTile]) {
                                                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                          updateWalkAndPathLayer,
                                                        DAT_PathFindingState::ptr)(1, this->DAT_SomeX, this->DAT_SomeY);
                                                }
                                            }
                                        } else if (logic2 == 0x2) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(3, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                                        } else if (logic2 == 0x10) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(4, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                                        } else if (logic2 == 0x1) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                        } else if (logic2 == 0x80) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(6, NEIGHBOUR_FLAGS_MASK_L2_THICK_SCRUB)
                                        } else if (logic2 == 0x40) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(7, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                                        } else if (logic2 == 0x20) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(8, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                            savedBitFlag = this->bitFlag;
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_8(9, NEIGHBOUR_FLAGS_MASK_SEA)
                                            this->bitFlag = this->bitFlag | savedBitFlag;
                                        } else if (logic2 == 0x4) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(10, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                                        } else if (logic2 == 0x8) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(11, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                                        } else {
                                            this->bitFlag = 0;
                                        }
                                        if (this->bitFlag != 0xff) {
                                            this->MacroLayer[this->DAT_SomeTile] = 1;
                                        } else if ((this->RandomLayer[this->DAT_SomeTile] & 0xf) == 0) {
                                            this->MacroLayer[this->DAT_SomeTile] = 2;
                                        } else {
                                            this->MacroLayer[this->DAT_SomeTile] = 0x800;
                                        }
                                        if (previousMacro != this->MacroLayer[this->DAT_SomeTile]) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                                                DAT_PathFindingState::ptr)(1, this->DAT_SomeX, this->DAT_SomeY);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (this->mapping40x40[blockRow][blockColumn] != 0) {
                    subRow = rotation;
                    rotation = 0;
                    for (; subRow < 10; subRow++) {
                        this->DAT_SomeY = blockRow * 10 + subRow;
                        this->DAT_SomeX = blockColumn * 10;
                        for (subColumn = 0; subColumn < 10; subColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY)
                                != FALSE) {
                                this->DAT_SomeTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY);
                                if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                    tileXOffset = MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeTile, this->DAT_SomeY);
                                    randomValue = this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                    for (index = 0; index < 0x10; index++) {
                                        tableX = DAT_TerrainDefinedData::instance.field2292_0x19d4[index].x;
                                        tableY = DAT_TerrainDefinedData::instance.field2292_0x19d4[index].y;
                                        neighbourTile = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(
                                            tileXOffset + tableX, this->DAT_SomeY + tableY);
                                        if (this->MacroLayer[neighbourTile] != 0x800) {
                                            break;
                                        }
                                    }
                                    if (index >= 0x10) {
                                        for (index = 0; index < 0x10; index++) {
                                            tableX = DAT_TerrainDefinedData::instance.field2292_0x19d4[index].x;
                                            tableY = DAT_TerrainDefinedData::instance.field2292_0x19d4[index].y;
                                            neighbourTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(
                                                tileXOffset + tableX, this->DAT_SomeY + tableY);
                                            this->MacroLayer[neighbourTile] = 0x10;
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + (short)(index << 6);
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + randomValue * 0x1000;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (this->mapping40x40[blockRow][blockColumn] != 0) {
                    subRow = rotation;
                    rotation = 0;
                    for (; subRow < 10; subRow++) {
                        this->DAT_SomeY = blockRow * 10 + subRow;
                        this->DAT_SomeX = blockColumn * 10;
                        for (subColumn = 0; subColumn < 10; subColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY)
                                != FALSE) {
                                this->DAT_SomeTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY);
                                if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                    tileXOffset = MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeTile, this->DAT_SomeY);
                                    randomValue = this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                    for (index = 0; index < 9; index++) {
                                        tableX = DAT_TerrainDefinedData::instance.field2291_0x198c[index].x;
                                        tableY = DAT_TerrainDefinedData::instance.field2291_0x198c[index].y;
                                        neighbourTile = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(
                                            tileXOffset + tableX, this->DAT_SomeY + tableY);
                                        if (this->MacroLayer[neighbourTile] != 0x800) {
                                            break;
                                        }
                                    }
                                    if (index >= 9) {
                                        for (index = 0; index < 9; index++) {
                                            tableX = DAT_TerrainDefinedData::instance.field2291_0x198c[index].x;
                                            tableY = DAT_TerrainDefinedData::instance.field2291_0x198c[index].y;
                                            neighbourTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(
                                                tileXOffset + tableX, this->DAT_SomeY + tableY);
                                            this->MacroLayer[neighbourTile] = 8;
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + (short)(index << 6);
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + randomValue * 0x1000;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (this->mapping40x40[blockRow][blockColumn] != 0) {
                    subRow = rotation;
                    rotation = 0;
                    for (; subRow < 10; subRow++) {
                        this->DAT_SomeY = blockRow * 10 + subRow;
                        this->DAT_SomeX = blockColumn * 10;
                        for (subColumn = 0; subColumn < 10; subColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY)
                                != FALSE) {
                                this->DAT_SomeTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY);
                                if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                    tileXOffset = MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeTile, this->DAT_SomeY);
                                    randomValue = this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                    for (index = 0; index < 4; index++) {
                                        tableX = DAT_TerrainDefinedData::instance.field2290_0x196c[index].x;
                                        tableY = DAT_TerrainDefinedData::instance.field2290_0x196c[index].y;
                                        neighbourTile = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(
                                            tileXOffset + tableX, this->DAT_SomeY + tableY);
                                        if (this->MacroLayer[neighbourTile] != 0x800) {
                                            break;
                                        }
                                    }
                                    if (index >= 4) {
                                        for (index = 0; index < 4; index++) {
                                            tableX = DAT_TerrainDefinedData::instance.field2290_0x196c[index].x;
                                            tableY = DAT_TerrainDefinedData::instance.field2290_0x196c[index].y;
                                            neighbourTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(
                                                tileXOffset + tableX, this->DAT_SomeY + tableY);
                                            this->MacroLayer[neighbourTile] = 4;
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + (short)(index << 6);
                                            this->MacroLayer[neighbourTile]
                                                = this->MacroLayer[neighbourTile] + randomValue * 0x1000;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (this->mapping40x40[blockRow][blockColumn] != 0) {
                    subRow = rotation;
                    rotation = 0;
                    for (; subRow < 10; subRow++) {
                        this->DAT_SomeY = blockRow * 10 + subRow;
                        this->DAT_SomeX = blockColumn * 10;
                        for (subColumn = 0; subColumn < 10; subColumn++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY)
                                != FALSE) {
                                this->DAT_SomeTile
                                    = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                        DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY);
                                if (this->MacroLayer[this->DAT_SomeTile] == 0x800) {
                                    this->MacroLayer[this->DAT_SomeTile] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
}

#pragma optimize("", on)
