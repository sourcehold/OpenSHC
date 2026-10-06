#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_MARSH 0x20000000 // L_MARSH
#define NEIGHBOUR_FLAGS_MASK_SEA 0x1 // L_SEA
#define NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH 0x8000 // L_DEFAULT_EARTH_OR_TEXTURE
#define NEIGHBOUR_FLAGS_MASK_L2_SCRUB 0x1 // L2_SCRUB
#define NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES 0x2 // L2_EARTH_AND_STONES
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM 0x4 // L2_PLATEAU_MEDIUM
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH 0x8 // L2_PLATEAU_HIGH
#define NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS 0x10 // L2_OASIS_GRASS
#define NEIGHBOUR_FLAGS_MASK_L2_BEACH 0x20 // L2_BEACH
#define NEIGHBOUR_FLAGS_MASK_L2_STONES 0x40 // L2_STONES_OR_DRIVEN_SANDUnk

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
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC9E0
    void TileMapState::updateGFXLayers()
    {
        /*
          Contains the handwritten neighbour-flag macro nine times (see NeighbourFlagsAsm.hpp), which
          is why the surrounding code is unoptimised: MSVC disables optimisation in a function holding
          inline asm, so every field access reloads this from the frame.

          Two stores below are dead in this function but present in the original, because the body is
          shared with updateMacroLayerRelated where they are read: "rotation" is reassigned from
          MacroLayer at the end of the tile setup, and "height" is never read at all.
        */
        /*
          The locals are declared here, in this order, because the original was built without
          optimisation: its stack slots are observable and MSVC assigns them per function, not per
          scope. Declaring them at first use instead costs ~12 points of match (52.6% vs 64.5%).
        */
        int rotation;
        int blockColumn;
        int gfxMode;
        int index;
        int macroHigh;
        int blockRow;
        int gfxBaseD;
        int luminescence;
        int gfxStride;
        int subRow;
        int subColumn;
        int gfxBaseA;
        int macroLow;
        int gfxBaseE;
        int height;
        int gfxBaseB;
        int gfxBaseC;
        int macroMid;
        int savedBitFlag;

        if (this->forceUpdateGFXLayers <= 0) {
            return;
        }
        this->forceUpdateGFXLayers = this->forceUpdateGFXLayers - 1;

        if (MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::getYSmallerThanYLimit, DAT_PathFindingState::ptr)()
            == FALSE) {
            return;
        }

        rotation = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRow = this->someIndex; blockRow <= this->someLimit; blockRow++) {
            for (blockColumn = this->someYLike; blockColumn <= this->someYLikeLimit; blockColumn++) {
                if (DAT_TileMapState::instance.mapping40x40[blockRow][blockColumn] != 0) {
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
                                if ((this->LogicLayer[this->DAT_SomeTile] & L_DEFAULT_EARTH_OR_TEXTURE) != 0) {
                                    if (this->GfxLayer[this->DAT_SomeTile] == 0) {
                                        luminescence = this->LuminesenceLayer[this->DAT_SomeTile];
                                        if (luminescence < 2) {
                                            luminescence = 2;
                                        }
                                        macroLow = (short)this->MacroLayer[this->DAT_SomeTile] & 0x3f;
                                        macroMid = ((short)this->MacroLayer[this->DAT_SomeTile] & 0x7c0) >> 6;
                                        macroHigh = ((short)this->MacroLayer[this->DAT_SomeTile] & 0xf000) >> 12;
                                        macroHigh = macroHigh & 3;
                                        rotation = (short)this->MacroLayer[this->DAT_SomeTile];
                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                            = (ushort)GMTotalPicturesProcessed::instance[9];

                                        if ((this->LogicLayer[this->DAT_SomeTile] & L_MARSH) != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_4(1, NEIGHBOUR_FLAGS_MASK_MARSH)
                                            gfxBaseA = 1;
                                            gfxBaseB = 3;
                                            gfxBaseC = 0x15;
                                            gfxBaseD = 0x21;
                                            gfxBaseE = 0x25;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_EARTH_AND_STONES)
                                            != 0) {
                                            height = this->HeightLayer[this->DAT_SomeTile];
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(2, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                                            gfxBaseA = 0x99;
                                            gfxBaseB = 0x9b;
                                            gfxBaseC = 0xad;
                                            gfxBaseD = 0xb9;
                                            gfxBaseE = 0xbd;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_OASIS_GRASS)
                                            != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(3, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                                            gfxBaseA = 0x1c9;
                                            gfxBaseB = 0x1cb;
                                            gfxBaseC = 0x1dd;
                                            gfxBaseD = 0x1e9;
                                            gfxBaseE = 0x1ed;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile]
                                                       & L2_STONES_OR_DRIVEN_SANDUnk)
                                            != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(4, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                                            gfxBaseA = 0x261;
                                            gfxBaseB = 0x263;
                                            gfxBaseC = 0x275;
                                            gfxBaseD = 0x281;
                                            gfxBaseE = 0x285;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_SCRUB) != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                            gfxBaseA = 0x2f9;
                                            gfxBaseB = 0x2fb;
                                            gfxBaseC = 0x30d;
                                            gfxBaseD = 0x319;
                                            gfxBaseE = 0x31d;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_THICK_SCRUB)
                                            != 0) {
                                            /* the original gathers L2_SCRUB here, not L2_THICK_SCRUB; kept as-is */
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(6, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                            gfxBaseA = 0x4a9;
                                            gfxBaseB = 0x4ab;
                                            gfxBaseC = 0x4bd;
                                            gfxBaseD = 0x4c9;
                                            gfxBaseE = 0x4cd;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_PLATEAU_MEDIUM)
                                            != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(7, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                                            gfxBaseA = 0x131;
                                            gfxBaseB = 0x133;
                                            gfxBaseC = 0x145;
                                            gfxBaseD = 0x151;
                                            gfxBaseE = 0x155;
                                            gfxStride = 4;
                                            gfxMode = 2;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_PLATEAU_HIGH)
                                            != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(8, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                                            gfxBaseA = 0x131;
                                            gfxBaseB = 0x133;
                                            gfxBaseC = 0x145;
                                            gfxBaseD = 0x151;
                                            gfxBaseE = 0x155;
                                            gfxStride = 4;
                                            gfxMode = 2;
                                        } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_BEACH) != 0) {
                                            MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(9, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                            savedBitFlag = this->bitFlag;
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_4(10, NEIGHBOUR_FLAGS_MASK_SEA)
                                            this->bitFlag = this->bitFlag | savedBitFlag;
                                            gfxBaseA = 0x391;
                                            gfxBaseB = 0x393;
                                            gfxBaseC = 0x3a5;
                                            gfxBaseD = 0x3b1;
                                            gfxBaseE = 0x3b5;
                                            gfxStride = 4;
                                            gfxMode = 0;
                                        } else {
                                            MACRO_NEIGHBOUR_FLAGS_LOGIC_4(11, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                                            gfxBaseA = 0x131;
                                            gfxBaseB = 0x133;
                                            gfxBaseC = 0x145;
                                            gfxBaseD = 0x151;
                                            gfxBaseE = 0x155;
                                            gfxStride = 4;
                                            gfxMode = 2;
                                        }

                                        if (macroLow == 1) {
                                            this->bitFlag = ~this->bitFlag;
                                            this->bitFlag = this->bitFlag & 0xaa;
                                            if (this->mapOrientation == 0) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 0);
                                            } else if (this->mapOrientation == 2) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 2);
                                            } else if (this->mapOrientation == 4) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 4);
                                            } else if (this->mapOrientation == 6) {
                                                this->bitFlag = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                        rotateByteLeft,
                                                    DAT_DirectionAlgorithmState::ptr)(this->bitFlag, 6);
                                            }

                                            if (gfxMode == 1) {
                                                this->GfxLayer[this->DAT_SomeTile] = 0;
                                                for (index = 0; index < 4; index++) {
                                                    if (DAT_TerrainDefinedData::instance.field2296_0x1d54[index][0]
                                                        == this->bitFlag) {
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = GMTotalPicturesProcessed::instance[55] + gfxBaseA
                                                            + (luminescence - 2) * gfxStride - 1
                                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 1)
                                                            + DAT_TerrainDefinedData::instance
                                                                  .field2296_0x1d54[index][1];
                                                    }
                                                }
                                                for (index = 4; index < 8; index++) {
                                                    if (DAT_TerrainDefinedData::instance.field2296_0x1d54[index][0]
                                                        == this->bitFlag) {
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = GMTotalPicturesProcessed::instance[55] + gfxBaseB
                                                            + (luminescence - 2) * gfxStride - 1
                                                            + DAT_TerrainDefinedData::instance
                                                                  .field2296_0x1d54[index][1];
                                                    }
                                                }
                                                if (this->GfxLayer[this->DAT_SomeTile] == 0) {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = GMTotalPicturesProcessed::instance[55] + gfxBaseC
                                                        + (luminescence - 2) * gfxStride - 1
                                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                                }
                                            } else if (luminescence == 2) {
                                                if (this->bitFlag != 0) {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = GMTotalPicturesProcessed::instance[55] + gfxBaseC
                                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = GMTotalPicturesProcessed::instance[55] + gfxBaseD
                                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                                }
                                            } else if (gfxMode == 2) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseA
                                                    + (luminescence - 3) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else if (this->bitFlag != 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseA
                                                    + (luminescence - 3) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseB
                                                    + (luminescence - 3) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                            }
                                        } else if (luminescence > 2) {
                                            if (gfxMode == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseB
                                                    + (luminescence - 3) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                            } else if (gfxMode == 2) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseA
                                                    + (luminescence - 3) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseD
                                                    + (luminescence - 2) * gfxStride - 1
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            }
                                        } else if (macroLow == 2) {
                                            if (gfxMode == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseD
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMTotalPicturesProcessed::instance[55] + gfxBaseD
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3) - 1;
                                            }
                                        } else if (macroLow == 4) {
                                            macroMid = DAT_TerrainDefinedData::instance
                                                           .field2293_0x1a54[this->mapOrientation / 2][macroMid];
                                            this->GfxLayer[this->DAT_SomeTile] = GMTotalPicturesProcessed::instance[55]
                                                + gfxBaseE + macroMid + macroHigh * 4 - 1;
                                        } else if (macroLow == 8) {
                                            macroMid = DAT_TerrainDefinedData::instance
                                                           .field2294_0x1b54[this->mapOrientation / 2][macroMid];
                                            this->GfxLayer[this->DAT_SomeTile] = macroHigh * 9
                                                + (GMTotalPicturesProcessed::instance[55] + gfxBaseE + macroMid) + 0xf;
                                        } else if (macroLow == 0x10) {
                                            macroMid = DAT_TerrainDefinedData::instance
                                                           .field2295_0x1c54[this->mapOrientation / 2][macroMid];
                                            this->GfxLayer[this->DAT_SomeTile] = macroHigh * 16
                                                + (GMTotalPicturesProcessed::instance[55] + gfxBaseE + macroMid) + 0x33;
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
}
}

#pragma optimize("", on)
