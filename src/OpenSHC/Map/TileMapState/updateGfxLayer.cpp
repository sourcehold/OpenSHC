#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Enums/MapOrientation.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

// The original's macro expansions read the global instance (NeighbourFlagsGlobalAsm.hpp), but here that
// measured 90.5% -> 89.8% (reccmp realigns the jump displacements of the now shorter body), so the this-based
// NeighbourFlagsAsm.hpp stays.
// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_RIVER 0x100000 // L_RIVER
#define NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD 0x300000 // L_RIVER | L_FORD
#define NEIGHBOUR_FLAGS_MASK_WALL_OR_GATEHOUSE 0x100 // L_WALL_OR_GATEHOUSE

// the original was optimised, but a jump from the handwritten asm to a C label (warning C4740) switches global
// optimisation off for the whole function: frame pointer, locals off ebp, sub esp, 0x118. The asm jump to
// wallAlpha below is that flow.

// the original indexes directionTranslationMatrix as one flat array of eight entries per row
#define DIRECTION_OFFSET(Y, DIRECTION) (this->directionTranslationMatrix[0][(Y) * 8 + (DIRECTION)])
// the original picks a sea-edge graphic from the rotated neighbour mask with this same switch twice
#define SEA_EDGE_PICK(MASK, OFFSET, MODULUS, COUNT, BIT)                                                               \
    switch (MASK) {                                                                                                    \
    case 0x80:                                                                                                         \
    case 0x81:                                                                                                         \
    case 0xc0:                                                                                                         \
    case 0xc1:                                                                                                         \
        OFFSET = 0;                                                                                                    \
        MODULUS = 4;                                                                                                   \
        break;                                                                                                         \
    case 0x20:                                                                                                         \
    case 0x30:                                                                                                         \
    case 0x60:                                                                                                         \
    case 0x70:                                                                                                         \
        OFFSET = 4;                                                                                                    \
        MODULUS = 4;                                                                                                   \
        break;                                                                                                         \
    case 0x08:                                                                                                         \
    case 0x0c:                                                                                                         \
    case 0x18:                                                                                                         \
    case 0x1c:                                                                                                         \
        OFFSET = 8;                                                                                                    \
        MODULUS = 4;                                                                                                   \
        break;                                                                                                         \
    case 0x02:                                                                                                         \
    case 0x03:                                                                                                         \
    case 0x06:                                                                                                         \
    case 0x07:                                                                                                         \
        OFFSET = 12;                                                                                                   \
        MODULUS = 4;                                                                                                   \
        break;                                                                                                         \
    case 0x83:                                                                                                         \
    case 0x87:                                                                                                         \
    case 0xc3:                                                                                                         \
    case 0xc7:                                                                                                         \
        OFFSET = 16;                                                                                                   \
        break;                                                                                                         \
    case 0xe0:                                                                                                         \
    case 0xe1:                                                                                                         \
    case 0xf0:                                                                                                         \
    case 0xf1:                                                                                                         \
        OFFSET = 18;                                                                                                   \
        break;                                                                                                         \
    case 0x38:                                                                                                         \
    case 0x3c:                                                                                                         \
    case 0x78:                                                                                                         \
    case 0x7c:                                                                                                         \
        OFFSET = 20;                                                                                                   \
        break;                                                                                                         \
    case 0x0e:                                                                                                         \
    case 0x0f:                                                                                                         \
    case 0x1e:                                                                                                         \
    case 0x1f:                                                                                                         \
        OFFSET = 22;                                                                                                   \
        break;                                                                                                         \
    case 0x10:                                                                                                         \
        OFFSET = 24;                                                                                                   \
        break;                                                                                                         \
    case 0x04:                                                                                                         \
        OFFSET = 26;                                                                                                   \
        break;                                                                                                         \
    case 0x01:                                                                                                         \
        OFFSET = 28;                                                                                                   \
        break;                                                                                                         \
    case 0x40:                                                                                                         \
        OFFSET = 30;                                                                                                   \
        break;                                                                                                         \
    default:                                                                                                           \
        COUNT = 0;                                                                                                     \
        for (BIT = 0; BIT < 8; BIT++) {                                                                                \
            if ((1 << BIT & MASK) != 0) {                                                                              \
                COUNT += 1;                                                                                            \
            }                                                                                                          \
        }                                                                                                              \
        if (COUNT < 4) {                                                                                               \
            OFFSET = 32;                                                                                               \
        } else {                                                                                                       \
            OFFSET = 33;                                                                                               \
        }                                                                                                              \
        MODULUS = 1;                                                                                                   \
    }

// rotate the gathered neighbour mask from map to screen orientation
#define ROTATE_BITFLAG_BY_ORIENTATION()                                                                                \
    if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {                                                       \
        this->bitFlag = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,      \
            &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 0);                                                 \
    } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {                                                 \
        this->bitFlag = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,      \
            &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 2);                                                 \
    } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {                                                \
        this->bitFlag = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,      \
            &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 4);                                                 \
    } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {                                                 \
        this->bitFlag = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,      \
            &DAT_DirectionAlgorithmState::instance)(this->bitFlag, 6);                                                 \
    }
