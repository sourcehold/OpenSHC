#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

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

// the three macro-tile offset tables are one int[3][4][16] array, one table per macro size 4, 8 and 16
#define MACRO_TILE_OFFSETS (*(int (*)[3][4][16]) & DAT_TerrainDefinedData::instance.field_0x1a54)

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC9E0
    void TileMapState::updateGFXLayers()
    {
        // Contains the handwritten neighbour-flag macro nine times (see NeighbourFlagsGlobalAsm.hpp), which
        // is why the surrounding code is unoptimised: MSVC disables optimisation in a function holding
        // inline asm, so every field access reloads this from the frame.
        //
        // One store below is dead in this function but present in the original, because the body is
        // shared with updateMacroLayerRelated: "elevation" is read from HeightLayer and never used.
        // The locals are declared here because the original was built without optimisation: its
        // stack slots are observable and MSVC assigns them per function, not per scope. Declaring
        // them at first use instead costs ~12 points of match (52.6% vs 64.5%).
        // At /Od MSVC lays the locals out by a hash of their NAME (16 buckets, walked in order;
        // inside one bucket the later declaration gets the higher slot), not by declaration order.
        // The names and their order below were chosen so the slots land where the original has them
        // (rotation at ebp-4 down to the gfx bases at ebp-0x4c); renaming any of them moves the slots.
        int rotation;
        int sectorColumn;
        int partIndex;
        int drawMode;
        int tileRow;
        int perLevel;
        int luminescence;
        int lowGfx;
        int sectorRow;
        int macroTop;
        int macroSizeType;
        int edgeBase;
        int tileColumn;
        int elevation;
        int macroBase;
        int priorBitFlag;
        int macroMid;
        int flatFrame;
        int cornerFrame;

        if (this->forceUpdateGFXLayers <= 0) {
            return;
        }
        this->forceUpdateGFXLayers--;

        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::getYSmallerThanYLimit,
                &DAT_PathFindingState::instance)()
            == FALSE) {
            return;
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
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_DEFAULT_EARTH_OR_TEXTURE) == 0) {
                                continue;
                            }
                            if (this->GfxLayer[this->DAT_SomeTile] != 0) {
                                continue;
                            }
                            luminescence = this->LuminesenceLayer[this->DAT_SomeTile];
                            if (luminescence < 2) {
                                luminescence = 2;
                            }
                            macroSizeType = this->MacroLayer[this->DAT_SomeTile] & 0x3f;
                            macroMid = (this->MacroLayer[this->DAT_SomeTile] & 0x7c0) >> 6;
                            macroTop = (this->MacroLayer[this->DAT_SomeTile] & 0xf000) >> 12;
                            macroTop &= 3;
                            this->PillarGFXLayer[this->DAT_SomeTile]
                                = *(int volatile*)&GMFirstPictureIndex::instance[9];

                            if ((this->LogicLayer[this->DAT_SomeTile] & L_MARSH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(1, NEIGHBOUR_FLAGS_MASK_MARSH)
                                edgeBase = 1;
                                cornerFrame = 3;
                                flatFrame = 21;
                                lowGfx = 33;
                                macroBase = 37;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_EARTH_AND_STONES) != 0) {
                                elevation = this->HeightLayer[this->DAT_SomeTile];
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(2, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                                edgeBase = 153;
                                cornerFrame = 155;
                                flatFrame = 173;
                                lowGfx = 185;
                                macroBase = 189;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_OASIS_GRASS) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(3, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                                edgeBase = 457;
                                cornerFrame = 459;
                                flatFrame = 477;
                                lowGfx = 489;
                                macroBase = 493;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_STONES_OR_DRIVEN_SANDUnk)
                                != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(4, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                                edgeBase = 609;
                                cornerFrame = 611;
                                flatFrame = 629;
                                lowGfx = 641;
                                macroBase = 645;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_SCRUB) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                edgeBase = 761;
                                cornerFrame = 763;
                                flatFrame = 781;
                                lowGfx = 793;
                                macroBase = 797;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_THICK_SCRUB) != 0) {
                                // the original gathers L2_SCRUB here, not L2_THICK_SCRUB; kept as-is
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(6, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                edgeBase = 1193;
                                cornerFrame = 1195;
                                flatFrame = 1213;
                                lowGfx = 1225;
                                macroBase = 1229;
                                perLevel = 4;
                                drawMode = 0;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_PLATEAU_MEDIUM) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(7, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                                edgeBase = 305;
                                cornerFrame = 307;
                                flatFrame = 325;
                                lowGfx = 337;
                                macroBase = 341;
                                perLevel = 4;
                                drawMode = 2;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_PLATEAU_HIGH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(8, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                                edgeBase = 305;
                                cornerFrame = 307;
                                flatFrame = 325;
                                lowGfx = 337;
                                macroBase = 341;
                                perLevel = 4;
                                drawMode = 2;
                            } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_BEACH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(9, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                priorBitFlag = this->bitFlag;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(10, NEIGHBOUR_FLAGS_MASK_SEA)
                                this->bitFlag = this->bitFlag | priorBitFlag;
                                edgeBase = 913;
                                cornerFrame = 915;
                                flatFrame = 933;
                                lowGfx = 945;
                                macroBase = 949;
                                perLevel = 4;
                                drawMode = 0;
                            } else {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(11, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                                edgeBase = 305;
                                cornerFrame = 307;
                                flatFrame = 325;
                                lowGfx = 337;
                                macroBase = 341;
                                perLevel = 4;
                                drawMode = 2;
                            }

                            if (macroSizeType == 1) {
                                this->bitFlag = ~this->bitFlag;
                                this->bitFlag &= 0xaa;
                                if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                                    this->bitFlag = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,
                                        &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 0);
                                } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                                    this->bitFlag = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,
                                        &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 2);
                                } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                    this->bitFlag = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,
                                        &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 4);
                                } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                    this->bitFlag = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,
                                        &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 6);
                                }

                                if (drawMode == 1) {
                                    this->GfxLayer[this->DAT_SomeTile] = 0;
                                    for (partIndex = 0; partIndex < 4; partIndex++) {
                                        if (DAT_TerrainDefinedData::instance.field_0x1d54[partIndex][0]
                                            == this->bitFlag) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55]
                                                + edgeBase + ((luminescence - 2) * perLevel - 1)
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 1)
                                                + DAT_TerrainDefinedData::instance.field_0x1d54[partIndex][1];
                                        }
                                    }
                                    for (partIndex = 4; partIndex < 8; partIndex++) {
                                        if (DAT_TerrainDefinedData::instance.field_0x1d54[partIndex][0]
                                            == this->bitFlag) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55]
                                                + cornerFrame + ((luminescence - 2) * perLevel - 1)
                                                + DAT_TerrainDefinedData::instance.field_0x1d54[partIndex][1];
                                        }
                                    }
                                    if (this->GfxLayer[this->DAT_SomeTile] == 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55]
                                            + flatFrame + ((luminescence - 2) * perLevel - 1)
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                    }
                                } else if (luminescence == 2) {
                                    if (this->bitFlag != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55]
                                            + flatFrame + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + lowGfx
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                    }
                                } else if (drawMode == 2) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + edgeBase
                                        + ((luminescence - 3) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                } else if (this->bitFlag != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + edgeBase
                                        + ((luminescence - 3) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + cornerFrame
                                        + ((luminescence - 3) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                }
                            } else if (luminescence > 2) {
                                if (drawMode == 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + cornerFrame
                                        + ((luminescence - 3) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 1);
                                } else if (drawMode == 2) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + edgeBase
                                        + ((luminescence - 3) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + lowGfx
                                        + ((luminescence - 2) * perLevel - 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                }
                            } else if (macroSizeType == 2) {
                                if (drawMode == 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + lowGfx
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + lowGfx
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3) - 1;
                                }
                            } else if (macroSizeType == 4) {
                                macroMid = MACRO_TILE_OFFSETS[0][this->mapOrientation / 2][macroMid];
                                this->GfxLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[55] + macroBase + macroMid + macroTop * 4 - 1;
                            } else if (macroSizeType == 8) {
                                macroMid = MACRO_TILE_OFFSETS[1][this->mapOrientation / 2][macroMid];
                                this->GfxLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[55] + macroBase + macroTop * 9 + macroMid + 15;
                            } else if (macroSizeType == 16) {
                                macroMid = MACRO_TILE_OFFSETS[2][this->mapOrientation / 2][macroMid];
                                this->GfxLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[55] + macroBase + macroTop * 16 + macroMid + 51;
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
