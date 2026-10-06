
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/TileMapState/GfxNeighbourMaskAsm.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

/* the original was built without optimisation: frame pointer, locals off ebp, sub esp, 0x118 */
#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
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
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Restarted to delay deadcode elimination for space: ram
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00509180
    void TileMapState::updateGfxLayer()
    {
        /* the locals MACRO_GFX_NEIGHBOUR_MASK reaches the layers through, see GfxNeighbourMaskAsm.hpp */
        char* _gfxLayer;
        char* _gfxDirMatrix;
        int _gfxTile;
        int _gfxY;
        uchar* _gfxBitFlag = &this->bitFlag;

        OpenSHC::Map::Buildings::BuildingTypeShort BVar1;
        ushort uVar2;
        ushort uVar3;
        short sVar4;
        short sVar5;
        byte bVar6;
        byte bVar7;
        int sVar8;
        bool bVar10;
        int bVar9;
        BOOLEnum BVar11;
        uint uVar12;
        int iVar13;
        int iVar14;
        uint uVar15;
        byte bVar16;
        int iVar17;
        uint* puVar18;
        byte bVar19;
        int local_d4;
        uint local_c0;
        int local_b8;
        int local_b4;
        short local_b0;
        int local_ac;
        int local_a4;
        int local_a0;
        short local_9c;
        int local_94;
        uint local_74;
        int local_70;
        int local_68;
        int local_60;
        int local_54;
        uint local_48;
        short local_44;
        int local_38;
        int local_30;
        int local_24;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        sVar8 = 0;
        if (0 < this->forceUpdateTextureTilemap) {
            this->forceUpdateTextureTilemap = this->forceUpdateTextureTilemap + -1;
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                bVar9 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if ((bVar9 != 0)
                                    && (this->DAT_SomeTile = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                            DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                        this->ChangedLayer[this->DAT_SomeTile] != 0)) {
                                    if (this->BuildingLayer[this->DAT_SomeTile] == 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->DAT_SomeTile, this->DAT_SomeY);
                                        iVar17 = this->DAT_SomeX;
                                        this->FloatingLayer[this->DAT_SomeTile] = 0;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xfc3f;
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xf7ff;
                                        if ((this->LogicLayer[this->DAT_SomeTile] & L_RIVER) == 0) {
                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_FORD) == 0) {
                                                if ((this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_WHEAT) == 0) {
                                                    if ((this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_HOP)
                                                        == 0) {
                                                        if ((this->LogicLayer[this->DAT_SomeTile] & L_FARM_FIELD_APPLE
                                                                | L_FARM_FIELD_DAIRY)
                                                            == 0) {
                                                            if ((((this->LogicLayer[this->DAT_SomeTile]
                                                                          & L_WALL_OR_GATEHOUSE
                                                                      | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)
                                                                     == 0)
                                                                    && (this->BuildingWasLayer[this->DAT_SomeTile]
                                                                        != '\0'))
                                                                && ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x10)
                                                                    != 0)) {
                                                                local_44 = 0;
                                                                switch (this->BuildingWasLayer[this->DAT_SomeTile]) {
                                                                case '\t':
                                                                case '\n':
                                                                case '\v':
                                                                case '\x18':
                                                                case '\x19':
                                                                case '$':
                                                                case '%':
                                                                case '&':
                                                                case '(':
                                                                case ')':
                                                                case '*':
                                                                case '+':
                                                                case ',':
                                                                case '-':
                                                                case '.':
                                                                case '0':
                                                                case '4':
                                                                case 'J':
                                                                case 'K':
                                                                case 'L':
                                                                case 'M':
                                                                case 'N':
                                                                case 'Z':
                                                                case 'j':
                                                                    local_44 = 0xc;
                                                                }
                                                                if ((this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        & 0x2000)
                                                                    == 0) {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)
                                                                              GMTotalPicturesProcessed::instance[0x95]
                                                                        + local_44 + 4
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)
                                                                              GMTotalPicturesProcessed::instance[0x95]
                                                                        + local_44
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                }
                                                            } else if ((this->LogicLayer[this->DAT_SomeTile]
                                                                           & L_WALL_OR_GATEHOUSE)
                                                                == 0) {
                                                                if ((this->LogicLayer[this->DAT_SomeTile] & L_SEA
                                                                        | L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING
                                                                        | L_BOULDERS | L_PEBBLES | L_IRON | L_RIVER
                                                                        | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP
                                                                        | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY
                                                                        | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_OIL)
                                                                    == 0) {
                                                                    local_48 = 0;
                                                                    this->WallOwnerLayer[this->DAT_SomeTile]
                                                                        = this->WallOwnerLayer[this->DAT_SomeTile]
                                                                        & 0xf7;
                                                                    _gfxLayer = (char*)this->ptr_LogicLayer;
                                                                    _gfxDirMatrix = (char*)this->ptr_MovementDirectionTranslationMatrix;
                                                                    _gfxTile = this->DAT_SomeTile;
                                                                    _gfxY = this->DAT_SomeY;
                                                                    MACRO_GFX_NEIGHBOUR_MASK(wall, 4, MACRO_GFX_SHIFT_4, MACRO_GFX_ROWSTEP_4, L_WALL_OR_GATEHOUSE)
                                                                    bVar19 = this->bitFlag;
                                                                                                                                        _gfxLayer = (char*)this->ptr_LogicLayer;
                                                                    _gfxTile = this->DAT_SomeTile;
                                                                    _gfxY = this->DAT_SomeY;
                                                                    MACRO_GFX_NEIGHBOUR_MASK(m1, 4, MACRO_GFX_SHIFT_4, MACRO_GFX_ROWSTEP_4, 2)
                                                                    bVar19 = ~this->bitFlag & bVar19;
                                                                    if (bVar19 != 0) {
                                                                        switch (bVar19 & 0xaa) {
                                                                        case 10:
                                                                            local_48 = 2;
                                                                            if ((bVar19 & 0x15) == 0x15) {
                                                                                local_48 = 0;
                                                                            }
                                                                            break;
                                                                        case 0x28:
                                                                            local_48 = (uint)((bVar19 & 0x54) != 0x54);
                                                                            break;
                                                                        case 0x82:
                                                                            local_48 = 3;
                                                                            if ((bVar19 & 0x45) == 0x45) {
                                                                                local_48 = 0;
                                                                            }
                                                                            break;
                                                                        case 0xa0:
                                                                            local_48 = 4;
                                                                            if ((bVar19 & 0x41) == 0x15) {
                                                                                local_48 = 0;
                                                                            }
                                                                        }
                                                                        if (local_48 != 0) {
                                                                            this->bitFlag = 0;
                                                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                                     + this->DAT_SomeTile * 4 + 4)
                                                                                    & 0x800)
                                                                                != 0) {
                                                                                this->bitFlag = 0x20;
                                                                            }
                                                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                                     + this->DAT_SomeTile * 4 + -4)
                                                                                    & 0x800)
                                                                                != 0) {
                                                                                this->bitFlag = this->bitFlag | 2;
                                                                            }
                                                                            puVar18 = (uint*)((char*)this
                                                                                                  ->ptr_LogicLayer
                                                                                + *(int*)((char*)this
                                                                                              ->ptr_MovementDirectionTranslationMatrix
                                                                                      + this->DAT_SomeY * 0x20)
                                                                                    * 4
                                                                                + this->DAT_SomeTile * 4);
                                                                            if ((puVar18[-1] & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 1;
                                                                            }
                                                                            if ((puVar18[1] & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 0x40;
                                                                            }
                                                                            if ((*puVar18 & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 0x80;
                                                                            }
                                                                            puVar18 = (uint*)((char*)this
                                                                                                  ->ptr_LogicLayer
                                                                                + *(int*)((int)((char*)this
                                                                                                    ->ptr_MovementDirectionTranslationMatrix
                                                                                              + this->DAT_SomeY * 0x20)
                                                                                      + 0x10)
                                                                                    * 4
                                                                                + this->DAT_SomeTile * 4);
                                                                            if ((puVar18[-1] & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 4;
                                                                            }
                                                                            if ((puVar18[1] & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 0x10;
                                                                            }
                                                                            if ((*puVar18 & L_STAIRS) != 0) {
                                                                                this->bitFlag = this->bitFlag | 8;
                                                                            }
                                                                            if (this->bitFlag != 0) {
                                                                                local_48 = 0;
                                                                            }
                                                                        }
                                                                        if (local_48 != 0) {
                                                                            /* the corner picks its two cardinal
                                                                               neighbours and the diagonal between them
                                                                               (the decompiler lost these four arms:
                                                                               they are the jump table at 0x00510d94) */
                                                                            switch (local_48) {
                                                                            case 1:
                                                                                local_68 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][2];
                                                                                local_60 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][4];
                                                                                local_54 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][3];
                                                                                break;
                                                                            case 2:
                                                                                local_68 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][6];
                                                                                local_60 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][4];
                                                                                local_54 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][5];
                                                                                break;
                                                                            case 3:
                                                                                local_68 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][6];
                                                                                local_60 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][0];
                                                                                local_54 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][7];
                                                                                break;
                                                                            case 4:
                                                                                local_68 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][2];
                                                                                local_60 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][0];
                                                                                local_54 = this->DAT_SomeTile
                                                                                    + this->directionTranslationMatrix
                                                                                          [this->DAT_SomeY][1];
                                                                                break;
                                                                            }
                                                                            bVar19 = this->HeightLayer[local_68];
                                                                            bVar16 = this->HeightLayer[local_60];
                                                                            bVar7 = this->HeightLayer[local_54];
                                                                            if ((this->LogicLayer[local_54] & 0x100U)
                                                                                == 0) {
                                                                                bVar7 = bVar16;
                                                                            }
                                                                            bVar6 = bVar16;
                                                                            if (bVar19 < bVar16) {
                                                                                bVar6 = bVar19;
                                                                            }
                                                                            if ((bVar6 < bVar7)
                                                                                && (bVar7 = bVar16, bVar19 < bVar16)) {
                                                                                bVar7 = bVar19;
                                                                            }
                                                                            if (this->HeightLayer[this->DAT_SomeTile]
                                                                                < bVar7) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = (ushort)bVar7;
                                                                                if (((this->DamageLayer[local_68] != 0)
                                                                                        || (this->DamageLayer[local_60]
                                                                                            != 0))
                                                                                    || ((
                                                                                        this->DamageLayer[local_54] != 0
                                                                                        && ((this->LogicLayer[local_54]
                                                                                                & 0x100U)
                                                                                            != 0)))) {
                                                                                    this->WallOwnerLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->WallOwnerLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 8;
                                                                                }
                                                                            } else {
                                                                                local_48 = 0;
                                                                            }
                                                                            if (local_48 != 0) {
                                                                                uVar12 = ((local_48 + 3)
                                                                                             - this->mapOrientation / 2)
                                                                                    % 4;
                                                                                switch (uVar12) {
                                                                                case 0:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x40;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x2f;
                                                                                    break;
                                                                                case 1:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x200;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x2e;
                                                                                    break;
                                                                                case 2:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x80;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x31;
                                                                                    break;
                                                                                case 3:
                                                                                    this->MiscDisplayLayer[this
                                                                                            ->DAT_SomeTile]
                                                                                        = this->MiscDisplayLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x100;
                                                                                    this->AlphaGFXLayer[this
                                                                                            ->DAT_SomeTile] = 0x30;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                this->field112_0x554908 = MACRO_CALL_MEMBER(
                                                                    OpenSHC::Map::TileMapState_Func::
                                                                        computeWallCornerRenderRotation,
                                                                    this)(iVar17);
                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[10] + -1
                                                                    + (short)this->field112_0x554908;
                                                                sVar4 = (short)GMTotalPicturesProcessed::instance[0xc];
                                                                if (this->DamageLayer[this->DAT_SomeTile] == 0) {
                                                                    if ((this->LogicLayer[this->DAT_SomeTile] & 0x200U)
                                                                        == 0) {
                                                                        if ((this->LogicLayer[this->DAT_SomeTile]
                                                                                & 0x800U)
                                                                            == 0) {
                                                                            if (this->LuminesenceLayer[this
                                                                                        ->DAT_SomeTile]
                                                                                < 4) {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x60
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 7);
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x68
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 7);
                                                                            }
                                                                        } else {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                OpenSHC::Map::TileMapState_Func::
                                                                                    hasHigherNeighborWithStairs,
                                                                                this)(
                                                                                this->DAT_SomeTile, this->DAT_SomeY, 0);
                                                                            if (BVar11 == FALSE) {
                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                    OpenSHC::Map::TileMapState_Func::
                                                                                        hasHigherNeighborWithStairs,
                                                                                    this)(this->DAT_SomeTile,
                                                                                    this->DAT_SomeY, 2);
                                                                                if (BVar11 == FALSE) {
                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::TileMapState_Func::
                                                                                            hasHigherNeighborWithStairs,
                                                                                        this)(this->DAT_SomeTile,
                                                                                        this->DAT_SomeY, 4);
                                                                                    if (BVar11 == FALSE) {
                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                                hasHigherNeighborWithStairs,
                                                                                            this)(this->DAT_SomeTile,
                                                                                            this->DAT_SomeY, 6);
                                                                                        if (BVar11 == FALSE) {
                                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                                OpenSHC::Map::
                                                                                                    TileMapState_Func::
                                                                                                        hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                this)(
                                                                                                this->DAT_SomeTile,
                                                                                                this->DAT_SomeY, 0);
                                                                                            if (BVar11 == FALSE) {
                                                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                                                    OpenSHC::Map::
                                                                                                        TileMapState_Func::
                                                                                                            hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                    this)(
                                                                                                    this->DAT_SomeTile,
                                                                                                    this->DAT_SomeY, 2);
                                                                                                if (BVar11 == FALSE) {
                                                                                                    BVar11 = MACRO_CALL_MEMBER(
                                                                                                        OpenSHC::Map::
                                                                                                            TileMapState_Func::
                                                                                                                hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                        this)(
                                                                                                        this->DAT_SomeTile,
                                                                                                        this->DAT_SomeY,
                                                                                                        4);
                                                                                                    if (BVar11
                                                                                                        == FALSE) {
                                                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                                                            OpenSHC::Map::
                                                                                                                TileMapState_Func::
                                                                                                                    hasHigherPlainNeighborWithWallOrGatehouse,
                                                                                                            this)(
                                                                                                            this->DAT_SomeTile,
                                                                                                            this->DAT_SomeY,
                                                                                                            6);
                                                                                                        if (BVar11
                                                                                                            == FALSE) {
                                                                                                            this->GfxLayer
                                                                                                                [this->DAT_SomeTile]
                                                                                                                = (short)GMTotalPicturesProcessed::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x68;
                                                                                                        } else {
                                                                                                            this->GfxLayer
                                                                                                                [this->DAT_SomeTile]
                                                                                                                = (short)GMTotalPicturesProcessed::
                                                                                                                      instance
                                                                                                                          [0xc]
                                                                                                                + 0x85;
                                                                                                        }
                                                                                                    } else {
                                                                                                        this->GfxLayer
                                                                                                            [this->DAT_SomeTile]
                                                                                                            = (short)GMTotalPicturesProcessed::
                                                                                                                  instance
                                                                                                                      [0xc]
                                                                                                            + 0x88;
                                                                                                    }
                                                                                                } else {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = (short)GMTotalPicturesProcessed::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                        + 0x87;
                                                                                                }
                                                                                            } else {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = (short)
                                                                                                          GMTotalPicturesProcessed::
                                                                                                              instance
                                                                                                                  [0xc]
                                                                                                    + 0x86;
                                                                                            }
                                                                                        } else {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = (short)
                                                                                                      GMTotalPicturesProcessed::
                                                                                                          instance[0xc]
                                                                                                + 0x85;
                                                                                        }
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (short)
                                                                                                  GMTotalPicturesProcessed::
                                                                                                      instance[0xc]
                                                                                            + 0x88;
                                                                                    }
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = (short)
                                                                                              GMTotalPicturesProcessed::
                                                                                                  instance[0xc]
                                                                                        + 0x87;
                                                                                }
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                          instance[0xc]
                                                                                    + 0x86;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        BVar11 = MACRO_CALL_MEMBER(
                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                isWallCornerForCardinalDirection,
                                                                            this)(
                                                                            this->DAT_SomeTile, this->DAT_SomeY, 0);
                                                                        if (BVar11 == FALSE) {
                                                                            BVar11 = MACRO_CALL_MEMBER(
                                                                                OpenSHC::Map::TileMapState_Func::
                                                                                    isWallCornerForCardinalDirection,
                                                                                this)(
                                                                                this->DAT_SomeTile, this->DAT_SomeY, 2);
                                                                            if (BVar11 == FALSE) {
                                                                                uVar12 = MACRO_CALL_MEMBER(
                                                                                    OpenSHC::Map::TileMapState_Func::
                                                                                        isWallCornerForDiagonalDirection,
                                                                                    this)(this->DAT_SomeTile,
                                                                                    this->DAT_SomeY, 1);
                                                                                if (uVar12 == 0) {
                                                                                    uVar12 = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::TileMapState_Func::
                                                                                            isWallCornerForDiagonalDirection,
                                                                                        this)(this->DAT_SomeTile,
                                                                                        this->DAT_SomeY, 3);
                                                                                    if (uVar12 == 0) {
                                                                                        uVar12 = MACRO_CALL_MEMBER(
                                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                                isWallCornerForDiagonalDirection,
                                                                                            this)(this->DAT_SomeTile,
                                                                                            this->DAT_SomeY, 5);
                                                                                        if (uVar12 == 0) {
                                                                                            uVar12 = MACRO_CALL_MEMBER(
                                                                                                OpenSHC::Map::
                                                                                                    TileMapState_Func::
                                                                                                        isWallCornerForDiagonalDirection,
                                                                                                this)(
                                                                                                this->DAT_SomeTile,
                                                                                                this->DAT_SomeY, 7);
                                                                                            sVar4 = (short)
                                                                                                GMTotalPicturesProcessed::
                                                                                                    instance[0xc];
                                                                                            if (uVar12 == 0) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x84;
                                                                                                this->LogicLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->LogicLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    | 0x400000;
                                                                                            } else {
                                                                                                if (this->mapOrientation
                                                                                                    == 0) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x81;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 2) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x80;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 4) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x83;
                                                                                                } else if (
                                                                                                    this->mapOrientation
                                                                                                    == 6) {
                                                                                                    this->GfxLayer[this
                                                                                                            ->DAT_SomeTile]
                                                                                                        = sVar4 + 0x82;
                                                                                                }
                                                                                                this->LogicLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->LogicLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    | 0x400000;
                                                                                            }
                                                                                        } else {
                                                                                            sVar4 = (short)
                                                                                                GMTotalPicturesProcessed::
                                                                                                    instance[0xc];
                                                                                            if (this->mapOrientation
                                                                                                == 0) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x80;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 2) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x83;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 4) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x82;
                                                                                            } else if (
                                                                                                this->mapOrientation
                                                                                                == 6) {
                                                                                                this->GfxLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = sVar4 + 0x81;
                                                                                            }
                                                                                            this->LogicLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = this->LogicLayer[this
                                                                                                          ->DAT_SomeTile]
                                                                                                | 0x400000;
                                                                                        }
                                                                                    } else {
                                                                                        sVar4 = (short)
                                                                                            GMTotalPicturesProcessed::
                                                                                                instance[0xc];
                                                                                        if (this->mapOrientation == 0) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x83;
                                                                                        } else if (this->mapOrientation
                                                                                            == 2) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x82;
                                                                                        } else if (this->mapOrientation
                                                                                            == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x81;
                                                                                        } else if (this->mapOrientation
                                                                                            == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x80;
                                                                                        }
                                                                                        this->LogicLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = this->LogicLayer[this
                                                                                                      ->DAT_SomeTile]
                                                                                            | 0x400000;
                                                                                    }
                                                                                } else {
                                                                                    sVar4 = (short)
                                                                                        GMTotalPicturesProcessed::
                                                                                            instance[0xc];
                                                                                    if (this->mapOrientation == 0) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x82;
                                                                                    } else if (this->mapOrientation
                                                                                        == 2) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x81;
                                                                                    } else if (this->mapOrientation
                                                                                        == 4) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x80;
                                                                                    } else if (this->mapOrientation
                                                                                        == 6) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = sVar4 + 0x83;
                                                                                    }
                                                                                    this->LogicLayer[this->DAT_SomeTile]
                                                                                        = this->LogicLayer[this
                                                                                                  ->DAT_SomeTile]
                                                                                        | 0x400000;
                                                                                }
                                                                            } else {
                                                                                sVar4
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                        instance[0xc];
                                                                                if ((this->mapOrientation == 0)
                                                                                    || (this->mapOrientation == 4)) {
                                                                                    if ((this->LogicLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & 0x400000U)
                                                                                        == 0) {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile] = sVar4
                                                                                            + 0x70
                                                                                            + (this->RandomLayer[this
                                                                                                       ->DAT_SomeTile]
                                                                                                & 3);
                                                                                    } else {
                                                                                        this->GfxLayer[this
                                                                                                ->DAT_SomeTile] = sVar4
                                                                                            + 0x78
                                                                                            + (this->RandomLayer[this
                                                                                                       ->DAT_SomeTile]
                                                                                                & 3);
                                                                                    }
                                                                                } else if ((this->LogicLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                               & 0x400000U)
                                                                                    == 0) {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                }
                                                                            }
                                                                        } else {
                                                                            sVar4 = (short)
                                                                                GMTotalPicturesProcessed::instance[0xc];
                                                                            if ((this->mapOrientation == 0)
                                                                                || (this->mapOrientation == 4)) {
                                                                                if ((this->LogicLayer[this
                                                                                             ->DAT_SomeTile]
                                                                                        & 0x400000U)
                                                                                    == 0) {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x74
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                } else {
                                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                                        = sVar4 + 0x7c
                                                                                        + (this->RandomLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                            & 3);
                                                                                }
                                                                            } else if ((this->LogicLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                           & 0x400000U)
                                                                                == 0) {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x70
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                            } else {
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = sVar4 + 0x78
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x8a
                                                                        + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->DAT_SomeY)));
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                            + (short)this->field112_0x554908;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[0xe] + 0x25
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 1) * 9;
                                                        DAT_BuildingsState::instance.field14_0x18e024 = 1;
                                                    }
                                                } else {
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->DAT_SomeY)));
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                        + (short)this->field112_0x554908;
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (this->RandomLayer[this->DAT_SomeTile] & 3)
                                                        + (short)GMTotalPicturesProcessed::instance[0xe];
                                                    DAT_BuildingsState::instance.field14_0x18e024 = 1;
                                                }
                                            } else {
                                                BVar11 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::TileMapState_Func::isTileSuitableForBrushPlacement,
                                                    this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                    (uint)((int)(this->DAT_SomeY)));
                                                if (BVar11 == FALSE) {
                                                    this->PillarGFXLayer[this->DAT_SomeTile] = 0x20;
                                                } else {
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (this->RandomLayer[this->DAT_SomeTile] & 0xf) + 0x23;
                                                }
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x29c;
                                            }
                                        } else {
                                            BVar11 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::isTileSuitableForBrushPlacement, this)(
                                                this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                (uint)((int)(this->DAT_SomeY)));
                                            if (BVar11 == FALSE) {
                                                this->PillarGFXLayer[this->DAT_SomeTile] = 0x20;
                                            } else {
                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                    = (this->RandomLayer[this->DAT_SomeTile] & 0xf) + 0x23;
                                            }
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x214;
                                        }
                                    } else if (DAT_BuildingsState::instance
                                                   .buildings[this->BuildingLayer[this->DAT_SomeTile]]
                                                   .buildingType
                                        == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeTileLuminescence,
                                            this)(this->DAT_SomeTile, this->DAT_SomeY);
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if ((((BVar11 != FALSE)
                                         && (this->DAT_SomeTile = MACRO_CALL_MEMBER(
                                                 OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                 DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                             (this->LogicLayer[this->DAT_SomeTile] & 0x100201U) != 0))
                                        && (this->ChangedLayer[this->DAT_SomeTile] != 0))
                                    && ((this->BuildingLayer[this->DAT_SomeTile] == 0
                                        && ((this->LogicLayer[this->DAT_SomeTile] & 0x10000030U) == 0)))) {
                                    if ((this->LogicLayer[this->DAT_SomeTile] & 1U) == 0) {
                                        if ((this->LogicLayer[this->DAT_SomeTile] & 0x100000U) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::computeTileCliffEdgeFlags, this)(
                                                this->DAT_SomeTile, this->DAT_SomeX, this->DAT_SomeY);
                                        }
                                    } else {
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xfffc;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][this->mapOrientation];
                                        this->field218_0x554a50 = (ushort)this->HeightLayer[iVar17];
                                        if ((this->LogicLayer[iVar17] & 1U) != 0) {
                                            this->field218_0x554a50 = 0;
                                        }
                                        if ((this->LogicLayer[iVar17] & 0x80U) != 0) {
                                            this->field218_0x554a50 = 0x14;
                                        }
                                        if (0x13 < this->field218_0x554a50) {
                                            sVar4 = (short)GMTotalPicturesProcessed::instance[0xa6];
                                            if (this->field218_0x554a50 < 0x5b) {
                                                if (this->field218_0x554a50 < 0x29) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5dc;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5e2;
                                                }
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x5ee;
                                            }
                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                = (ushort)GMTotalPicturesProcessed::instance[9];
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x40;
                                        }
                                        local_74 = 0;
                                        this->bitFlag = 0;
                                        for (local_70 = 0; local_70 < 8; local_70 = local_70 + 1) {
                                            iVar17 = this->DAT_SomeTile
                                                + this->directionTranslationMatrix[this->DAT_SomeY][local_70];
                                            if (this->HeightLayer[iVar17] < 0x14) {
                                                if ((this->LogicLayer[iVar17] & 0x100031U) == 0) {
                                                    this->bitFlag
                                                        = this->bitFlag | (byte)(0x80 >> ((byte)local_70 & 0x1f));
                                                }
                                                if (((this->LogicLayer[iVar17] & 0x100001U) == 0)
                                                    && ((this->Logic2Layer[iVar17] & 0x20) != 0)) {
                                                    local_74 = 0x80 >> ((byte)local_70 & 0x1f) | local_74;
                                                }
                                            }
                                        }
                                        if (this->bitFlag != 0) {
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x100;
                                            this->CertainPathLayer[this->DAT_SomeTile]
                                                = (ushort)this->bitFlag | (ushort)(local_74 << 8);
                                        }
                                    }
                                    if ((this->LogicLayer[this->DAT_SomeTile] & 0x200U) != 0) {
                                        uVar12 = (this->field84_0x5548a4 + 7) % 8;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = (this->field84_0x5548a4 + 1) % 8;
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if (this->LuminesenceLayer[this->DAT_SomeTile] < 4) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x60
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x68
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                            }
                                        }
                                        uVar12 = (this->field84_0x5548a4 + 1) % 8;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = (this->field84_0x5548a4 + 3) % 8;
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if ((this->DAT_SomeY & 1U) == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x138;
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x137;
                                            }
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                        uVar12 = (this->field84_0x5548a4 + 5) % 8;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = (this->field84_0x5548a4 + 7) % 8;
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            if ((this->DAT_SomeY & 1U) == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x13a;
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[0xc] + 0x139;
                                            }
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                        uVar12 = (this->field84_0x5548a4 + 3) % 8;
                                        iVar17 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        uVar12 = (this->field84_0x5548a4 + 5) % 8;
                                        iVar13 = this->DAT_SomeTile
                                            + this->directionTranslationMatrix[this->DAT_SomeY][uVar12];
                                        if (((((this->LogicLayer[iVar17] | this->LogicLayer[iVar13]) & 1U) == 0)
                                                && ((this->MiscDisplayLayer[iVar17] & 0x3c0) != 0))
                                            && ((this->MiscDisplayLayer[iVar13] & 0x3c0) != 0)) {
                                            uVar12 = (int)this->DAT_SomeY % 8;
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[0xc] + 0x12f
                                                + (short)uVar12;
                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x3c0;
                                        }
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if (((BVar11 != FALSE)
                                        && (this->DAT_SomeTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                            (this->LogicLayer[this->DAT_SomeTile] & 1U) != 0))
                                    && (((this->ChangedLayer[this->DAT_SomeTile] != 0
                                             && (((this->LogicLayer[this->DAT_SomeTile] & 0x10000030U) == 0
                                                 && (this->BuildingLayer[this->DAT_SomeTile] == 0))))
                                        && ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x40) == 0)))) {
                                                                        _gfxLayer = (char*)this->ptr_MiscDisplayLayer;
                                    _gfxTile = this->DAT_SomeTile;
                                    _gfxY = this->DAT_SomeY;
                                    MACRO_GFX_NEIGHBOUR_MASK(m2, 2, MACRO_GFX_SHIFT_2, MACRO_GFX_ROWSTEP_2, 0x80)
                                    bVar19 = this->bitFlag;
                                                                        _gfxLayer = (char*)this->ptr_MiscDisplayLayer;
                                    _gfxTile = this->DAT_SomeTile;
                                    _gfxY = this->DAT_SomeY;
                                    MACRO_GFX_NEIGHBOUR_MASK(m3, 2, MACRO_GFX_SHIFT_2, MACRO_GFX_ROWSTEP_2, 0x40)
                                    bVar16 = this->bitFlag;
                                    this->bitFlag = bVar16 & ~bVar19;
                                    if (this->bitFlag != 0) {
                                        this->GfxLayer[this->DAT_SomeTile]
                                            = (short)GMTotalPicturesProcessed::instance[0xa6] + 0x5d0;
                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                            = (ushort)GMTotalPicturesProcessed::instance[9];
                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x80;
                                    }
                                }
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
            local_c = DAT_PathFindingState::instance.mappingYRelated % 10;
            for (local_18 = this->someIndex; local_18 <= this->someLimit; local_18 = local_18 + 1) {
                for (local_10 = this->someYLike; local_10 <= this->someYLikeLimit; local_10 = local_10 + 1) {
                    if (*(char*)(local_18 * 0x28 + 0x1f93438 + local_10) != '\0') {
                        local_24 = local_c;
                        local_c = 0;
                        for (; local_24 < 10; local_24 = local_24 + 1) {
                            this->DAT_SomeY = local_18 * 10 + local_24;
                            this->DAT_SomeX = local_10 * 10;
                            for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
                                BVar11 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->DAT_SomeX, (uint)((int)(this->DAT_SomeY)));
                                if (((BVar11 != FALSE)
                                        && (this->DAT_SomeTile = MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                                DAT_ViewportRenderState::ptr)(this->DAT_SomeX, this->DAT_SomeY),
                                            (this->LogicLayer[this->DAT_SomeTile] & L_BORDER | L_BORDER_EDGE) == 0))
                                    && (this->ChangedLayer[this->DAT_SomeTile] != 0)) {
                                    this->ChangedLayer[this->DAT_SomeTile] = this->ChangedLayer[this->DAT_SomeTile] - 1;
                                    iVar17 = this->DAT_SomeX;
                                    if ((this->LogicLayer[this->DAT_SomeTile] & L_SEA) == 0) {
                                        if ((this->LogicLayer[this->DAT_SomeTile] & L_RIVER) == 0) {
                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_FORD) == 0) {
                                                if ((this->LogicLayer[this->DAT_SomeTile] & L_PLAIN2_AND_PITCH) == 0) {
                                                    if (this->BuildingLayer[this->DAT_SomeTile] != 0) {
                                                        iVar13 = (int)this->BuildingLayer[this->DAT_SomeTile];
                                                        if (DAT_BuildingsState::instance.buildings[iVar13].buildingType
                                                            == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                                                            this->field112_0x554908
                                                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                        computeWallCornerRenderRotation,
                                                                    this)(this->DAT_SomeX);
                                                            this->WallGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[10] + -1
                                                                + (short)this->field112_0x554908;
                                                        }
                                                        iVar14 = MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                            this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                            (uint)((int)(this->DAT_SomeY)));
                                                        BVar1 = DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType;
                                                        if (((BVar1 == OpenSHC::Map::Buildings::BT_FIREBALLISTA)
                                                                || ((0x4f < (short)BVar1 && ((short)BVar1 < 0x55))))
                                                            && (iVar14 == 0)) {
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)(((((int)(uint)this
                                                                                    ->HeightLayer[this->DAT_SomeTile]
                                                                                >> 3)
                                                                               + -1)
                                                                              * 0x40)
                                                                      / 2)
                                                                + (short)GMTotalPicturesProcessed::instance[3]
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else {
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->field112_0x554908;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        }
                                                        if (((DAT_BuildingsState::instance.buildings[iVar13]
                                                                     .buildingType
                                                                 == OpenSHC::Map::Buildings::BT_KILLINGPIT)
                                                                && (DAT_BuildingsState::instance.buildings[iVar13].state
                                                                    < 1))
                                                            && ((
                                                                BVar11 = MACRO_CALL_MEMBER(
                                                                    OpenSHC::Game::GameStateStructures_Func::isSameTeam,
                                                                    DAT_GameState::ptr)(
                                                                    (int)DAT_BuildingsState::instance.buildings[iVar13]
                                                                        .owner,
                                                                    (int)((int)(DAT_GameSynchronyState::instance
                                                                            .currentPlayerSlotID))),
                                                                BVar11 == FALSE
                                                                    && (DAT_GameCore::instance.gameMode_2
                                                                        != OpenSHC::Game::GM_EDITOR)))) {
                                                            if ((this->LogicLayer[this->DAT_SomeTile]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE)
                                                                == 0)
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        } else {
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .buildingType
                                                                == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED)
                                                                goto LAB_00510585;
                                                            if (DAT_BuildingsState::instance.buildings[iVar13]
                                                                    .currentTilePositionAdjusted
                                                                == this->DAT_SomeTile) {
                                                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                      updateBuildingGraphicsLayer,
                                                                    this)(iVar13);
                                                                goto LAB_005109e8;
                                                            }
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                    if ((this->LogicLayer[this->DAT_SomeTile] & L_KEEP_NON_MANOR_HOUSE)
                                                        == 0) {
                                                        if (((this->LogicLayer[this->DAT_SomeTile] & L_ROCKY) == 0)
                                                            || ((this->LogicLayer[this->DAT_SomeTile]
                                                                    & L_WALL_OR_GATEHOUSE)
                                                                != 0)) {
                                                            if ((this->LogicLayer[this->DAT_SomeTile] & L_BOULDERS)
                                                                == 0) {
                                                                if ((this->LogicLayer[this->DAT_SomeTile] & L_PEBBLES)
                                                                    == 0) {
                                                                    if ((this->LogicLayer[this->DAT_SomeTile] & L_IRON)
                                                                        == 0) {
                                                                        if ((this->LogicLayer[this->DAT_SomeTile]
                                                                                & L_OIL)
                                                                            == 0) {
                                                                            if ((this->LogicLayer[this->DAT_SomeTile]
                                                                                    & L_MOAT)
                                                                                == 0) {
                                                                                if (((this->LogicLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                             & L_WALL_OR_GATEHOUSE
                                                                                         | L_FARM_FIELD_WHEAT
                                                                                         | L_FARM_FIELD_HOP
                                                                                         | L_FARM_FIELD_APPLE
                                                                                         | L_FARM_FIELD_DAIRY)
                                                                                        == 0)
                                                                                    || ((this->LogicLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & L_FARM_FIELD_APPLE)
                                                                                        != 0)) {
                                                                                    sVar8 = 0;
                                                                                    if ((this->WallOwnerLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & 8)
                                                                                        != 0) {
                                                                                        sVar8 = 0x2d;
                                                                                    }
                                                                                    if ((this->MiscDisplayLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                            & 0x80)
                                                                                        != 0)
                                                                                        goto LAB_0050ffbc;
                                                                                    if ((((this->LogicLayer[this
                                                                                                   ->DAT_SomeTile]
                                                                                                  & L_WALL_OR_GATEHOUSE
                                                                                              | L_BUILDING
                                                                                              | L_KEEP_NON_MANOR_HOUSE)
                                                                                             != 0)
                                                                                            || (this->BuildingWasLayer
                                                                                                    [this->DAT_SomeTile]
                                                                                                == '\0'))
                                                                                        || ((this->MiscDisplayLayer[this
                                                                                                     ->DAT_SomeTile]
                                                                                                & 0x10)
                                                                                            == 0))
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            } else {
                                                                                this->bitFlag = 0;
                                                                                for (local_d4 = 0; local_d4 < 8;
                                                                                    local_d4 = local_d4 + 2) {
                                                                                    iVar13 = this->DAT_SomeTile
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->DAT_SomeY]
                                                                                              [local_d4];
                                                                                    if ((this->LogicLayer[iVar13]
                                                                                            & L_MOAT)
                                                                                        == 0) {
                                                                                        if (((this->BuildingLayer
                                                                                                     [iVar13]
                                                                                                 != 0)
                                                                                                && (DAT_BuildingsState::instance
                                                                                                        .buildings[this->BuildingLayer
                                                                                                                [iVar13]]
                                                                                                        .buildingType
                                                                                                    == OpenSHC::Map::
                                                                                                        Buildings::
                                                                                                            BT_DRAWBRIDGE))
                                                                                            && (iVar13
                                                                                                = MACRO_CALL_MEMBER(
                                                                                                    OpenSHC::Map::
                                                                                                        TileMapState_Func::
                                                                                                            returnOwnedMoatAtTile,
                                                                                                    this)(iVar13),
                                                                                                iVar13 != 0)) {
                                                                                            this->bitFlag
                                                                                                = this->bitFlag
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    } else {
                                                                                        this->bitFlag = this->bitFlag
                                                                                            | (byte)(0x80
                                                                                                >> ((byte)local_d4
                                                                                                    & 0x1f));
                                                                                    }
                                                                                }
                                                                                this->bitFlag = ~this->bitFlag & 0xaa;
                                                                                if (this->bitFlag == 0) {
                                                                                    this->bitFlag = 0;
                                                                                    for (local_d4 = 1; local_d4 < 8;
                                                                                        local_d4 = local_d4 + 2) {
                                                                                        iVar13 = this->DAT_SomeTile
                                                                                            + this->directionTranslationMatrix
                                                                                                  [this->DAT_SomeY]
                                                                                                  [local_d4];
                                                                                        if ((this->LogicLayer[iVar13]
                                                                                                & L_MOAT)
                                                                                            == 0) {
                                                                                            if (((this->BuildingLayer
                                                                                                         [iVar13]
                                                                                                     != 0)
                                                                                                    && (DAT_BuildingsState::instance
                                                                                                            .buildings
                                                                                                                [this->BuildingLayer
                                                                                                                        [iVar13]]
                                                                                                            .buildingType
                                                                                                        == OpenSHC::Map::
                                                                                                            Buildings::
                                                                                                                BT_DRAWBRIDGE))
                                                                                                && (iVar13
                                                                                                    = MACRO_CALL_MEMBER(
                                                                                                        OpenSHC::Map::
                                                                                                            TileMapState_Func::
                                                                                                                returnOwnedMoatAtTile,
                                                                                                        this)(iVar13),
                                                                                                    iVar13 != 0)) {
                                                                                                this->bitFlag
                                                                                                    = this->bitFlag
                                                                                                    | (byte)(0x80
                                                                                                        >> ((byte)
                                                                                                                local_d4
                                                                                                            & 0x1f));
                                                                                            }
                                                                                        } else {
                                                                                            this->bitFlag
                                                                                                = this->bitFlag
                                                                                                | (byte)(0x80
                                                                                                    >> ((byte)local_d4
                                                                                                        & 0x1f));
                                                                                        }
                                                                                    }
                                                                                    this->bitFlag
                                                                                        = ~this->bitFlag & 0x55;
                                                                                }
                                                                                if (this->mapOrientation == 0) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 0);
                                                                                } else if (this->mapOrientation == 2) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 2);
                                                                                } else if (this->mapOrientation == 4) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 4);
                                                                                } else if (this->mapOrientation == 6) {
                                                                                    this->bitFlag = MACRO_CALL_MEMBER(
                                                                                        OpenSHC::Map::Navigation::
                                                                                            DirectionAlgorithmState_Func::
                                                                                                rotateByteLeft,
                                                                                        DAT_DirectionAlgorithmState::
                                                                                            ptr)(this->bitFlag, 6);
                                                                                }
                                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                                    = (short)GMTotalPicturesProcessed::
                                                                                          instance[5]
                                                                                    + 0xcc
                                                                                    + (ushort)this->LuminesenceLayer
                                                                                            [this->DAT_SomeTile]
                                                                                        * 4
                                                                                    + (this->RandomLayer[this
                                                                                               ->DAT_SomeTile]
                                                                                        & 3);
                                                                                for (local_14 = 0; local_14 < 7;
                                                                                    local_14 = local_14 + 1) {
                                                                                    if (DAT_TerrainDefinedData::instance
                                                                                            .field2298_0x1d64[local_14]
                                                                                            .unk1
                                                                                        == this->bitFlag) {
                                                                                        sVar4 = (short)
                                                                                            GMTotalPicturesProcessed::
                                                                                                instance[5];
                                                                                        if (local_14 < 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0xec
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (ushort)DAT_TerrainDefinedData::
                                                                                                      instance
                                                                                                          .field2298_0x1d64
                                                                                                              [local_14]
                                                                                                          .unk2;
                                                                                        } else if (local_14 == 4) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x10c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->DAT_SomeTile]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 5) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 300
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                        [this->DAT_SomeTile]
                                                                                                    * 4
                                                                                                + (this->RandomLayer[this
                                                                                                           ->DAT_SomeTile]
                                                                                                    & 3);
                                                                                        } else if (local_14 == 6) {
                                                                                            this->GfxLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = sVar4 + 0x14c
                                                                                                + (ushort)this->LuminesenceLayer
                                                                                                      [this->DAT_SomeTile];
                                                                                        }
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if ((this->MiscDisplayLayer[this
                                                                                             ->DAT_SomeTile]
                                                                                        & 0x80)
                                                                                    != 0) {
                                                                                LAB_0050ffbc:
                                                                                    uVar12
                                                                                        = (0xdU - this->mapOrientation)
                                                                                        % 8;
                                                                                    uVar15 = (9 - this->mapOrientation)
                                                                                        % 8;
                                                                                    iVar13 = this->DAT_SomeTile
                                                                                        + this->directionTranslationMatrix
                                                                                              [this->DAT_SomeY][uVar15];
                                                                                    uVar2 = (ushort)iVar17;
                                                                                    uVar3 = (ushort)this->DAT_SomeY;
                                                                                    if ((this->MiscDisplayLayer[this->DAT_SomeTile
                                                                                             + this
                                                                                                 ->directionTranslationMatrix
                                                                                                     [this->DAT_SomeY]
                                                                                                     [uVar12]]
                                                                                            & 0x80)
                                                                                        == 0) {
                                                                                        if ((this->MiscDisplayLayer
                                                                                                    [iVar13]
                                                                                                & 0x80)
                                                                                            == 0) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = this->AlphaGFXLayer[this
                                                                                                          ->DAT_SomeTile]
                                                                                                + ((uVar2 ^ uVar3) & 1);
                                                                                        } else if ((this->mapOrientation
                                                                                                       == 0)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        } else {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        }
                                                                                    } else if ((this->MiscDisplayLayer
                                                                                                       [iVar13]
                                                                                                   & 0x80)
                                                                                        == 0) {
                                                                                        if ((this->mapOrientation == 0)
                                                                                            || (this->mapOrientation
                                                                                                == 4)) {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x35 + sVar8;
                                                                                        } else {
                                                                                            this->AlphaGFXLayer[this
                                                                                                    ->DAT_SomeTile]
                                                                                                = ((uVar2 ^ uVar3) & 1)
                                                                                                + 0x33 + sVar8;
                                                                                        }
                                                                                    } else if ((this->mapOrientation
                                                                                                   == 0)
                                                                                        || (this->mapOrientation
                                                                                            == 6)) {
                                                                                        uVar12
                                                                                            = (int)this->DAT_SomeY % 8;
                                                                                        this->AlphaGFXLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (0x3e - (short)uVar12)
                                                                                            + sVar8;
                                                                                    } else {
                                                                                        uVar12
                                                                                            = (int)this->DAT_SomeY % 8;
                                                                                        this->AlphaGFXLayer[this
                                                                                                ->DAT_SomeTile]
                                                                                            = (short)uVar12 + 0x37
                                                                                            + sVar8;
                                                                                    }
                                                                                    this->bitFlag = 0;
                                                                                    if ((*(uint*)((char*)this
                                                                                                      ->ptr_LogicLayer
                                                                                             + this->DAT_SomeTile * 4
                                                                                             + 4)
                                                                                            & 0x200)
                                                                                        != 0) {
                                                                                        this->bitFlag = 0x20;
                                                                                    }
                                                                                    if ((*(uint*)((char*)this
                                                                                                      ->ptr_LogicLayer
                                                                                             + this->DAT_SomeTile * 4
                                                                                             + -4)
                                                                                            & 0x200)
                                                                                        != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 2;
                                                                                    }
                                                                                    puVar18 = (uint*)((char*)this
                                                                                                          ->ptr_LogicLayer
                                                                                        + *(int*)((char*)this
                                                                                                      ->ptr_MovementDirectionTranslationMatrix
                                                                                              + this->DAT_SomeY * 0x20)
                                                                                            * 4
                                                                                        + this->DAT_SomeTile * 4);
                                                                                    if ((puVar18[-1] & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 1;
                                                                                    }
                                                                                    if ((puVar18[1] & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x40;
                                                                                    }
                                                                                    if ((*puVar18 & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x80;
                                                                                    }
                                                                                    puVar18 = (uint*)((char*)this
                                                                                                          ->ptr_LogicLayer
                                                                                        + *(int*)((int)((char*)this
                                                                                                            ->ptr_MovementDirectionTranslationMatrix
                                                                                                      + this->DAT_SomeY
                                                                                                          * 0x20)
                                                                                              + 0x10)
                                                                                            * 4
                                                                                        + this->DAT_SomeTile * 4);
                                                                                    if ((puVar18[-1] & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 4;
                                                                                    }
                                                                                    if ((puVar18[1] & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 0x10;
                                                                                    }
                                                                                    if ((*puVar18 & 0x200) != 0) {
                                                                                        this->bitFlag
                                                                                            = this->bitFlag | 8;
                                                                                    }
                                                                                    if (this->bitFlag != 0) {
                                                                                        switch (this->mapOrientation) {
                                                                                        case 0:
                                                                                            if ((this->bitFlag & 0x82)
                                                                                                == 0x82) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 2:
                                                                                            if ((this->bitFlag & 0xa0)
                                                                                                == 0xa0) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 4:
                                                                                            if ((this->bitFlag & 0x28)
                                                                                                == 0x28) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                            break;
                                                                                        case 6:
                                                                                            if ((this->bitFlag & 10)
                                                                                                == 10) {
                                                                                                this->AlphaGFXLayer[this
                                                                                                        ->DAT_SomeTile]
                                                                                                    = this->AlphaGFXLayer
                                                                                                          [this->DAT_SomeTile]
                                                                                                    + 0xe;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    if ((this->LogicLayer[this
                                                                                                 ->DAT_SomeTile]
                                                                                                & L_PLAIN2_AND_PITCH
                                                                                            | L_MOAT)
                                                                                        == 0)
                                                                                        goto LAB_00510585;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            this->PillarGFXLayer[this
                                                                                    ->DAT_SomeTile] = (ushort)
                                                                                GMTotalPicturesProcessed::instance[9];
                                                                            this->field112_0x554908
                                                                                = (int)(short)this
                                                                                      ->RandomLayer[this->DAT_SomeTile]
                                                                                & 7;
                                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                                = (short)GMTotalPicturesProcessed::
                                                                                      instance[0x37]
                                                                                + 0x428
                                                                                + (short)(this->field112_0x554908 << 4);
                                                                            sVar4 = (short)this->DAT_SomeY;
                                                                            sVar5 = (short)this->DAT_SomeX;
                                                                            if (this->field112_0x554908 == 0) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->field112_0x554908 == 1) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x1ff;
                                                                            } else if (this->field112_0x554908 == 2) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->field112_0x554908 == 3) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->field112_0x554908 == 4) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->field112_0x554908 == 5) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0xff;
                                                                            } else if (this->field112_0x554908 == 6) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            } else if (this->field112_0x554908 == 7) {
                                                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                                                    = this->RandomLayer[this
                                                                                              ->DAT_SomeTile]
                                                                                        + sVar5 + sVar4
                                                                                    & 0x7f;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        MACRO_CALL_MEMBER(
                                                                            OpenSHC::Map::TileMapState_Func::
                                                                                computeClimbRampRotation,
                                                                            this)(this->DAT_SomeTile,
                                                                            (uint)((int)(this->DAT_SomeX)),
                                                                            (uint)((int)(this->DAT_SomeY)));
                                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                                            = (short)
                                                                                  GMTotalPicturesProcessed::instance[9]
                                                                            + -1 + (short)this->field112_0x554908;
                                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                            = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                            | 0x800;
                                                                        this->field112_0x554908
                                                                            = (int)(short)this
                                                                                  ->RandomLayer[this->DAT_SomeTile]
                                                                            & 0xf;
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0xee + (short)this->field112_0x554908;
                                                                    }
                                                                } else {
                                                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                          computeClimbRampRotation,
                                                                        this)(this->DAT_SomeTile,
                                                                        (uint)((int)(this->DAT_SomeX)),
                                                                        (uint)((int)(this->DAT_SomeY)));
                                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[9]
                                                                        + -1 + (short)this->field112_0x554908;
                                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                        | 0x800;
                                                                    this->field112_0x554908
                                                                        = (int)(short)this
                                                                              ->RandomLayer[this->DAT_SomeTile]
                                                                        & 0xf;
                                                                    if (this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        < 6) {
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0x20 + (short)this->field112_0x554908;
                                                                    } else {
                                                                        this->GfxLayer[this->DAT_SomeTile]
                                                                            = (short)GMTotalPicturesProcessed::instance
                                                                                  [0xc]
                                                                            + 0x30 + (short)this->field112_0x554908;
                                                                    }
                                                                }
                                                            } else {
                                                                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                      computeClimbRampRotation,
                                                                    this)(this->DAT_SomeTile,
                                                                    (uint)((int)(this->DAT_SomeX)),
                                                                    (uint)((int)(this->DAT_SomeY)));
                                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                    + (short)this->field112_0x554908;
                                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                    = this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                    | 0x800;
                                                                this->field112_0x554908
                                                                    = (int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                    & 0xf;
                                                                if (this->LuminesenceLayer[this->DAT_SomeTile] < 6) {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[0xc]
                                                                        + 0x40 + (short)this->field112_0x554908;
                                                                } else {
                                                                    this->GfxLayer[this->DAT_SomeTile]
                                                                        = (short)GMTotalPicturesProcessed::instance[0xc]
                                                                        + 0x50 + (short)this->field112_0x554908;
                                                                }
                                                            }
                                                        } else {
                                                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->DAT_SomeTile,
                                                                (uint)((int)(this->DAT_SomeX)),
                                                                (uint)((int)(this->DAT_SomeY)));
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->field112_0x554908;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                            iVar13 = (int)this->OrganismLayer[this->DAT_SomeTile];
                                                            if (1999 < iVar13) {
                                                                if (*(int*)(&DAT_LandscapeState::instance.trees[0x635]
                                                                                .unknownDistanceRelatedToCrow
                                                                        + iVar13 * 0x10)
                                                                    == this->DAT_SomeTile) {
                                                                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                          applyRockGraphicsToFootprint,
                                                                        this)(iVar13 + -2000);
                                                                }
                                                                goto LAB_0050c199;
                                                            }
                                                            this->field112_0x554908
                                                                = (int)(short)this->RandomLayer[this->DAT_SomeTile] & 7;
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[0x38]
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                                                + (short)this->field112_0x554908;
                                                        }
                                                    } else {
                                                        if (DAT_BuildingsState::instance
                                                                .buildings[this->BuildingLayer[this->DAT_SomeTile]]
                                                                .currentTilePositionAdjusted
                                                            != this->DAT_SomeTile)
                                                            goto LAB_0050c199;
                                                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                              updateBuildingGraphicsLayer,
                                                            this)((int)this->BuildingLayer[this->DAT_SomeTile]);
                                                    }
                                                } else {
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xdfff;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, this)(
                                                        this->DAT_SomeTile);
                                                    if (iVar13 != 0) {
                                                        if (((this->pitchDitches[iVar13].state < 2)
                                                                && (BVar11 = MACRO_CALL_MEMBER(
                                                                        OpenSHC::Game::GameStateStructures_Func::
                                                                            isSameTeam,
                                                                        DAT_GameState::ptr)(
                                                                        (int)this->pitchDitches[iVar13].owner,
                                                                        (int)((int)(DAT_GameSynchronyState::instance
                                                                                .currentPlayerSlotID))),
                                                                    BVar11 == FALSE))
                                                            && (DAT_GameCore::instance.gameMode_2
                                                                != OpenSHC::Game::GM_EDITOR)) {
                                                            if ((this->LogicLayer[this->DAT_SomeTile]
                                                                    & L_DEFAULT_EARTH_OR_TEXTURE)
                                                                == 0)
                                                                goto LAB_00510585;
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        } else {
                                                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::
                                                                                  computeClimbRampRotation,
                                                                this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                                (uint)((int)(this->DAT_SomeY)));
                                                            this->PillarGFXLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                                + (short)this->field112_0x554908;
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (this->pitchDitches[iVar13].rng & 7U)
                                                                + (short)GMTotalPicturesProcessed::instance[0x8c];
                                                            this->MiscDisplayLayer[this->DAT_SomeTile]
                                                                = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x2000;
                                                            if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x80)
                                                                != 0)
                                                                goto LAB_0050ffbc;
                                                        }
                                                        goto LAB_0050c199;
                                                    }
                                                LAB_00510585:
                                                    uVar12
                                                        = (((int)(uint)this->HeightLayer[this->DAT_SomeTile] >> 3) - 1)
                                                        % 16;
                                                    local_8 = uVar12 * 0x40 + 1;
                                                    iVar13 = MACRO_CALL_MEMBER(
                                                        OpenSHC::Map::TileMapState_Func::computeClimbRampRotation,
                                                        this)(this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                        (uint)((int)(this->DAT_SomeY)));
                                                    if ((this->HeightLayer[this->DAT_SomeTile] < 0x88)
                                                        && (iVar13 == 0)) {
                                                        if (local_8 < 1) {
                                                            local_8 = 1;
                                                        }
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)((local_8 + -1) / 2)
                                                            + (short)GMTotalPicturesProcessed::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        BVar11 = MACRO_CALL_MEMBER(
                                                            OpenSHC::Map::TileMapState_Func::isCliffDropInDirection,
                                                            this)(this->DAT_SomeTile, (undefined4)((int)(iVar17)),
                                                            this->DAT_SomeY);
                                                        if (BVar11 == FALSE) {
                                                            bVar10 = false;
                                                        } else {
                                                            bVar10 = true;
                                                        }
                                                    } else {
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[9] + -1
                                                            + (short)this->field112_0x554908;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                        bVar10 = true;
                                                    }
                                                    if ((this->Logic2Layer[this->DAT_SomeTile] & 0x20) == 0) {
                                                        if (this->HeightLayer[this->DAT_SomeTile] < 8) {
                                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 2) == 0) {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[2]
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[0x37]
                                                                    + 0xb4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                            }
                                                        } else if ((this->LogicLayer[this->DAT_SomeTile]
                                                                       & L_DEFAULT_EARTH_OR_TEXTURE)
                                                            == 0) {
                                                            if ((bVar10)
                                                                && (DAT_GameCore::instance.gameMode_2
                                                                    == OpenSHC::Game::GM_EDITOR)) {
                                                                this->LogicLayer[this->DAT_SomeTile]
                                                                    = this->LogicLayer[this->DAT_SomeTile] | 128;
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[0x38]
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 8
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = (short)GMTotalPicturesProcessed::instance[2]
                                                                    + ((short)((int)(uint)this
                                                                                   ->HeightLayer[this->DAT_SomeTile]
                                                                           >> 3)
                                                                          + -1)
                                                                        * 0x20
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            }
                                                        } else {
                                                            /*
                                                              sets section 1001 after placing oasis grass for example
                                                             */
                                                            this->GfxLayer[this->DAT_SomeTile] = 0;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->DAT_SomeTile] = 0;
                                                    }
                                                }
                                            } else {
                                                bVar19 = 0;
                                                if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                            & L_RIVER
                                                        | L_FORD)
                                                    != 0) {
                                                    bVar19 = 0x20;
                                                }
                                                if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                            & L_RIVER
                                                        | L_FORD)
                                                    != 0) {
                                                    bVar19 = bVar19 | 2;
                                                }
                                                if ((*(uint*)((char*)this->ptr_LogicLayer
                                                         + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                             * 4
                                                         + this->DAT_SomeTile * 4)
                                                            & L_RIVER
                                                        | L_FORD)
                                                    != 0) {
                                                    bVar19 = bVar19 | 0x80;
                                                }
                                                if ((*(uint*)((char*)this->ptr_LogicLayer
                                                         + *(int*)((int)((char*)this
                                                                             ->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4)
                                                            & L_RIVER
                                                        | L_FORD)
                                                    != 0) {
                                                    bVar19 = bVar19 | 8;
                                                }
                                                this->bitFlag = ~bVar19 & 0xaa;
                                                if (this->bitFlag == 0) {
                                                    bVar19 = (*(uint*)((char*)this->ptr_LogicLayer
                                                                  + *(int*)((char*)this
                                                                                ->ptr_MovementDirectionTranslationMatrix
                                                                        + this->DAT_SomeY * 0x20)
                                                                      * 4
                                                                  + this->DAT_SomeTile * 4 + -4)
                                                                     & L_RIVER
                                                                 | L_FORD)
                                                        != 0;
                                                    if ((*(uint*)((char*)this->ptr_LogicLayer
                                                             + *(int*)((char*)this
                                                                           ->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + 4)
                                                            & 0x300000)
                                                        != 0) {
                                                        bVar19 = bVar19 | 0x40;
                                                    }
                                                    if ((*(uint*)((char*)this->ptr_LogicLayer
                                                             + *(int*)((int)((char*)this
                                                                                 ->ptr_MovementDirectionTranslationMatrix
                                                                           + this->DAT_SomeY * 0x20)
                                                                   + 0x10)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + -4)
                                                            & 0x300000)
                                                        != 0) {
                                                        bVar19 = bVar19 | 4;
                                                    }
                                                    if ((*(uint*)((char*)this->ptr_LogicLayer
                                                             + *(int*)((int)((char*)this
                                                                                 ->ptr_MovementDirectionTranslationMatrix
                                                                           + this->DAT_SomeY * 0x20)
                                                                   + 0x10)
                                                                 * 4
                                                             + this->DAT_SomeTile * 4 + 4)
                                                            & 0x300000)
                                                        != 0) {
                                                        bVar19 = bVar19 | 0x10;
                                                    }
                                                    this->bitFlag = ~bVar19 & 0x55;
                                                }
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
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x29c
                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 8
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 7);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance.field2298_0x1d64[local_14].unk1
                                                        == this->bitFlag) {
                                                        sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                                        if (local_14 < 4) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x234
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (ushort)DAT_TerrainDefinedData::instance
                                                                      .field2298_0x1d64[local_14]
                                                                      .unk2;
                                                        } else if (local_14 == 4) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x254
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else if (local_14 == 5) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x274
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                        } else if (local_14 == 6) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x294
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile];
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        } else {
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = this->Logic2Layer[this->DAT_SomeTile] & 0xf7;
                                            bVar19 = 0;
                                            if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4) & 1)
                                                != 0) {
                                                bVar19 = 0x20;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                    & 1)
                                                != 0) {
                                                bVar19 = bVar19 | 2;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                     + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                           + this->DAT_SomeY * 0x20)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 1)
                                                != 0) {
                                                bVar19 = bVar19 | 0x80;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                     + *(int*)((int)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                           + 0x10)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 1)
                                                != 0) {
                                                bVar19 = bVar19 | 8;
                                            }
                                            if ((bVar19 != 0)
                                                && (this->Logic2Layer[this->DAT_SomeTile]
                                                    = this->Logic2Layer[this->DAT_SomeTile] | 8,
                                                    (this->Logic2Layer[this->DAT_SomeTile] & 0x20) != 0)) {
                                                this->Logic2Layer[this->DAT_SomeTile]
                                                    = this->Logic2Layer[this->DAT_SomeTile] & 0xdf;
                                                this->WallGFXLayer[this->DAT_SomeTile]
                                                    = this->RandomLayer[this->DAT_SomeTile] & 7;
                                            }
                                            bVar19 = 0;
                                            if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                    & 0x100031)
                                                != 0) {
                                                bVar19 = 0x20;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                    & 0x100031)
                                                != 0) {
                                                bVar19 = bVar19 | 2;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                     + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                           + this->DAT_SomeY * 0x20)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 0x100031)
                                                != 0) {
                                                bVar19 = bVar19 | 0x80;
                                            }
                                            if ((*(uint*)((char*)this->ptr_LogicLayer
                                                     + *(int*)((int)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                                   + this->DAT_SomeY * 0x20)
                                                           + 0x10)
                                                         * 4
                                                     + this->DAT_SomeTile * 4)
                                                    & 0x100031)
                                                != 0) {
                                                bVar19 = bVar19 | 8;
                                            }
                                            this->bitFlag = ~bVar19 & 0xaa;
                                            if (this->bitFlag == 0) {
                                                bVar19
                                                    = (*(uint*)((char*)this->ptr_LogicLayer
                                                           + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                                 + this->DAT_SomeY * 0x20)
                                                               * 4
                                                           + this->DAT_SomeTile * 4 + -4)
                                                          & 0x100031)
                                                    != 0;
                                                if ((*(uint*)((char*)this->ptr_LogicLayer
                                                         + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + 4)
                                                        & 0x100031)
                                                    != 0) {
                                                    bVar19 = bVar19 | 0x40;
                                                }
                                                if ((*(uint*)((char*)this->ptr_LogicLayer
                                                         + *(int*)((int)((char*)this
                                                                             ->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + -4)
                                                        & 0x100031)
                                                    != 0) {
                                                    bVar19 = bVar19 | 4;
                                                }
                                                if ((*(uint*)((char*)this->ptr_LogicLayer
                                                         + *(int*)((int)((char*)this
                                                                             ->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                               + 0x10)
                                                             * 4
                                                         + this->DAT_SomeTile * 4 + 4)
                                                        & 0x100031)
                                                    != 0) {
                                                    bVar19 = bVar19 | 0x10;
                                                }
                                                this->bitFlag = ~bVar19 & 0x55;
                                            }
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
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::propagateCliffEdgeFlagFromNeighbor,
                                                this)(this->DAT_SomeTile, iVar17, this->DAT_SomeY);
                                            if (this->Logic2Layer[this->DAT_SomeTile] == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (short)GMTotalPicturesProcessed::instance[5] + 0x214
                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                for (local_14 = 0; local_14 < 7; local_14 = local_14 + 1) {
                                                    if (DAT_TerrainDefinedData::instance.field2298_0x1d64[local_14].unk1
                                                        == this->bitFlag) {
                                                        this->bitFlag = 0;
                                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                 + this->DAT_SomeTile * 4 + 4)
                                                                & 0x200000)
                                                            != 0) {
                                                            this->bitFlag = 0x20;
                                                        }
                                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                 + this->DAT_SomeTile * 4 + -4)
                                                                & 0x200000)
                                                            != 0) {
                                                            this->bitFlag = this->bitFlag | 2;
                                                        }
                                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                 + *(int*)((char*)this
                                                                               ->ptr_MovementDirectionTranslationMatrix
                                                                       + this->DAT_SomeY * 0x20)
                                                                     * 4
                                                                 + this->DAT_SomeTile * 4)
                                                                & 0x200000)
                                                            != 0) {
                                                            this->bitFlag = this->bitFlag | 0x80;
                                                        }
                                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                                 + *(int*)((int)((char*)this
                                                                                     ->ptr_MovementDirectionTranslationMatrix
                                                                               + this->DAT_SomeY * 0x20)
                                                                       + 0x10)
                                                                     * 4
                                                                 + this->DAT_SomeTile * 4)
                                                                & 0x200000)
                                                            != 0) {
                                                            this->bitFlag = this->bitFlag | 8;
                                                        }
                                                        sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                                        if (local_14 < 4) {
                                                            if (this->bitFlag == 0) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x234
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .field2298_0x1d64[local_14]
                                                                          .unk2;
                                                            } else {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x2dc
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (ushort)DAT_TerrainDefinedData::instance
                                                                          .field2298_0x1d64[local_14]
                                                                          .unk2;
                                                            }
                                                        } else if (this->bitFlag == 0) {
                                                            if (local_14 == 4) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x254
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else if (local_14 == 5) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x274
                                                                    + (ushort)this->LuminesenceLayer[this->DAT_SomeTile]
                                                                        * 4
                                                                    + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            } else if (local_14 == 6) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x294
                                                                    + (ushort)this
                                                                          ->LuminesenceLayer[this->DAT_SomeTile];
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 0x20) != 0) {
                                                sVar4 = (this->WallGFXLayer[this->DAT_SomeTile] & 8) * 8 + 0x38d;
                                                sVar5 = (short)GMTotalPicturesProcessed::instance[5];
                                                if (this->mapOrientation == 0) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + (short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                              >> 5)
                                                            * 8;
                                                } else if (this->mapOrientation == 2) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 2U
                                                              & 7)
                                                            * 8;
                                                } else if (this->mapOrientation == 4) {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 4U
                                                              & 7)
                                                            * 8;
                                                } else {
                                                    this->GfxLayer[this->DAT_SomeTile] = sVar5 + sVar4 + -1
                                                        + ((short)((int)(this->WallGFXLayer[this->DAT_SomeTile] & 0x3e0)
                                                               >> 5)
                                                                  - 6U
                                                              & 7)
                                                            * 8;
                                                }
                                            }
                                            sVar4 = (short)GMTotalPicturesProcessed::instance[5];
                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 0x50) == 0) {
                                                if (((int)(char)this->Logic2Layer[this->DAT_SomeTile] & 0x88U) == 0) {
                                                    if ((this->Logic2Layer[this->DAT_SomeTile] & 1) == 0) {
                                                        if ((this->Logic2Layer[this->DAT_SomeTile] & 2) == 0) {
                                                            if ((this->Logic2Layer[this->DAT_SomeTile] & 4) != 0) {
                                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x41c;
                                                            }
                                                        } else {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x414;
                                                        }
                                                    } else {
                                                        this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x40c;
                                                    }
                                                } else {
                                                                                                        _gfxLayer = (char*)this->ptr_LogicLayer;
                                                    _gfxTile = this->DAT_SomeTile;
                                                    _gfxY = this->DAT_SomeY;
                                                    MACRO_GFX_NEIGHBOUR_MASK(m4, 4, MACRO_GFX_SHIFT_4, MACRO_GFX_ROWSTEP_4, 1)
                                                    bVar19 = this->bitFlag;
                                                    bVar16 = 0;
                                                    if ((*(uint*)((char*)this->ptr_TerrainTypeTileMap
                                                             + this->DAT_SomeTile + 1)
                                                            & 0x50)
                                                        != 0) {
                                                        bVar16 = 0x20;
                                                    }
                                                    if ((*(uint*)((char*)this->ptr_TerrainTypeTileMap
                                                             + this->DAT_SomeTile + -1)
                                                            & 0x50)
                                                        != 0) {
                                                        bVar16 = bVar16 | 2;
                                                    }
                                                    puVar18 = (uint*)((char*)this->ptr_TerrainTypeTileMap
                                                        + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                            + this->DAT_SomeY * 0x20)
                                                        + this->DAT_SomeTile);
                                                    if ((*(uint*)((int)puVar18 + -1) & 0x50) != 0) {
                                                        bVar16 = bVar16 | 1;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 1) & 0x50) != 0) {
                                                        bVar16 = bVar16 | 0x40;
                                                    }
                                                    if ((*puVar18 & 0x50) != 0) {
                                                        bVar16 = bVar16 | 0x80;
                                                    }
                                                    puVar18 = (uint*)((char*)this->ptr_TerrainTypeTileMap
                                                        + *(int*)((int)((char*)this
                                                                            ->ptr_MovementDirectionTranslationMatrix
                                                                      + this->DAT_SomeY * 0x20)
                                                            + 0x10)
                                                        + this->DAT_SomeTile);
                                                    if ((*(uint*)((int)puVar18 + -1) & 0x50) != 0) {
                                                        bVar16 = bVar16 | 4;
                                                    }
                                                    if ((*(uint*)((int)puVar18 + 1) & 0x50) != 0) {
                                                        bVar16 = bVar16 | 0x10;
                                                    }
                                                    if ((*puVar18 & 0x50) != 0) {
                                                        bVar16 = bVar16 | 8;
                                                    }
                                                    this->bitFlag = bVar16 | bVar19;
                                                    local_c0 = 0xffffffff;
                                                    if (this->bitFlag == 0) {
                                                                                                                _gfxLayer = (char*)this->ptr_LogicLayer;
                                                        _gfxTile = this->DAT_SomeTile;
                                                        _gfxY = this->DAT_SomeY;
                                                        MACRO_GFX_NEIGHBOUR_MASK(m5, 4, MACRO_GFX_SHIFT_4, MACRO_GFX_ROWSTEP_4, 0x100000)
                                                        if (this->bitFlag != 0) {
                                                            for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
                                                                if ((((uint)this->bitFlag
                                                                         & 1 << ((byte)local_14 & 0x1f))
                                                                        != 0)
                                                                    && (this->HeightLayer[this->DAT_SomeTile
                                                                            + this->directionTranslationMatrix
                                                                                [this->DAT_SomeY]
                                                                                [DAT_TerrainDefinedData::instance
                                                                                        .field2475_0x370c[local_14]]]
                                                                        <= this->HeightLayer[this->DAT_SomeTile])) {
                                                                    this->bitFlag = this->bitFlag
                                                                        & ~(byte)(1 << ((byte)local_14 & 0x1f));
                                                                }
                                                            }
                                                            if (this->bitFlag != 0) {
                                                                if ((this->bitFlag & 0x80) == 0) {
                                                                    if ((this->bitFlag & 0x20) == 0) {
                                                                        if ((this->bitFlag & 8) == 0) {
                                                                            if ((this->bitFlag & 2) == 0) {
                                                                                if (this->bitFlag == 0x41) {
                                                                                    local_c0 = 4;
                                                                                } else if (this->bitFlag == 0x50) {
                                                                                    local_c0 = 6;
                                                                                } else if (this->bitFlag == 0x14) {
                                                                                    local_c0 = 0;
                                                                                } else if (this->bitFlag == 5) {
                                                                                    local_c0 = 2;
                                                                                } else if ((this->bitFlag & 0x40)
                                                                                    == 0) {
                                                                                    if ((this->bitFlag & 1) == 0) {
                                                                                        if ((this->bitFlag & 4) == 0) {
                                                                                            if ((this->bitFlag & 0x10)
                                                                                                != 0) {
                                                                                                local_c0 = 7;
                                                                                            }
                                                                                        } else {
                                                                                            local_c0 = 1;
                                                                                        }
                                                                                    } else {
                                                                                        local_c0 = 3;
                                                                                    }
                                                                                } else {
                                                                                    local_c0 = 5;
                                                                                }
                                                                            } else if ((this->bitFlag & 0x80) == 0) {
                                                                                if ((this->bitFlag & 8) == 0) {
                                                                                    if ((this->bitFlag & 5) == 5) {
                                                                                        local_c0 = 2;
                                                                                    } else {
                                                                                        local_c0 = 2;
                                                                                    }
                                                                                } else {
                                                                                    local_c0 = 1;
                                                                                }
                                                                            } else {
                                                                                local_c0 = 3;
                                                                            }
                                                                        } else if ((this->bitFlag & 2) == 0) {
                                                                            if ((this->bitFlag & 0x20) == 0) {
                                                                                if ((this->bitFlag & 0x14) == 0x14) {
                                                                                    local_c0 = 0;
                                                                                } else {
                                                                                    local_c0 = 0;
                                                                                }
                                                                            } else {
                                                                                local_c0 = 7;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 1;
                                                                        }
                                                                    } else if ((this->bitFlag & 8) == 0) {
                                                                        if ((this->bitFlag & 0x80) == 0) {
                                                                            if ((this->bitFlag & 0x50) == 0x50) {
                                                                                local_c0 = 6;
                                                                            } else {
                                                                                local_c0 = 6;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 5;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 7;
                                                                    }
                                                                } else if ((this->bitFlag & 0x20) == 0) {
                                                                    if ((this->bitFlag & 2) == 0) {
                                                                        if ((this->bitFlag & 0x41) == 0x41) {
                                                                            local_c0 = 4;
                                                                        } else {
                                                                            local_c0 = 4;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 3;
                                                                    }
                                                                } else {
                                                                    local_c0 = 5;
                                                                }
                                                                local_c0 = ((local_c0 - this->mapOrientation) + 8) % 8;
                                                                this->GfxLayer[this->DAT_SomeTile]
                                                                    = sVar4 + 0x30c + (short)(local_c0 << 4);
                                                            }
                                                        }
                                                        if (local_c0 == 0xffffffff) {
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            this->Logic2Layer[this->DAT_SomeTile]
                                                                = this->Logic2Layer[this->DAT_SomeTile] & 0x7f;
                                                        }
                                                    } else {
                                                        if ((this->bitFlag & 0x80) == 0) {
                                                            if ((this->bitFlag & 0x20) == 0) {
                                                                if ((this->bitFlag & 8) == 0) {
                                                                    if ((this->bitFlag & 2) == 0) {
                                                                        if (this->bitFlag == 0x40) {
                                                                            local_c0 = 5;
                                                                        } else if (this->bitFlag == 1) {
                                                                            local_c0 = 3;
                                                                        } else if (this->bitFlag == 4) {
                                                                            local_c0 = 1;
                                                                        } else if (this->bitFlag == 0x10) {
                                                                            local_c0 = 7;
                                                                        } else if (this->bitFlag == 0x41) {
                                                                            local_c0 = 4;
                                                                        } else if (this->bitFlag == 0x50) {
                                                                            local_c0 = 6;
                                                                        } else if (this->bitFlag == 0x14) {
                                                                            local_c0 = 0;
                                                                        } else if (this->bitFlag == 5) {
                                                                            local_c0 = 2;
                                                                        }
                                                                    } else if ((this->bitFlag & 0x80) == 0) {
                                                                        if ((this->bitFlag & 8) == 0) {
                                                                            if ((this->bitFlag & 5) == 5) {
                                                                                local_c0 = 2;
                                                                            } else {
                                                                                local_c0 = 2;
                                                                            }
                                                                        } else {
                                                                            local_c0 = 1;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 3;
                                                                    }
                                                                } else if ((this->bitFlag & 2) == 0) {
                                                                    if ((this->bitFlag & 0x20) == 0) {
                                                                        if ((this->bitFlag & 0x14) == 0x14) {
                                                                            local_c0 = 0;
                                                                        } else {
                                                                            local_c0 = 0;
                                                                        }
                                                                    } else {
                                                                        local_c0 = 7;
                                                                    }
                                                                } else {
                                                                    local_c0 = 1;
                                                                }
                                                            } else if ((this->bitFlag & 8) == 0) {
                                                                if ((this->bitFlag & 0x80) == 0) {
                                                                    if ((this->bitFlag & 0x50) == 0x50) {
                                                                        local_c0 = 6;
                                                                    } else {
                                                                        local_c0 = 6;
                                                                    }
                                                                } else {
                                                                    local_c0 = 5;
                                                                }
                                                            } else {
                                                                local_c0 = 7;
                                                            }
                                                        } else if ((this->bitFlag & 0x20) == 0) {
                                                            if ((this->bitFlag & 2) == 0) {
                                                                if ((this->bitFlag & 0x41) == 0x41) {
                                                                    local_c0 = 4;
                                                                } else {
                                                                    local_c0 = 4;
                                                                }
                                                            } else {
                                                                local_c0 = 3;
                                                            }
                                                        } else {
                                                            local_c0 = 5;
                                                        }
                                                        if (local_c0 == 0xffffffff) {
                                                            this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x214
                                                                + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                                + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                            this->Logic2Layer[this->DAT_SomeTile]
                                                                = this->Logic2Layer[this->DAT_SomeTile] & 0x7f;
                                                        } else {
                                                            uVar12 = ((local_c0 - this->mapOrientation) + 8) % 8;
                                                            this->GfxLayer[this->DAT_SomeTile]
                                                                = sVar4 + 0x30c + (short)(uVar12 << 4);
                                                        }
                                                    }
                                                }
                                            } else {
                                                this->GfxLayer[this->DAT_SomeTile] = sVar4 + 0x2fc;
                                            }
                                        }
                                    LAB_005109e8:
                                        if ((this->LogicLayer[this->DAT_SomeTile] & 0x10000100U) != 0) {
                                            bVar19 = this->DefaultHeightLayer[this->DAT_SomeTile];
                                            iVar17 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::TileMapState_Func::computeClimbRampRotation, this)(
                                                this->DAT_SomeTile, (uint)((int)(iVar17)),
                                                (uint)((int)(this->DAT_SomeY)));
                                            sVar5 = (short)GMTotalPicturesProcessed::instance[9];
                                            sVar4 = (short)this->field112_0x554908;
                                            if (this->DefaultHeightLayer[this->DAT_SomeTile] < 0x88) {
                                                if (iVar17 == 0) {
                                                    if ((this->Logic2Layer[this->DAT_SomeTile] & 2) == 0) {
                                                        this->PillarGFXLayer[this->DAT_SomeTile]
                                                            = (short)(((((int)(uint)bVar19 >> 3) + -1) * 0x40) / 2)
                                                            + (short)GMTotalPicturesProcessed::instance[3]
                                                            + (ushort)this->LuminesenceLayer[this->DAT_SomeTile] * 4
                                                            + (this->RandomLayer[this->DAT_SomeTile] & 3);
                                                    } else {
                                                        this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                    }
                                                } else {
                                                    this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                                }
                                            } else {
                                                this->PillarGFXLayer[this->DAT_SomeTile] = sVar5 + -1 + sVar4;
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x800;
                                            }
                                        }
                                    } else {
                                        this->Logic2Layer[this->DAT_SomeTile]
                                            = this->Logic2Layer[this->DAT_SomeTile] & 0xf7;
                                        this->bitFlag = 0;
                                        if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + 4)
                                                & 0x100000)
                                            != 0) {
                                            this->bitFlag = 0x20;
                                        }
                                        if ((*(uint*)((char*)this->ptr_LogicLayer + this->DAT_SomeTile * 4 + -4)
                                                & 0x100000)
                                            != 0) {
                                            this->bitFlag = this->bitFlag | 2;
                                        }
                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                 + *(int*)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                       + this->DAT_SomeY * 0x20)
                                                     * 4
                                                 + this->DAT_SomeTile * 4)
                                                & 0x100000)
                                            != 0) {
                                            this->bitFlag = this->bitFlag | 0x80;
                                        }
                                        if ((*(uint*)((char*)this->ptr_LogicLayer
                                                 + *(int*)((int)((char*)this->ptr_MovementDirectionTranslationMatrix
                                                               + this->DAT_SomeY * 0x20)
                                                       + 0x10)
                                                     * 4
                                                 + this->DAT_SomeTile * 4)
                                                & 0x100000)
                                            != 0) {
                                            this->bitFlag = this->bitFlag | 8;
                                        }
                                        if (this->bitFlag == 0) {
                                            if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0) == 0) {
                                                                                                _gfxLayer = (char*)this->ptr_MiscDisplayLayer;
                                                _gfxTile = this->DAT_SomeTile;
                                                _gfxY = this->DAT_SomeY;
                                                MACRO_GFX_NEIGHBOUR_MASK(m6, 2, MACRO_GFX_SHIFT_2, MACRO_GFX_ROWSTEP_2, 0x40)
                                                bVar19 = this->bitFlag;
                                                                                                _gfxLayer = (char*)this->ptr_MiscDisplayLayer;
                                                _gfxTile = this->DAT_SomeTile;
                                                _gfxY = this->DAT_SomeY;
                                                MACRO_GFX_NEIGHBOUR_MASK(m7, 2, MACRO_GFX_SHIFT_2, MACRO_GFX_ROWSTEP_2, 0x80)
                                                bVar16 = this->bitFlag;
                                                this->bitFlag = bVar16 & ~bVar19;
                                                if (this->bitFlag != 0) {
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[0xa6] + 0x5c4;
                                                    this->PillarGFXLayer[this->DAT_SomeTile]
                                                        = (ushort)GMTotalPicturesProcessed::instance[9];
                                                    this->MiscDisplayLayer[this->DAT_SomeTile]
                                                        = this->MiscDisplayLayer[this->DAT_SomeTile] | 0xc0;
                                                }
                                            }
                                            if (2 < this->LuminesenceLayer[this->DAT_SomeTile]) {
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xffbf;
                                                this->MiscDisplayLayer[this->DAT_SomeTile]
                                                    = this->MiscDisplayLayer[this->DAT_SomeTile] & 0xff7f;
                                            }
                                            local_38 = this->LuminesenceLayer[this->DAT_SomeTile] - 2;
                                            if (local_38 < 0) {
                                                local_38 = 0;
                                            }
                                            sVar4 = (short)local_38;
                                            if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0xc0) == 0) {
                                                if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x100) == 0) {
                                                                                                        _gfxLayer = (char*)this->ptr_MiscDisplayLayer;
                                                    _gfxTile = this->DAT_SomeTile;
                                                    _gfxY = this->DAT_SomeY;
                                                    MACRO_GFX_NEIGHBOUR_MASK(m8, 2, MACRO_GFX_SHIFT_2, MACRO_GFX_ROWSTEP_2, 0x100)
                                                    if (this->bitFlag != 0) {
                                                        local_ac = 2;
                                                        uVar12 = (uint)this->bitFlag
                                                            << ((byte)this->mapOrientation & 0x1f);
                                                        uVar12 = uVar12 & 0xff | (int)uVar12 >> 8;
                                                        switch (uVar12) {
                                                        case 1:
                                                            local_b0 = 0x1c;
                                                            break;
                                                        case 2:
                                                        case 3:
                                                        case 6:
                                                        case 7:
                                                            local_b0 = 0xc;
                                                            local_ac = 4;
                                                            break;
                                                        case 4:
                                                            local_b0 = 0x1a;
                                                            break;
                                                        default:
                                                            local_b4 = 0;
                                                            for (local_b8 = 0; local_b8 < 8; local_b8 = local_b8 + 1) {
                                                                if ((1 << ((byte)local_b8 & 0x1f) & uVar12) != 0) {
                                                                    local_b4 = local_b4 + 1;
                                                                }
                                                            }
                                                            if (local_b4 < 4) {
                                                                local_b0 = 0x20;
                                                            } else {
                                                                local_b0 = 0x21;
                                                            }
                                                            local_ac = 1;
                                                            break;
                                                        case 8:
                                                        case 0xc:
                                                        case 0x18:
                                                        case 0x1c:
                                                            local_b0 = 8;
                                                            local_ac = 4;
                                                            break;
                                                        case 0xe:
                                                        case 0xf:
                                                        case 0x1e:
                                                        case 0x1f:
                                                            local_b0 = 0x16;
                                                            break;
                                                        case 0x10:
                                                            local_b0 = 0x18;
                                                            break;
                                                        case 0x20:
                                                        case 0x30:
                                                        case 0x60:
                                                        case 0x70:
                                                            local_b0 = 4;
                                                            local_ac = 4;
                                                            break;
                                                        case 0x38:
                                                        case 0x3c:
                                                        case 0x78:
                                                        case 0x7c:
                                                            local_b0 = 0x14;
                                                            break;
                                                        case 0x40:
                                                            local_b0 = 0x1e;
                                                            break;
                                                        case 0x80:
                                                        case 0x81:
                                                        case 0xc0:
                                                        case 0xc1:
                                                            local_b0 = 0;
                                                            local_ac = 4;
                                                            break;
                                                        case 0x83:
                                                        case 0x87:
                                                        case 0xc3:
                                                        case 199:
                                                            local_b0 = 0x10;
                                                            break;
                                                        case 0xe0:
                                                        case 0xe1:
                                                        case 0xf0:
                                                        case 0xf1:
                                                            local_b0 = 0x12;
                                                        }
                                                        this->GfxLayer[this->DAT_SomeTile]
                                                            = (short)GMTotalPicturesProcessed::instance[0xa6]
                                                            + (short)((int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                % local_ac)
                                                            + local_b0 + 8 + sVar4 * 0xf6;
                                                        this->MiscDisplayLayer[this->DAT_SomeTile]
                                                            = this->MiscDisplayLayer[this->DAT_SomeTile] | 0x200;
                                                    }
                                                } else {
                                                    local_94 = 2;
                                                    uVar15 = (int)this->CertainPathLayer[this->DAT_SomeTile] & 0xff;
                                                    uVar12 = uVar15 << ((byte)this->mapOrientation & 0x1f);
                                                    uVar12 = uVar12 & 0xff | (int)uVar12 >> 8;
                                                    switch (uVar12) {
                                                    case 1:
                                                        local_9c = 0x1c;
                                                        break;
                                                    case 2:
                                                    case 3:
                                                    case 6:
                                                    case 7:
                                                        local_9c = 0xc;
                                                        local_94 = 4;
                                                        break;
                                                    case 4:
                                                        local_9c = 0x1a;
                                                        break;
                                                    default:
                                                        local_a0 = 0;
                                                        for (local_a4 = 0; local_a4 < 8; local_a4 = local_a4 + 1) {
                                                            if ((1 << ((byte)local_a4 & 0x1f) & uVar12) != 0) {
                                                                local_a0 = local_a0 + 1;
                                                            }
                                                        }
                                                        if (local_a0 < 4) {
                                                            local_9c = 0x20;
                                                        } else {
                                                            local_9c = 0x21;
                                                        }
                                                        local_94 = 1;
                                                        break;
                                                    case 8:
                                                    case 0xc:
                                                    case 0x18:
                                                    case 0x1c:
                                                        local_9c = 8;
                                                        local_94 = 4;
                                                        break;
                                                    case 0xe:
                                                    case 0xf:
                                                    case 0x1e:
                                                    case 0x1f:
                                                        local_9c = 0x16;
                                                        break;
                                                    case 0x10:
                                                        local_9c = 0x18;
                                                        break;
                                                    case 0x20:
                                                    case 0x30:
                                                    case 0x60:
                                                    case 0x70:
                                                        local_9c = 4;
                                                        local_94 = 4;
                                                        break;
                                                    case 0x38:
                                                    case 0x3c:
                                                    case 0x78:
                                                    case 0x7c:
                                                        local_9c = 0x14;
                                                        break;
                                                    case 0x40:
                                                        local_9c = 0x1e;
                                                        break;
                                                    case 0x80:
                                                    case 0x81:
                                                    case 0xc0:
                                                    case 0xc1:
                                                        local_9c = 0;
                                                        local_94 = 4;
                                                        break;
                                                    case 0x83:
                                                    case 0x87:
                                                    case 0xc3:
                                                    case 199:
                                                        local_9c = 0x10;
                                                        break;
                                                    case 0xe0:
                                                    case 0xe1:
                                                    case 0xf0:
                                                    case 0xf1:
                                                        local_9c = 0x12;
                                                    }
                                                    local_9c = (short)((int)(short)this->RandomLayer[this->DAT_SomeTile]
                                                                   % local_94)
                                                        + local_9c;
                                                    if (uVar15
                                                        != ((int)this->CertainPathLayer[this->DAT_SomeTile] >> 8
                                                            & 0xffU)) {
                                                        local_9c = local_9c + 0x66;
                                                    }
                                                    this->GfxLayer[this->DAT_SomeTile]
                                                        = (short)GMTotalPicturesProcessed::instance[0xa6] + local_9c
                                                        + 0x2a + sVar4 * 0xf6;
                                                }
                                            }
                                            if ((this->MiscDisplayLayer[this->DAT_SomeTile] & 0x3c0) == 0) {
                                                this->GfxLayer[this->DAT_SomeTile]
                                                    = (this->RandomLayer[this->DAT_SomeTile] & 7)
                                                    + (short)GMTotalPicturesProcessed::instance[0xa6] + sVar4 * 0xf6;
                                                this->PillarGFXLayer[this->DAT_SomeTile]
                                                    = (ushort)GMTotalPicturesProcessed::instance[9];
                                            }
                                        } else {
                                            this->GfxLayer[this->DAT_SomeTile]
                                                = (short)GMTotalPicturesProcessed::instance[5] + 0x2fc;
                                            this->Logic2Layer[this->DAT_SomeTile]
                                                = this->Logic2Layer[this->DAT_SomeTile] | 8;
                                        }
                                    }
                                }
                            LAB_0050c199:
                                this->DAT_SomeX = this->DAT_SomeX + 1;
                            }
                        }
                    }
                }
            }
        }
        return;
    }

}
}

#pragma optimize("", on)