#define MIN_OF(A, B) ((A) < (B) ? (A) : (B))
// the original always loads a GMFirstPictureIndex entry as a whole dword before narrowing it, which MSVC only
// does for a volatile read; a plain read of an int into a short is narrowed to a word load
#define GM_FIRST_PICTURE_INDEX(I) (*(int volatile*)&GMFirstPictureIndex::instance[I])

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_OIL;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x00509180
    void TileMapState::updateGfxLayer()
    {
        // The original keeps all of these at fixed frame offsets. MSVC lays out the locals of a function without global
        // optimisation by hash bucket of the name and then by declaration order, so every name here was picked to fall
        // into one bucket (hence the odd suffixes) and they are declared from the lowest slot up. Renaming one moves
        // the whole frame.
        int heightStepA;
        int rightAlphaTile;
        int leftAlphaTileRef;
        int moatTile6;
        int moatDirectionValue;
        int ditchIDCur;
        int tileHeightAt;
        int lowerTileIndex;
        int riverMaskA;
        int bankDirection;
        int bankBase_;
        int edgeBitId;
        int edgeBitsValue;
        int edgeOffsetId;
        int edgeModulusWork;
        int edgeMaskD;
        int pathBitValue;
        int pathBitsWork;
        int pathOffsetVal;
        int pathSymmetricNow;
        int pathModulusWork;
        int pathHighMaskCur;
        int pathLowPos;
        int seaMask_;
        int wallMaskId;
        int leftTile8;
        int rightTileCalc;
        int neighbourTilePos;
        int shallowMaskMain;
        int directionTmp;
        int diagonalHeightG;
        int firstTile3;
        int wallHeightIndex;
        int secondTileTmp;
        int secondHeightHere;
        int firstHeightVal;
        int diagonalTileTmp;
        int wallNeighboursIndex;
        int cornerBitsVal;
        int cornerMain;
        int buildingWasOffsetOld;
        int tileXTmp;
        int alphaBaseCur;
        int shadeLevelRef;
        int buildingIDTmp;
        int subColumnId;
        int rockIndexId;
        int cliffDropValue;
        int subRow2;
        int rampRotation;
        int facingTile;
        int blockRowVal;
        int local_14_f;
        int blockColumnRef;
        int rotationNew;
        int heightPicture_;
        alphaBaseCur = 0;
        if (this->forceUpdateTextureTilemap <= 0) {
            return;
        }
        this->forceUpdateTextureTilemap -= 1;
        rotationNew = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRowVal = this->someIndex; blockRowVal <= this->someLimit; blockRowVal++) {
            for (blockColumnRef = this->someYLike; blockColumnRef <= this->someYLikeLimit; blockColumnRef++) {
                if (DAT_TileMapState::instance.mapping40x40[blockRowVal][blockColumnRef] != 0) {
                    for (subRow2 = rotationNew, rotationNew = 0; subRow2 < 10; subRow2++) {
                        for (subColumnId = 0, this->DAT_SomeY = blockRowVal * 10 + subRow2,
                            this->DAT_SomeX = blockColumnRef * 10;
                            subColumnId < 10; subColumnId++, this->DAT_SomeX++) {
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
                            if ((short)this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                buildingIDTmp = (short)this->BuildingLayer[this->DAT_SomeTile];
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence, this)(
                                        this->DAT_SomeTile, this->DAT_SomeY);
                                }
                                continue;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence, this)(
                                this->DAT_SomeTile, this->DAT_SomeY);
                            tileXTmp = this->DAT_SomeX;
                            this->FloatingLayer[this->DAT_SomeTile] = 0;
                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & ~0x3c0;
                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & ~0x800;
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_RIVER) != 0) {
                                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileSuitableForBrushPlacement,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY)
                                    != FALSE) {
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = ((short)this->RandomLayer[this->DAT_SomeTile] & 0xf) + 35;
                                } else {
                                    this->PillarGFXLayer[this->DAT_SomeTile] = 32;
                                }
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 532;
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_FORD) != 0) {
                                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileSuitableForBrushPlacement,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY)
                                    != FALSE) {
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = ((short)this->RandomLayer[this->DAT_SomeTile] & 0xf) + 35;
                                } else {
                                    this->PillarGFXLayer[this->DAT_SomeTile] = 32;
                                }
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 668;
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_WHEAT) != 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                this->GfxLayer[this->DAT_SomeTile] = ((short)this->RandomLayer[this->DAT_SomeTile] & 3)
                                    + GMFirstPictureIndex::instance[14];
                                DAT_BuildingsState::instance.field_0x18e024 = 1;
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_HOP) != 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[14] + 37
                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 1) * 9;
                                DAT_BuildingsState::instance.field_0x18e024 = 1;
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & (L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY))
                                != 0) {
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile]
                                    & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                                    == 0
                                && this->BuildingWasLayer[this->DAT_SomeTile] != 0
                                && ((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x10) != 0) {
                                buildingWasOffsetOld = 0;
                                switch (this->BuildingWasLayer[this->DAT_SomeTile]) {
                                case OpenSHC::Map::Buildings::BT_BARRACKS:
                                case OpenSHC::Map::Buildings::BT_STOCKPILE:
                                case OpenSHC::Map::Buildings::BT_ARMORY:
                                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                                case OpenSHC::Map::Buildings::BT_CHAPEL:
                                case OpenSHC::Map::Buildings::BT_CHURCH:
                                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                                case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                                case OpenSHC::Map::Buildings::BT_STONEKEEP:
                                case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                                case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                                case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                                case OpenSHC::Map::Buildings::BT_WOODGATE2:
                                case OpenSHC::Map::Buildings::BT_SIGNPOST:
                                case OpenSHC::Map::Buildings::BT_TOWER1:
                                case OpenSHC::Map::Buildings::BT_TOWER2:
                                case OpenSHC::Map::Buildings::BT_TOWER3:
                                case OpenSHC::Map::Buildings::BT_TOWER4:
                                case OpenSHC::Map::Buildings::BT_TOWER5:
                                case OpenSHC::Map::Buildings::BT_UNKNOWN7:
                                case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                                    buildingWasOffsetOld = 12;
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x2000) != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[149]
                                        + (buildingWasOffsetOld + 1)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[149]
                                        + (buildingWasOffsetOld + 5)
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7) - 1;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_WALL_OR_GATEHOUSE) != 0) {
                                this->wallCornerRotation = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::computeWallCornerRenderRotation, this)(tileXTmp);
                                this->WallGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[10] + this->wallCornerRotation - 1;
                                if ((char)this->DamageLayer[this->DAT_SomeTile] != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 138
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                } else if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL) != 0) {
                                    if (MACRO_CALL_MEMBER(
                                            OpenSHC::Map::TileMapState_Func::isWallCornerForCardinalDirection, this)(
                                            this->DAT_SomeTile, this->DAT_SomeY, 0)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH
                                            || this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL_VARIATIONUnk) != 0) {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12]
                                                    + 124 + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12]
                                                    + 116 + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            }
                                        } else if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL_VARIATIONUnk)
                                            != 0) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 120
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 112
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        }
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::isWallCornerForCardinalDirection,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 2)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH
                                            || this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL_VARIATIONUnk) != 0) {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12]
                                                    + 120 + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12]
                                                    + 112 + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            }
                                        } else if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL_VARIATIONUnk)
                                            != 0) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 124
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 116
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        }
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::isWallCornerForDiagonalDirection,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 1)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 130;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 129;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 128;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 131;
                                        }
                                        this->LogicLayer[this->DAT_SomeTile] |= L_CRENEL_VARIATIONUnk;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::isWallCornerForDiagonalDirection,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 3)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 131;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 130;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 129;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 128;
                                        }
                                        this->LogicLayer[this->DAT_SomeTile] |= L_CRENEL_VARIATIONUnk;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::isWallCornerForDiagonalDirection,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 5)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 128;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 131;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 130;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 129;
                                        }
                                        this->LogicLayer[this->DAT_SomeTile] |= L_CRENEL_VARIATIONUnk;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::isWallCornerForDiagonalDirection,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 7)
                                        != FALSE) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 129;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 128;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 131;
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[12] + 130;
                                        }
                                        this->LogicLayer[this->DAT_SomeTile] |= L_CRENEL_VARIATIONUnk;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 132;
                                        this->LogicLayer[this->DAT_SomeTile] |= L_CRENEL_VARIATIONUnk;
                                    }
                                } else if ((this->LogicLayer[this->DAT_SomeTile] & L_STAIRS) != 0) {
                                    if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::hasHigherNeighborWithStairs,
                                            this)(this->DAT_SomeTile, this->DAT_SomeY, 0)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 134;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::hasHigherNeighborWithStairs, this)(
                                                   this->DAT_SomeTile, this->DAT_SomeY, 2)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 135;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::hasHigherNeighborWithStairs, this)(
                                                   this->DAT_SomeTile, this->DAT_SomeY, 4)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 136;
                                    } else if (MACRO_CALL_MEMBER(
                                                   OpenSHC::Map::TileMapState_Func::hasHigherNeighborWithStairs, this)(
                                                   this->DAT_SomeTile, this->DAT_SomeY, 6)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 133;
                                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                     hasHigherPlainNeighborWithWallOrGatehouse,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 0)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 134;
                                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                     hasHigherPlainNeighborWithWallOrGatehouse,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 2)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 135;
                                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                     hasHigherPlainNeighborWithWallOrGatehouse,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 4)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 136;
                                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                     hasHigherPlainNeighborWithWallOrGatehouse,
                                                   this)(this->DAT_SomeTile, this->DAT_SomeY, 6)
                                        != FALSE) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 133;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 104;
                                    }
                                } else if (this->LuminesenceLayer[this->DAT_SomeTile] >= 4) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 104
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 96
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                }
                                continue;
                            } else if ((this->LogicLayer[this->DAT_SomeTile]
                                           & (L_SEA | L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING | L_BOULDERS
                                               | L_PEBBLES | L_IRON | L_RIVER | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP
                                               | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY | L_KEEP_NON_MANOR_HOUSE
                                               | L_MARSH | L_OIL))
                                == 0) {
                                cornerMain = 0;
                                this->WallOwnerLayer[this->DAT_SomeTile] &= ~8;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(wall, NEIGHBOUR_FLAGS_MASK_WALL_OR_GATEHOUSE)
                                wallNeighboursIndex = this->bitFlag;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(m1, 2)
                                wallNeighboursIndex = ~this->bitFlag & wallNeighboursIndex;
                                if (wallNeighboursIndex != 0) {
                                    cornerBitsVal = wallNeighboursIndex & 0xaa;
                                    switch (cornerBitsVal) {
                                    case 0x82:
                                        cornerMain = 3;
                                        if ((wallNeighboursIndex & 0x45) == 0x45) {
                                            cornerMain = 0;
                                        }
                                        break;
                                    case 0x0a:
                                        cornerMain = 2;
                                        if ((wallNeighboursIndex & 0x15) == 0x15) {
                                            cornerMain = 0;
                                        }
                                        break;
                                    case 0x28:
                                        cornerMain = 1;
                                        if ((wallNeighboursIndex & 0x54) == 0x54) {
                                            cornerMain = 0;
                                        }
                                        break;
                                    case 0xa0:
                                        cornerMain = 4;
                                        // the original compares the masked bits against 0x15, which they can never
                                        // equal, so this corner is never cleared here
                                        if ((wallNeighboursIndex & 0x41) == 0x15) {
                                            cornerMain = 0;
                                        }
                                    }
                                    if (cornerMain != 0) {
                                        MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(r1, 0x800)
                                        if (this->bitFlag != 0) {
                                            cornerMain = 0;
                                        }
                                    }
                                    if (cornerMain != 0) {
                                        // the corner picks its two cardinal neighbours and the diagonal between them
                                        switch (cornerMain) {
                                        case 1:
                                            firstTile3 = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 2);
                                            secondTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 4);
                                            diagonalTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 3);
                                            break;
                                        case 2:
                                            firstTile3 = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 6);
                                            secondTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 4);
                                            diagonalTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 5);
                                            break;
                                        case 3:
                                            firstTile3 = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 6);
                                            secondTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 0);
                                            diagonalTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 7);
                                            break;
                                        case 4:
                                            firstTile3 = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 2);
                                            secondTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 0);
                                            diagonalTileTmp = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, 1);
                                        }
                                        firstHeightVal = this->HeightLayer[firstTile3];
                                        secondHeightHere = this->HeightLayer[secondTileTmp];
                                        diagonalHeightG = this->HeightLayer[diagonalTileTmp];
                                        if ((DAT_TileMapState::instance.LogicLayer[diagonalTileTmp]
                                                & L_WALL_OR_GATEHOUSE)
                                            == 0) {
                                            diagonalHeightG = secondHeightHere;
                                        }
                                        wallHeightIndex
                                            = MIN_OF(MIN_OF(firstHeightVal, secondHeightHere), diagonalHeightG);
                                        if (this->HeightLayer[this->DAT_SomeTile] >= wallHeightIndex) {
                                            cornerMain = 0;
                                        } else {
                                            this->WallGFXLayer[this->DAT_SomeTile] = (byte)wallHeightIndex;
                                            if (DAT_TileMapState::instance.DamageLayer[firstTile3] != 0
                                                || DAT_TileMapState::instance.DamageLayer[secondTileTmp] != 0
                                                || (DAT_TileMapState::instance.DamageLayer[diagonalTileTmp] != 0
                                                    && (DAT_TileMapState::instance.LogicLayer[diagonalTileTmp]
                                                           & L_WALL_OR_GATEHOUSE)
                                                        != 0)) {
                                                this->WallOwnerLayer[this->DAT_SomeTile] |= 8;
                                            }
                                        }
                                    }
                                    if (cornerMain != 0) {
                                        cornerMain = ((cornerMain + 3) - this->mapOrientation / 2) % 4 + 1;
                                        switch (cornerMain) {
                                        case 1:
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x40;
                                            this->AlphaGFXLayer[this->DAT_SomeTile] = 47;
                                            break;
                                        case 2:
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x200;
                                            this->AlphaGFXLayer[this->DAT_SomeTile] = 46;
                                            break;
                                        case 3:
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x80;
                                            this->AlphaGFXLayer[this->DAT_SomeTile] = 49;
                                            break;
                                        case 4:
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x100;
                                            this->AlphaGFXLayer[this->DAT_SomeTile] = 48;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rotationNew = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRowVal = this->someIndex; blockRowVal <= this->someLimit; blockRowVal++) {
            for (blockColumnRef = this->someYLike; blockColumnRef <= this->someYLikeLimit; blockColumnRef++) {
                if (DAT_TileMapState::instance.mapping40x40[blockRowVal][blockColumnRef] != 0) {
                    for (subRow2 = rotationNew, rotationNew = 0; subRow2 < 10; subRow2++) {
                        for (subColumnId = 0, this->DAT_SomeY = blockRowVal * 10 + subRow2,
                            this->DAT_SomeX = blockColumnRef * 10;
                            subColumnId < 10; subColumnId++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if ((this->LogicLayer[this->DAT_SomeTile] & (L_SEA | L_CRENEL | L_RIVER)) == 0) {
                                continue;
                            }
                            if ((char)this->ChangedLayer[this->DAT_SomeTile] == 0) {
                                continue;
                            }
                            if ((short)this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile]
                                    & (L_BORDER | L_BORDER_EDGE | L_KEEP_NON_MANOR_HOUSE))
                                != 0) {
                                continue;
                            }
                            tileXTmp = this->DAT_SomeX;
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0xfffc;
                                facingTile
                                    = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, this->mapOrientation);
                                this->gfxTileHeight = this->HeightLayer[facingTile];
                                if ((this->LogicLayer[facingTile] & L_SEA) != 0) {
                                    this->gfxTileHeight = 0;
                                }
                                if ((this->LogicLayer[facingTile] & L_ROCKY) != 0) {
                                    this->gfxTileHeight = 20;
                                }
                                if ((short)this->gfxTileHeight >= 20) {
                                    if ((short)this->gfxTileHeight > 90) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166] + 1518;
                                    } else if ((short)this->gfxTileHeight > 40) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166] + 1506;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166] + 1500;
                                    }
                                    this->PillarGFXLayer[this->DAT_SomeTile] = GM_FIRST_PICTURE_INDEX(9);
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x40;
                                }
                                shallowMaskMain = 0;
                                this->bitFlag = 0;
                                for (directionTmp = 0; directionTmp < 8; directionTmp++) {
                                    neighbourTilePos
                                        = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, directionTmp);
                                    if (DAT_TileMapState::instance.HeightLayer[neighbourTilePos] < 20) {
                                        if ((this->LogicLayer[neighbourTilePos]
                                                & (L_SEA | L_BORDER | L_BORDER_EDGE | L_RIVER))
                                            == 0) {
                                            this->bitFlag |= 0x80 >> directionTmp;
                                        }
                                        if ((this->LogicLayer[neighbourTilePos] & (L_SEA | L_RIVER)) == 0
                                            && ((char)this->Logic2Layer[neighbourTilePos] & 0x20) != 0) {
                                            shallowMaskMain = 0x80 >> directionTmp | shallowMaskMain;
                                        }
                                    }
                                }
                                if (this->bitFlag != 0) {
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x100;
                                    this->CertainPathLayer[this->DAT_SomeTile] = this->bitFlag | shallowMaskMain << 8;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_RIVER) != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileCliffEdgeFlags, this)(
                                    this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_CRENEL) != 0) {
                                leftTile8 = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 7) % 8);
                                rightTileCalc = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 1) % 8);
                                if (((this->LogicLayer[leftTile8] | this->LogicLayer[rightTileCalc]) & L_SEA) == 0
                                    && ((short)this->MiscDisplayLayer[leftTile8] & 0x3c0) != 0
                                    && ((short)this->MiscDisplayLayer[rightTileCalc] & 0x3c0) != 0) {
                                    if (this->LuminesenceLayer[this->DAT_SomeTile] >= 4) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 104
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 96
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                    }
                                }
                                leftTile8 = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 1) % 8);
                                rightTileCalc = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 3) % 8);
                                if (((this->LogicLayer[leftTile8] | this->LogicLayer[rightTileCalc]) & L_SEA) == 0
                                    && ((short)this->MiscDisplayLayer[leftTile8] & 0x3c0) != 0
                                    && ((short)this->MiscDisplayLayer[rightTileCalc] & 0x3c0) != 0) {
                                    if ((this->DAT_SomeY & 1) != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 311;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 312;
                                    }
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                }
                                leftTile8 = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 5) % 8);
                                rightTileCalc = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 7) % 8);
                                if (((this->LogicLayer[leftTile8] | this->LogicLayer[rightTileCalc]) & L_SEA) == 0
                                    && ((short)this->MiscDisplayLayer[leftTile8] & 0x3c0) != 0
                                    && ((short)this->MiscDisplayLayer[rightTileCalc] & 0x3c0) != 0) {
                                    if ((this->DAT_SomeY & 1) != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 313;
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[12] + 314;
                                    }
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                }
                                leftTile8 = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 3) % 8);
                                rightTileCalc = this->DAT_SomeTile
                                    + DIRECTION_OFFSET(this->DAT_SomeY, (this->screenSouthEastDirection + 5) % 8);
                                if (((this->LogicLayer[leftTile8] | this->LogicLayer[rightTileCalc]) & L_SEA) == 0
                                    && ((short)this->MiscDisplayLayer[leftTile8] & 0x3c0) != 0
                                    && ((short)this->MiscDisplayLayer[rightTileCalc] & 0x3c0) != 0) {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[12] + 303 + this->DAT_SomeY % 8;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                }
                            }
                        }
                    }
                }
            }
        }
        rotationNew = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRowVal = this->someIndex; blockRowVal <= this->someLimit; blockRowVal++) {
            for (blockColumnRef = this->someYLike; blockColumnRef <= this->someYLikeLimit; blockColumnRef++) {
                if (DAT_TileMapState::instance.mapping40x40[blockRowVal][blockColumnRef] != 0) {
                    for (subRow2 = rotationNew, rotationNew = 0; subRow2 < 10; subRow2++) {
                        for (subColumnId = 0, this->DAT_SomeY = blockRowVal * 10 + subRow2,
                            this->DAT_SomeX = blockColumnRef * 10;
                            subColumnId < 10; subColumnId++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_SEA) == 0) {
                                continue;
                            }
                            if ((char)this->ChangedLayer[this->DAT_SomeTile] == 0) {
                                continue;
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile]
                                    & (L_BORDER | L_BORDER_EDGE | L_KEEP_NON_MANOR_HOUSE))
                                != 0) {
                                continue;
                            }
                            if ((short)this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                continue;
                            }
                            if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x40) != 0) {
                            } else {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(m2, 0x80)
                                wallMaskId = this->bitFlag;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(m3, 0x40)
                                this->bitFlag &= ~wallMaskId;
                                this->bitFlag &= 0xe3;
                                if (this->bitFlag != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166] + 1488;
                                    this->PillarGFXLayer[this->DAT_SomeTile] = GM_FIRST_PICTURE_INDEX(9);
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x80;
                                }
                            }
                        }
                    }
                }
            }
        }
        rotationNew = DAT_PathFindingState::instance.mappingYRelated % 10;
        for (blockRowVal = this->someIndex; blockRowVal <= this->someLimit; blockRowVal++) {
            for (blockColumnRef = this->someYLike; blockColumnRef <= this->someYLikeLimit; blockColumnRef++) {
                if (DAT_TileMapState::instance.mapping40x40[blockRowVal][blockColumnRef] != 0) {
                    for (subRow2 = rotationNew, rotationNew = 0; subRow2 < 10; subRow2++) {
                        for (subColumnId = 0, this->DAT_SomeY = blockRowVal * 10 + subRow2,
                            this->DAT_SomeX = blockColumnRef * 10;
                            subColumnId < 10; subColumnId++, this->DAT_SomeX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY)
                                == FALSE) {
                                continue;
                            }
                            this->DAT_SomeTile
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->DAT_SomeX, this->DAT_SomeY);
                            if ((this->LogicLayer[this->DAT_SomeTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                                continue;
                            }
                            if ((char)this->ChangedLayer[this->DAT_SomeTile] == 0) {
                                continue;
                            }
                            this->ChangedLayer[this->DAT_SomeTile] = (char)this->ChangedLayer[this->DAT_SomeTile] - 1;
                            tileXTmp = this->DAT_SomeX;
                            if ((this->LogicLayer[this->DAT_SomeTile] & L_SEA) != 0) {
                                this->Logic2Layer[this->DAT_SomeTile]
                                    = (char)this->Logic2Layer[this->DAT_SomeTile] & ~8;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(sea1, NEIGHBOUR_FLAGS_MASK_RIVER)
                                if (this->bitFlag != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 764;
                                    this->Logic2Layer[this->DAT_SomeTile]
                                        = (char)this->Logic2Layer[this->DAT_SomeTile] | 8;
                                    continue;
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0) != 0) {
                                } else {
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(sea2, 0x40)
                                    seaMask_ = this->bitFlag;
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(sea3, 0x80)
                                    this->bitFlag &= ~seaMask_;
                                    this->bitFlag &= 0xe3;
                                    if (this->bitFlag != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166] + 1476;
                                        this->PillarGFXLayer[this->DAT_SomeTile] = GM_FIRST_PICTURE_INDEX(9);
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0xc0;
                                    }
                                }
                                if (this->LuminesenceLayer[this->DAT_SomeTile] > 2) {
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & ~0x40;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & ~0x80;
                                }
                                shadeLevelRef = this->LuminesenceLayer[this->DAT_SomeTile] - 2;
                                if (shadeLevelRef < 0) {
                                    shadeLevelRef = 0;
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0) != 0) {
                                } else if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x100) != 0) {
                                    pathModulusWork = 2;
                                    pathLowPos = this->CertainPathLayer[this->DAT_SomeTile] & 0xff;
                                    pathHighMaskCur = this->CertainPathLayer[this->DAT_SomeTile] >> 8 & 0xff;
                                    pathSymmetricNow = 0;
                                    if (pathLowPos == pathHighMaskCur) {
                                        pathSymmetricNow = 1;
                                    }
                                    pathLowPos <<= DAT_TileMapState::instance.mapOrientation;
                                    pathLowPos = pathLowPos & 0xff | pathLowPos >> 8;
                                    SEA_EDGE_PICK(
                                        pathLowPos, pathOffsetVal, pathModulusWork, pathBitsWork, pathBitValue)
                                    pathOffsetVal
                                        = this->RandomLayer[this->DAT_SomeTile] % pathModulusWork + pathOffsetVal;
                                    if (pathSymmetricNow == 0) {
                                        pathOffsetVal += 102;
                                    }
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166]
                                        + (pathOffsetVal + 43) + shadeLevelRef * 246 - 1;
                                } else {
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(sea4, 0x100)
                                    if (this->bitFlag != 0) {
                                        edgeModulusWork = 2;
                                        edgeMaskD = this->bitFlag;
                                        edgeMaskD <<= DAT_TileMapState::instance.mapOrientation;
                                        edgeMaskD = edgeMaskD & 0xff | edgeMaskD >> 8;
                                        SEA_EDGE_PICK(
                                            edgeMaskD, edgeOffsetId, edgeModulusWork, edgeBitsValue, edgeBitId)
                                        edgeOffsetId
                                            = this->RandomLayer[this->DAT_SomeTile] % edgeModulusWork + edgeOffsetId;
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[166]
                                            + (edgeOffsetId + 9) + shadeLevelRef * 246 - 1;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x200;
                                    }
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x3c0) == 0) {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = ((short)this->RandomLayer[this->DAT_SomeTile] & 7)
                                        + GMFirstPictureIndex::instance[166] + shadeLevelRef * 246;
                                    this->PillarGFXLayer[this->DAT_SomeTile] = GM_FIRST_PICTURE_INDEX(9);
                                }
                                continue;
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_RIVER) != 0) {
                                this->Logic2Layer[this->DAT_SomeTile]
                                    = (char)this->Logic2Layer[this->DAT_SomeTile] & ~8;
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(riv1, 1)
                                if (this->bitFlag != 0) {
                                    this->Logic2Layer[this->DAT_SomeTile]
                                        = (char)this->Logic2Layer[this->DAT_SomeTile] | 8;
                                    if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_BEACH) != 0) {
                                        this->Logic2Layer[this->DAT_SomeTile]
                                            = (char)this->Logic2Layer[this->DAT_SomeTile] & ~L2_BEACH;
                                        this->WallGFXLayer[this->DAT_SomeTile]
                                            = (short)this->RandomLayer[this->DAT_SomeTile] & 7;
                                    }
                                }
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(riv2, 0x100031)
                                this->bitFlag = ~this->bitFlag;
                                this->bitFlag &= 0xaa;
                                if (this->bitFlag == 0) {
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(riv3, 0x100031)
                                    this->bitFlag = ~this->bitFlag;
                                    this->bitFlag &= 0x55;
                                }
                                ROTATE_BITFLAG_BY_ORIENTATION()
                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::propagateCliffEdgeFlagFromNeighbor,
                                    this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                if ((char)this->Logic2Layer[this->DAT_SomeTile] == 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 532
                                        + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                    for (local_14_f = 0; local_14_f < 7; local_14_f++) {
                                        if (DAT_TerrainDefinedData::instance.TerrainFlagGraphicLookup[local_14_f].unk1
                                            == this->bitFlag) {
                                            MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(riv4, 0x200000)
                                            if (local_14_f < 4) {
                                                if (this->bitFlag == 0) {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = GMFirstPictureIndex::instance[5] + 564
                                                        + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                        + DAT_TerrainDefinedData::instance
                                                              .TerrainFlagGraphicLookup[local_14_f]
                                                              .unk2;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = GMFirstPictureIndex::instance[5] + 732
                                                        + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                        + DAT_TerrainDefinedData::instance
                                                              .TerrainFlagGraphicLookup[local_14_f]
                                                              .unk2;
                                                }
                                            } else if (this->bitFlag != 0) {
                                            } else if (local_14_f == 4) {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                                    + 596 + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else if (local_14_f == 5) {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                                    + 628 + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            } else if (local_14_f == 6) {
                                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                                    + 660 + this->LuminesenceLayer[this->DAT_SomeTile];
                                            }
                                            break;
                                        }
                                    }
                                }
                                if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_BEACH) != 0) {
                                    bankBase_ = (this->WallGFXLayer[this->DAT_SomeTile] & 8) * 8 + 909;
                                    switch (this->mapOrientation) {
                                    case OpenSHC::Map::Enums::MO_NORTH:
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                            + bankBase_ + ((this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0) >> 5) * 8
                                            - 1;
                                        break;
                                    case OpenSHC::Map::Enums::MO_EAST:
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                            + bankBase_
                                            + (((this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0) >> 5) - 2 & 7) * 8 - 1;
                                        break;
                                    case OpenSHC::Map::Enums::MO_SOUTH:
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                            + bankBase_
                                            + (((this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0) >> 5) - 4 & 7) * 8 - 1;
                                        break;
                                    default:
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5]
                                            + bankBase_
                                            + (((this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0) >> 5) - 6 & 7) * 8 - 1;
                                    }
                                }
                                if (((char)this->Logic2Layer[this->DAT_SomeTile]
                                        & (L2_OASIS_GRASS | L2_STONES_OR_DRIVEN_SANDUnk))
                                    != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 764;
                                } else if (((char)this->Logic2Layer[this->DAT_SomeTile]
                                               & (L2_PLATEAU_HIGH | L2_THICK_SCRUB))
                                    != 0) {
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(riv5, 1)
                                    riverMaskA = this->bitFlag;
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(riv6, 0x50)
                                    this->bitFlag = this->bitFlag | riverMaskA;
                                    bankDirection = -1;
                                    if (this->bitFlag != 0) {
                                        if ((this->bitFlag & 0x80) != 0) {
                                            if ((this->bitFlag & 0x20) != 0) {
                                                bankDirection = 5;
                                            } else if ((this->bitFlag & 2) != 0) {
                                                bankDirection = 3;
                                            } else if ((this->bitFlag & 0x41) == 0x41) {
                                                bankDirection = 4;
                                            } else {
                                                bankDirection = 4;
                                            }
                                        } else if ((this->bitFlag & 0x20) != 0) {
                                            if ((this->bitFlag & 8) != 0) {
                                                bankDirection = 7;
                                            } else if ((this->bitFlag & 0x80) != 0) {
                                                bankDirection = 5;
                                            } else if ((this->bitFlag & 0x50) == 0x50) {
                                                bankDirection = 6;
                                            } else {
                                                bankDirection = 6;
                                            }
                                        } else if ((this->bitFlag & 8) != 0) {
                                            if ((this->bitFlag & 2) != 0) {
                                                bankDirection = 1;
                                            } else if ((this->bitFlag & 0x20) != 0) {
                                                bankDirection = 7;
                                            } else if ((this->bitFlag & 0x14) == 0x14) {
                                                bankDirection = 0;
                                            } else {
                                                bankDirection = 0;
                                            }
                                        } else if ((this->bitFlag & 2) != 0) {
                                            if ((this->bitFlag & 0x80) != 0) {
                                                bankDirection = 3;
                                            } else if ((this->bitFlag & 8) != 0) {
                                                bankDirection = 1;
                                            } else if ((this->bitFlag & 5) == 5) {
                                                bankDirection = 2;
                                            } else {
                                                bankDirection = 2;
                                            }
                                        } else if (this->bitFlag == 0x40) {
                                            bankDirection = 5;
                                        } else if (this->bitFlag == 1) {
                                            bankDirection = 3;
                                        } else if (this->bitFlag == 4) {
                                            bankDirection = 1;
                                        } else if (this->bitFlag == 0x10) {
                                            bankDirection = 7;
                                        } else if (this->bitFlag == 0x41) {
                                            bankDirection = 4;
                                        } else if (this->bitFlag == 0x50) {
                                            bankDirection = 6;
                                        } else if (this->bitFlag == 0x14) {
                                            bankDirection = 0;
                                        } else if (this->bitFlag == 5) {
                                            bankDirection = 2;
                                        }
                                        if (bankDirection == -1) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 532
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = (char)this->Logic2Layer[this->DAT_SomeTile] & ~L2_THICK_SCRUB;
                                        } else {
                                            bankDirection = (bankDirection - this->mapOrientation + 8) % 8;
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = GMFirstPictureIndex::instance[5] + bankDirection * 16 + 780;
                                        }
                                    } else {
                                        MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(riv7, NEIGHBOUR_FLAGS_MASK_RIVER)
                                        if (this->bitFlag != 0) {
                                            tileHeightAt = this->HeightLayer[this->DAT_SomeTile];
                                            for (local_14_f = 0; local_14_f < 8; local_14_f++) {
                                                if ((this->bitFlag & 1 << local_14_f) != 0) {
                                                    lowerTileIndex = this->DAT_SomeTile
                                                        + DIRECTION_OFFSET(this->DAT_SomeY,
                                                            DAT_TerrainDefinedData::instance.field_0x370c[local_14_f]);
                                                    if (this->HeightLayer[lowerTileIndex] <= tileHeightAt) {
                                                        this->bitFlag &= ~(1 << local_14_f);
                                                    }
                                                }
                                            }
                                            if (this->bitFlag != 0) {
                                                if ((this->bitFlag & 0x80) != 0) {
                                                    if ((this->bitFlag & 0x20) != 0) {
                                                        bankDirection = 5;
                                                    } else if ((this->bitFlag & 2) != 0) {
                                                        bankDirection = 3;
                                                    } else if ((this->bitFlag & 0x41) == 0x41) {
                                                        bankDirection = 4;
                                                    } else {
                                                        bankDirection = 4;
                                                    }
                                                } else if ((this->bitFlag & 0x20) != 0) {
                                                    if ((this->bitFlag & 8) != 0) {
                                                        bankDirection = 7;
                                                    } else if ((this->bitFlag & 0x80) != 0) {
                                                        bankDirection = 5;
                                                    } else if ((this->bitFlag & 0x50) == 0x50) {
                                                        bankDirection = 6;
                                                    } else {
                                                        bankDirection = 6;
                                                    }
                                                } else if ((this->bitFlag & 8) != 0) {
                                                    if ((this->bitFlag & 2) != 0) {
                                                        bankDirection = 1;
                                                    } else if ((this->bitFlag & 0x20) != 0) {
                                                        bankDirection = 7;
                                                    } else if ((this->bitFlag & 0x14) == 0x14) {
                                                        bankDirection = 0;
                                                    } else {
                                                        bankDirection = 0;
                                                    }
                                                } else if ((this->bitFlag & 2) != 0) {
                                                    if ((this->bitFlag & 0x80) != 0) {
                                                        bankDirection = 3;
                                                    } else if ((this->bitFlag & 8) != 0) {
                                                        bankDirection = 1;
                                                    } else if ((this->bitFlag & 5) == 5) {
                                                        bankDirection = 2;
                                                    } else {
                                                        bankDirection = 2;
                                                    }
                                                } else if (this->bitFlag == 0x41) {
                                                    bankDirection = 4;
                                                } else if (this->bitFlag == 0x50) {
                                                    bankDirection = 6;
                                                } else if (this->bitFlag == 0x14) {
                                                    bankDirection = 0;
                                                } else if (this->bitFlag == 5) {
                                                    bankDirection = 2;
                                                } else if ((this->bitFlag & 0x40) != 0) {
                                                    bankDirection = 5;
                                                } else if ((this->bitFlag & 1) != 0) {
                                                    bankDirection = 3;
                                                } else if ((this->bitFlag & 4) != 0) {
                                                    bankDirection = 1;
                                                } else if ((this->bitFlag & 0x10) != 0) {
                                                    bankDirection = 7;
                                                }
                                                bankDirection = (bankDirection - this->mapOrientation + 8) % 8;
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = GMFirstPictureIndex::instance[5] + bankDirection * 16 + 780;
                                            }
                                        }
                                        if (bankDirection == -1) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 532
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = (char)this->Logic2Layer[this->DAT_SomeTile] & ~L2_THICK_SCRUB;
                                        }
                                    }
                                } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & 1) != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 1036;
                                } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & 2) != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 1044;
                                } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & 4) != 0) {
                                    this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 1052;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_FORD) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(ford1, NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD)
                                this->bitFlag = ~this->bitFlag;
                                this->bitFlag &= 0xaa;
                                if (this->bitFlag == 0) {
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(ford2, NEIGHBOUR_FLAGS_MASK_RIVER_OR_FORD)
                                    this->bitFlag = ~this->bitFlag;
                                    this->bitFlag &= 0x55;
                                }
                                ROTATE_BITFLAG_BY_ORIENTATION()
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 668
                                    + this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                for (local_14_f = 0; local_14_f < 7; local_14_f++) {
                                    if (DAT_TerrainDefinedData::instance.TerrainFlagGraphicLookup[local_14_f].unk1
                                        == this->bitFlag) {
                                        if (local_14_f < 4) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 564
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + DAT_TerrainDefinedData::instance.TerrainFlagGraphicLookup[local_14_f]
                                                      .unk2;
                                        } else if (local_14_f == 4) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 596
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else if (local_14_f == 5) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 628
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else if (local_14_f == 6) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 660
                                                + this->LuminesenceLayer[this->DAT_SomeTile];
                                        }
                                        break;
                                    }
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_PLAIN2_AND_PITCH) != 0) {
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] & ~0x2000;
                                ditchIDCur = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, this)(this->DAT_SomeTile);
                                if (ditchIDCur != 0) {
                                    if (this->pitchDitches[ditchIDCur].state < 2
                                        && MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isSameTeam,
                                               &DAT_GameState::instance)(this->pitchDitches[ditchIDCur].owner,
                                               DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                            == FALSE
                                        && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                                        if ((this->LogicLayer[this->DAT_SomeTile] & L_DEFAULT_EARTH_OR_TEXTURE) != 0) {
                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                            continue;
                                        } else {
                                            goto plainTerrain;
                                        }
                                    }
                                    rampRotation
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                            this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = (this->pitchDitches[ditchIDCur].rng & 7) + GMFirstPictureIndex::instance[140];
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x2000;
                                    if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x80) != 0) {
                                        __asm jmp wallAlpha
                                    }
                                    continue;
                                }
                                goto plainTerrain;
                            } else if ((short)this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                buildingIDTmp = (short)this->BuildingLayer[this->DAT_SomeTile];
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                    == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                                    this->wallCornerRotation = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::TileMapState_Func::computeWallCornerRenderRotation, this)(
                                        tileXTmp);
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[10] + this->wallCornerRotation - 1;
                                }
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                switch (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType) {
                                case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
                                case OpenSHC::Map::Buildings::BT_CATAPULT:
                                case OpenSHC::Map::Buildings::BT_TREBUCHET:
                                case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
                                case OpenSHC::Map::Buildings::BT_SIEGETOWER:
                                case OpenSHC::Map::Buildings::BT_SHIELD:
                                    if (rampRotation == 0) {
                                        heightPicture_ = (this->HeightLayer[this->DAT_SomeTile] / 8 - 1) * 64 + 1;
                                        this->PillarGFXLayer[this->DAT_SomeTile] = (heightPicture_ - 1) / 2
                                            + GMFirstPictureIndex::instance[3]
                                            + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        break;
                                    }
                                default:
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                }
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                        == OpenSHC::Map::Buildings::BT_KILLINGPIT
                                    && DAT_BuildingsState::instance.buildings[buildingIDTmp].state <= 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::isSameTeam,
                                           &DAT_GameState::instance)(
                                           DAT_BuildingsState::instance.buildings[buildingIDTmp].owner,
                                           DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                        == FALSE
                                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                                    if ((this->LogicLayer[this->DAT_SomeTile] & L_DEFAULT_EARTH_OR_TEXTURE) != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = 0;
                                        continue;
                                    }
                                    goto plainTerrain;
                                }
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                    == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
                                    goto plainTerrain;
                                }
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].currentTilePositionAdjusted
                                    != this->DAT_SomeTile) {
                                    continue;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, this)(
                                    buildingIDTmp);
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_KEEP_NON_MANOR_HOUSE) != 0) {
                                buildingIDTmp = (short)this->BuildingLayer[this->DAT_SomeTile];
                                if (DAT_BuildingsState::instance.buildings[buildingIDTmp].currentTilePositionAdjusted
                                    != this->DAT_SomeTile) {
                                    continue;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, this)(
                                    buildingIDTmp);
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_ROCKY) != 0
                                && (this->LogicLayer[this->DAT_SomeTile] & L_WALL_OR_GATEHOUSE) == 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                rockIndexId = this->OrganismLayer[this->DAT_SomeTile];
                                if (rockIndexId >= 2000) {
                                    rockIndexId -= 2000;
                                    if (DAT_LandscapeState::instance.rocks[rockIndexId].tile != this->DAT_SomeTile) {
                                        continue;
                                    }
                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyRockGraphicsToFootprint,
                                        this)(rockIndexId);
                                    continue;
                                }
                                this->wallCornerRotation = (short)this->RandomLayer[this->DAT_SomeTile] & 7;
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[56]
                                    + this->LuminesenceLayer[this->DAT_SomeTile] * 8 + this->wallCornerRotation;
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_BOULDERS) != 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                this->wallCornerRotation = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                if (this->LuminesenceLayer[this->DAT_SomeTile] >= 6) {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[12] + 80 + this->wallCornerRotation;
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[12] + 64 + this->wallCornerRotation;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_PEBBLES) != 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                this->wallCornerRotation = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                if (this->LuminesenceLayer[this->DAT_SomeTile] >= 6) {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[12] + 48 + this->wallCornerRotation;
                                } else {
                                    this->GfxLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[12] + 32 + this->wallCornerRotation;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_IRON) != 0) {
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                this->PillarGFXLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                    = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                this->wallCornerRotation = (short)this->RandomLayer[this->DAT_SomeTile] & 0xf;
                                this->GfxLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[12] + 238 + this->wallCornerRotation;
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_OIL) != 0) {
                                this->PillarGFXLayer[this->DAT_SomeTile] = GM_FIRST_PICTURE_INDEX(9);
                                this->wallCornerRotation = (short)this->RandomLayer[this->DAT_SomeTile] & 7;
                                this->GfxLayer[this->DAT_SomeTile]
                                    = GMFirstPictureIndex::instance[55] + 1064 + this->wallCornerRotation * 16;
                                if (this->wallCornerRotation == 0) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x1ff;
                                } else if (this->wallCornerRotation == 1) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x1ff;
                                } else if (this->wallCornerRotation == 2) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x7f;
                                } else if (this->wallCornerRotation == 3) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x7f;
                                } else if (this->wallCornerRotation == 4) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0xff;
                                } else if (this->wallCornerRotation == 5) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0xff;
                                } else if (this->wallCornerRotation == 6) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x7f;
                                } else if (this->wallCornerRotation == 7) {
                                    this->WallGFXLayer[this->DAT_SomeTile]
                                        = (this->RandomLayer[this->DAT_SomeTile] + this->DAT_SomeX + this->DAT_SomeY)
                                        & 0x7f;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile] & L_MOAT) != 0) {
                                this->bitFlag = 0;
                                for (moatDirectionValue = 0; moatDirectionValue < 8;
                                    moatDirectionValue = moatDirectionValue + 2) {
                                    moatTile6
                                        = this->DAT_SomeTile + DIRECTION_OFFSET(this->DAT_SomeY, moatDirectionValue);
                                    if ((this->LogicLayer[moatTile6] & L_MOAT) != 0) {
                                        this->bitFlag |= 0x80 >> moatDirectionValue;
                                    } else if ((short)this->BuildingLayer[moatTile6] != 0) {
                                        buildingIDTmp = (short)this->BuildingLayer[moatTile6];
                                        if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                                == OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                                            && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile,
                                                   this)(moatTile6)
                                                != 0) {
                                            this->bitFlag |= 0x80 >> moatDirectionValue;
                                        }
                                    }
                                }
                                this->bitFlag = ~this->bitFlag;
                                this->bitFlag &= 0xaa;
                                if (this->bitFlag == 0) {
                                    this->bitFlag = 0;
                                    for (moatDirectionValue = 1; moatDirectionValue < 8;
                                        moatDirectionValue = moatDirectionValue + 2) {
                                        moatTile6 = this->DAT_SomeTile
                                            + DIRECTION_OFFSET(this->DAT_SomeY, moatDirectionValue);
                                        if ((this->LogicLayer[moatTile6] & L_MOAT) != 0) {
                                            this->bitFlag |= 0x80 >> moatDirectionValue;
                                        } else if ((short)this->BuildingLayer[moatTile6] != 0) {
                                            buildingIDTmp = (short)this->BuildingLayer[moatTile6];
                                            if (DAT_BuildingsState::instance.buildings[buildingIDTmp].buildingType
                                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                                                && MACRO_CALL_MEMBER(
                                                       OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(
                                                       moatTile6)
                                                    != 0) {
                                                this->bitFlag |= 0x80 >> moatDirectionValue;
                                            }
                                        }
                                    }
                                    this->bitFlag = ~this->bitFlag;
                                    this->bitFlag &= 0x55;
                                }
                                ROTATE_BITFLAG_BY_ORIENTATION()
                                this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 204
                                    + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                    + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                for (local_14_f = 0; local_14_f < 7; local_14_f++) {
                                    if (DAT_TerrainDefinedData::instance.TerrainFlagGraphicLookup[local_14_f].unk1
                                        == this->bitFlag) {
                                        if (local_14_f < 4) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 236
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + DAT_TerrainDefinedData::instance.TerrainFlagGraphicLookup[local_14_f]
                                                      .unk2;
                                        } else if (local_14_f == 4) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 268
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else if (local_14_f == 5) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 300
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        } else if (local_14_f == 6) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[5] + 332
                                                + this->LuminesenceLayer[this->DAT_SomeTile];
                                        }
                                        break;
                                    }
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x80) != 0) {
                                    goto wallAlpha;
                                }
                            } else if ((this->LogicLayer[this->DAT_SomeTile]
                                           & (L_WALL_OR_GATEHOUSE | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP
                                               | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY))
                                    == 0
                                || (this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_APPLE) != 0) {
                                alphaBaseCur = 0;
                                if ((this->WallOwnerLayer[this->DAT_SomeTile] & 8) != 0) {
                                    alphaBaseCur = 45;
                                }
                                if (((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x80) != 0) {
                                // the original jumps here from the pitch-ditch and moat arms: its gotos show as a
                                // doubled jmp
                                wallAlpha:
                                    leftAlphaTileRef = this->DAT_SomeTile
                                        + DIRECTION_OFFSET(this->DAT_SomeY, (13 - this->mapOrientation) % 8);
                                    rightAlphaTile = this->DAT_SomeTile
                                        + DIRECTION_OFFSET(this->DAT_SomeY, (9 - this->mapOrientation) % 8);
                                    if (((short)this->MiscDisplayLayer[leftAlphaTileRef] & 0x80) != 0) {
                                        if (((short)this->MiscDisplayLayer[rightAlphaTile] & 0x80) != 0) {
                                            if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH
                                                || this->mapOrientation == OpenSHC::Map::Enums::MO_WEST) {
                                                this->AlphaGFXLayer[this->DAT_SomeTile]
                                                    = 0x3e - this->DAT_SomeY % 8 + alphaBaseCur;
                                            } else {
                                                this->AlphaGFXLayer[this->DAT_SomeTile]
                                                    = this->DAT_SomeY % 8 + alphaBaseCur + 55;
                                            }
                                        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH
                                            || this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->AlphaGFXLayer[this->DAT_SomeTile]
                                                = ((tileXTmp ^ this->DAT_SomeY) & 1) + alphaBaseCur + 53;
                                        } else {
                                            this->AlphaGFXLayer[this->DAT_SomeTile]
                                                = ((tileXTmp ^ this->DAT_SomeY) & 1) + alphaBaseCur + 51;
                                        }
                                    } else if (((short)this->MiscDisplayLayer[rightAlphaTile] & 0x80) != 0) {
                                        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH
                                            || this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                                            this->AlphaGFXLayer[this->DAT_SomeTile]
                                                = ((tileXTmp ^ this->DAT_SomeY) & 1) + alphaBaseCur + 51;
                                        } else {
                                            this->AlphaGFXLayer[this->DAT_SomeTile]
                                                = ((tileXTmp ^ this->DAT_SomeY) & 1) + alphaBaseCur + 53;
                                        }
                                    } else {
                                        this->AlphaGFXLayer[this->DAT_SomeTile] += (tileXTmp ^ this->DAT_SomeY) & 1;
                                    }
                                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(alpha, 0x200)
                                    if (this->bitFlag != 0) {
                                        switch (this->mapOrientation) {
                                        case OpenSHC::Map::Enums::MO_NORTH:
                                            if ((this->bitFlag & 0x82) == 0x82) {
                                                this->AlphaGFXLayer[this->DAT_SomeTile] += 14;
                                            }
                                            break;
                                        case OpenSHC::Map::Enums::MO_SOUTH:
                                            if ((this->bitFlag & 0x28) == 0x28) {
                                                this->AlphaGFXLayer[this->DAT_SomeTile] += 14;
                                            }
                                            break;
                                        case OpenSHC::Map::Enums::MO_WEST:
                                            if ((this->bitFlag & 0xa) == 0xa) {
                                                this->AlphaGFXLayer[this->DAT_SomeTile] += 14;
                                            }
                                            break;
                                        case OpenSHC::Map::Enums::MO_EAST:
                                            if ((this->bitFlag & 0xa0) == 0xa0) {
                                                this->AlphaGFXLayer[this->DAT_SomeTile] += 14;
                                            }
                                        }
                                    }
                                    if ((this->LogicLayer[this->DAT_SomeTile] & (L_MOAT | L_PLAIN2_AND_PITCH)) == 0) {
                                        goto plainTerrain;
                                    }
                                } else if ((this->LogicLayer[this->DAT_SomeTile]
                                               & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                                        == 0
                                    && this->BuildingWasLayer[this->DAT_SomeTile] != 0
                                    && ((short)this->MiscDisplayLayer[this->DAT_SomeTile] & 0x10) != 0) {
                                } else {
                                // the plain terrain graphic; the original jumps here with goto from several arms above
                                plainTerrain:
                                    heightStepA = (this->HeightLayer[this->DAT_SomeTile] / 8 - 1) % 16;
                                    heightPicture_ = heightStepA * 64 + 1;
                                    rampRotation
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                            this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                    if (this->HeightLayer[this->DAT_SomeTile] >= 136 || rampRotation != 0) {
                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                            = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                        cliffDropValue = 1;
                                    } else {
                                        if (heightPicture_ <= 0) {
                                            heightPicture_ = 1;
                                        }
                                        this->PillarGFXLayer[this->DAT_SomeTile] = (heightPicture_ - 1) / 2
                                            + GMFirstPictureIndex::instance[3]
                                            + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isCliffDropInDirection,
                                                this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY)
                                            != 0) {
                                            cliffDropValue = 1;
                                        } else {
                                            cliffDropValue = 0;
                                        }
                                    }
                                    heightPicture_ = (this->HeightLayer[this->DAT_SomeTile] / 8 - 1) * 32 + 1;
                                    if (((char)this->Logic2Layer[this->DAT_SomeTile] & L2_BEACH) != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = 0;
                                    } else if (this->HeightLayer[this->DAT_SomeTile] < 8) {
                                        if (((char)this->Logic2Layer[this->DAT_SomeTile] & 2) != 0) {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[55] + 180
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                        } else {
                                            this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[2]
                                                + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                        }
                                    } else if ((this->LogicLayer[this->DAT_SomeTile] & L_DEFAULT_EARTH_OR_TEXTURE)
                                        != 0) {
                                        this->GfxLayer[this->DAT_SomeTile] = 0;
                                    } else if (cliffDropValue != 0
                                        && DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                                        this->LogicLayer[this->DAT_SomeTile] |= L_ROCKY;
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[56]
                                            + this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 7);
                                    } else {
                                        this->GfxLayer[this->DAT_SomeTile] = GMFirstPictureIndex::instance[2]
                                            + heightPicture_ + (this->LuminesenceLayer[this->DAT_SomeTile] * 4 - 1)
                                            + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
                                    }
                                }
                            }
                            if ((this->LogicLayer[this->DAT_SomeTile] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE))
                                != 0) {
                                heightPicture_ = (this->DefaultHeightLayer[this->DAT_SomeTile] / 8 - 1) * 64 + 1;
                                rampRotation
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                        this)(this->DAT_SomeTile, tileXTmp, this->DAT_SomeY);
                                if (this->DefaultHeightLayer[this->DAT_SomeTile] >= 136) {
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                } else if (rampRotation != 0) {
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                } else if (((char)this->Logic2Layer[this->DAT_SomeTile] & 2) != 0) {
                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                        = GMFirstPictureIndex::instance[9] + this->wallCornerRotation - 1;
                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                        = (short)this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                } else {
                                    this->PillarGFXLayer[this->DAT_SomeTile] = (heightPicture_ - 1) / 2
                                        + GMFirstPictureIndex::instance[3]
                                        + this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                        + ((short)this->RandomLayer[this->DAT_SomeTile] & 3);
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
