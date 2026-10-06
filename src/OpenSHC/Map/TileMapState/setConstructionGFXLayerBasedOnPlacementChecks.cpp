
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Type propagation algorithm not settling
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00504F10
    int TileMapState::setConstructionGFXLayerBasedOnPlacementChecks(int x, int y, MappersEnum type, int size)
    {
        int iVar1;
        BuildingType BVar2;
        undefined2 uVar8;
        int iVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        ushort uVar9;
        MappersEnum MVar10;
        XYPair* pXVar11;
        int* piVar12;
        int iVar13;
        int iVar14;
        int iVar15;
        int local_14;
        int _offset;
        short sprite;
        short command;
        iVar1 = x;
        command = (short)type;
        iVar14 = this->field188_0x554a14;
        local_14 = 0;
        this->field188_0x554a14 = 0;
        if (iVar14 != 0) {
            BVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)((MappersEnum)command);
            this->buildingSpriteSheetID_1 = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[BVar2].intValue;
            this->buildingSpriteID1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID,
                DAT_BuildingsState::ptr)((MappersEnum)command);
            this->buildingSpriteID2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID2,
                DAT_BuildingsState::ptr)((MappersEnum)command);
        } else {
            if (this->buildingPlacementFail == 2) {
                this->field188_0x554a14 = 0;
                return (int)(2);
            }
            if (this->buildingPlacementFail != FALSE) {
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        local_14, size);
                    iVar14 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                        + this->buildingX + x;
                    if ((this->LogicLayer[iVar14] & 0x10000500U) == 0) {
                        iVar15 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar14, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                            (MappersEnum)command, 0);
                        this->ConstructionGFXLayer[iVar14] = (-(ushort)(iVar15 != 0) & 0xfff9) + 0x3e;
                    }
                    local_14 = local_14 + 1;
                } while (local_14 < this->constructionTileCount);
                uVar8 = (undefined2)((uint)local_14 >> 0x10);
                if (((command == OpenSHC::Commands::M_MAPPER_KEEP1) || (command == OpenSHC::Commands::M_MAPPER_KEEP2))
                    || (command == OpenSHC::Commands::M_MAPPER_KEEP3)) {
                    piVar12
                        = (int*)((int)DAT_TerrainDefinedData::ptr + ((short)command + -0x3c) * 0x60 + 0x264);
                    x = 3;
                    do {
                        iVar14 = DAT_ViewportRenderState::instance.translationMatrix[piVar12[1] + y].addXgetTile
                            + *piVar12 + iVar1;
                        if ((this->LogicLayer[iVar14] & 0x10000500U) == 0) {
                            iVar15
                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                    this)(iVar14, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                    (MappersEnum)command, 0);
                            this->ConstructionGFXLayer[iVar14] = (-(ushort)(iVar15 != 0) & 0xfff9) + 0x3e;
                        }
                        piVar12 = piVar12 + 2;
                        x = x + -1;
                    } while (x != 0);
                    iVar3 = ((short)command + -0x3c) * 0x20;
                    iVar14 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar3 + 900);
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar3 + 0x388);
                    local_14 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            local_14, 7);
                        iVar13 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y + iVar15]
                                     .addXgetTile
                            + this->buildingX + iVar1 + iVar14;
                        if ((this->LogicLayer[iVar13] & 0x10000500U) == 0) {
                            iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                this)(iVar13, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                (MappersEnum)command, 0);
                            this->ConstructionGFXLayer[iVar13] = (-(ushort)(iVar4 != 0) & 0xfff9) + 0x3e;
                        }
                        local_14 = local_14 + 1;
                    } while (local_14 < this->constructionTileCount);
                    iVar14 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar3 + 0x3e4);
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar3 + 1000);
                    iVar3 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar3, 5);
                        iVar13 = this->buildingY + iVar15 + y;
                        iVar4 = DAT_ViewportRenderState::instance.translationMatrix[iVar13].addXgetTile
                            + this->buildingX + iVar14 + iVar1;
                        if ((this->LogicLayer[iVar4] & 0x10000500U) == 0) {
                            iVar13
                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                    this)(iVar4, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                    (MappersEnum)command, 0);
                            iVar13 = (-(uint)(iVar13 != 0) & 0xfffffff9) + 0x3e;
                            this->ConstructionGFXLayer[iVar4] = (ushort)iVar13;
                        }
                        uVar8 = (undefined2)((uint)iVar13 >> 0x10);
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < this->constructionTileCount);
                }
                if (((command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A) || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B))
                    || ((command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D)))) {
                    MVar10 = (MappersEnum)command;
                    iVar14 = MVar10 * 3 + -0x1a4;
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar14 * 8 + 0x56c);
                    iVar14 = iVar14 * 8;
                    iVar3 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar14 + 0x570);
                    iVar13 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar13, 3);
                        iVar5 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + iVar3 + y]
                                    .addXgetTile
                            + this->buildingX + iVar15 + iVar1;
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar5, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), MVar10, 0);
                        iVar13 = iVar13 + 1;
                        this->ConstructionGFXLayer[iVar5] = (-(ushort)(iVar4 != 0) & 0xfff9) + 0x3e;
                    } while (iVar13 < this->constructionTileCount);
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar14 + 0x578);
                    iVar14 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar14 + 0x57c);
                    iVar3 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar3, 3);
                        iVar4 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + iVar14 + y]
                                    .addXgetTile
                            + this->buildingX + iVar15 + iVar1;
                        iVar13 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar4, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), MVar10, 0);
                        iVar3 = iVar3 + 1;
                        this->ConstructionGFXLayer[iVar4] = (-(ushort)(iVar13 != 0) & 0xfff9) + 0x3e;
                    } while (iVar3 < this->constructionTileCount);
                    piVar12 = (int*)((int)DAT_TerrainDefinedData::ptr + (MVar10 * 3 + -0x1a4) * 0x10 + 0x5cc);
                    type = OpenSHC::Commands::M_MAPPER_FOREST;
                    do {
                        iVar15 = DAT_ViewportRenderState::instance.translationMatrix[piVar12[1] + y].addXgetTile
                            + *piVar12 + iVar1;
                        iVar14 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                            iVar15, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), MVar10, 0);
                        iVar14 = (-(uint)(iVar14 != 0) & 0xfffffff9) + 0x3e;
                        piVar12 = piVar12 + 2;
                        type = (MappersEnum)(type - OpenSHC::Commands::M_MAPPER_AREA);
                        this->ConstructionGFXLayer[iVar15] = (ushort)iVar14;
                    } while (type != OpenSHC::Commands::M_MAPPER_NULL);
                    return iVar14;
                }
                if ((command == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO) || (command == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB)) {
                    iVar14 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar14, 5);
                        iVar3 = this->buildingX;
                        iVar15 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile;
                        if ((this->LogicLayer[iVar1 + this->buildingX + iVar15 + 5] & 0x10000500U) == 0) {
                            iVar13
                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                    this)(iVar15 + this->buildingX + iVar1 + 5,
                                    (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                    (MappersEnum)command, 0);
                            this->ConstructionGFXLayer[iVar1 + iVar3 + iVar15 + 5]
                                = (-(ushort)(iVar13 != 0) & 0xfff9) + 0x3e;
                        }
                        iVar14 = iVar14 + 1;
                    } while (iVar14 < this->constructionTileCount);
                    iVar14 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar14, 5);
                        iVar15
                            = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5].addXgetTile
                            + this->buildingX + iVar1;
                        if ((this->LogicLayer[iVar15] & 0x10000500U) == 0) {
                            iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                this)(iVar15, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                (MappersEnum)command, 0);
                            this->ConstructionGFXLayer[iVar15] = (-(ushort)(iVar3 != 0) & 0xfff9) + 0x3e;
                        }
                        iVar14 = iVar14 + 1;
                    } while (iVar14 < this->constructionTileCount);
                    iVar14 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar14, 5);
                        iVar3 = this->buildingX;
                        iVar13 = this->buildingY + y + 5;
                        iVar15
                            = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5].addXgetTile;
                        if ((this->LogicLayer[iVar1 + this->buildingX + iVar15 + 5] & 0x10000500U) == 0) {
                            iVar13
                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                    this)(iVar15 + this->buildingX + iVar1 + 5,
                                    (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                    (MappersEnum)command, 0);
                            iVar13 = (-(uint)(iVar13 != 0) & 0xfffffff9) + 0x3e;
                            this->ConstructionGFXLayer[iVar1 + iVar3 + iVar15 + 5] = (ushort)iVar13;
                        }
                        iVar14 = iVar14 + 1;
                    } while (iVar14 < this->constructionTileCount);
                    return iVar13;
                }
                if ((command != OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD) && (command != OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD)) {
                    if (command != OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
                        /* the original returns eax with a leftover tile index still in its high half */
                        return (ushort)command;
                    }
                    iVar14 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar14, 4);
                        iVar15 = this->buildingY + y + 4;
                        iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 4].addXgetTile
                            + this->buildingX + iVar1;
                        if ((this->LogicLayer[iVar3] & 0x10000500U) == 0) {
                            iVar15
                                = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                    this)(iVar3, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                    OpenSHC::Commands::M_MAPPER_OIL_SMELTER, 0);
                            iVar15 = (-(uint)(iVar15 != 0) & 0xfffffff9) + 0x3e;
                            this->ConstructionGFXLayer[iVar3] = (ushort)iVar15;
                        }
                        iVar14 = iVar14 + 1;
                    } while (iVar14 < this->constructionTileCount);
                    return iVar15;
                }
                iVar14 = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        iVar14, 5);
                    iVar15 = (this->buildingY + y + 5) * 3;
                    iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5].addXgetTile
                        + this->buildingX + iVar1;
                    if ((this->LogicLayer[iVar3] & 0x10000500U) == 0) {
                        iVar15 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar3, (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                            (MappersEnum)command, 0);
                        iVar15 = (-(uint)(iVar15 != 0) & 0xfffffff9) + 0x3e;
                        this->ConstructionGFXLayer[iVar3] = (ushort)iVar15;
                    }
                    iVar14 = iVar14 + 1;
                } while (iVar14 < this->constructionTileCount);
                return iVar15;
            }
        }
        if (command == OpenSHC::Commands::M_MAPPER_WHEATFARM) {
            size = 3;
        } else if (command == OpenSHC::Commands::M_MAPPER_HOPSFARM) {
            size = 3;
        } else if (command == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
            size = 3;
        } else if (command == OpenSHC::Commands::M_MAPPER_CATTLEFARM) {
            size = 3;
        } else if ((((command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A) || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C))
                       || (command == OpenSHC::Commands::M_MAPPER_GATE_STONE1A))
            || (command == OpenSHC::Commands::M_MAPPER_GATE_STONE2A)) {
            this->field78_0x55488c = 0x51;
        } else if (((command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B) || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D))
            || ((command == OpenSHC::Commands::M_MAPPER_GATE_STONE1B || (command == OpenSHC::Commands::M_MAPPER_GATE_STONE2B)))) {
            this->field78_0x55488c = 0x50;
        }
        MVar10 = (MappersEnum)command;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(local_14, size);
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + iVar1;
            iVar15 = this->uiBuildingRotation;
            if (((this->uiBuildingRotation != 0xf) && (this->uiBuildingRotation != 8))
                && (iVar15 = this->uiBuildingRotation - this->mapOrientation, iVar15 < 0)) {
                iVar15 = iVar15 + 8;
            }
            sprite = (short)this->buildingSpriteID1;
            if ((this->mapOrientation == 2) || (this->mapOrientation == 6)) {
                if (this->field78_0x55488c != 0x51)
                    goto LAB_00505714;
            } else if (this->field78_0x55488c == 0x51) {
            LAB_00505714:
                sprite = (short)this->buildingSpriteID2;
            }
            if ((command == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE) && (iVar15 != 0)) {
                if (iVar15 == 2) {
                    iVar15 = 3;
                } else if (iVar15 == 4) {
                    iVar15 = 2;
                } else if (iVar15 == 6) {
                    iVar15 = 1;
                }
            }
            BVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(MVar10);
            if (BVar2 == OpenSHC::Map::Buildings::BT_UNKNOWN1) {
                sprite = sprite + (short)(&DAT_BuildingDefinedData::instance.field209_0x976c[9].y)[MVar10];
            } else {
                BVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(MVar10);
                if (BVar2 == OpenSHC::Map::Buildings::BT_HOVEL) {
                    sprite = (short)DAT_BuildingDefinedData::instance.SomeSpriteArray1[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .hovelCountUpToEight];
                }
            }
            if (this->uiBuildingRotation == 0xf) {
                this->ConstructionGFXLayer[iVar3]
                    = ((short)GMTotalPicturesProcessed::instance[this->buildingSpriteSheetID_1] + sprite
                          + (short)this->buildingRotationRelatedValue)
                    - 1;
            } else {
                this->ConstructionGFXLayer[iVar3]
                    = ((short)(iVar15 * size * size)
                          + (short)GMTotalPicturesProcessed::instance[this->buildingSpriteSheetID_1] + sprite
                          + (short)this->buildingRotationRelatedValue)
                    - 1;
            }
            if (iVar14 != 0) {
                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
            }
            local_14 = local_14 + 1;
            if (this->constructionTileCount <= local_14) {
                iVar15 = (ushort)command;
                if ((((command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A) || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B))
                        || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C))
                    || (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D)) {
                    /*
                      0 3 6 9
                     */
                    _offset = MVar10 * 3 + -420;
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + _offset * 8 + 0x50c);
                    iVar3 = *(int*)((int)DAT_TerrainDefinedData::ptr + _offset * 8 + 0x510);
                    /*
                      0 24 48 72
                     */
                    iVar4 = _offset * 8;
                    iVar13 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 0x514);
                    iVar5 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar5, 2);
                        iVar6 = DAT_ViewportRenderState::instance.translationMatrix[iVar3 + y + this->buildingY]
                                    .addXgetTile
                            + this->buildingX + iVar15 + iVar1;
                        this->ConstructionGFXLayer[iVar6] = (short)this->buildingRotationRelatedValue
                            + (short)GMTotalPicturesProcessed::instance[0x34];
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar6] = this->MiscDisplayLayer[iVar6] | 0x8000;
                        }
                        iVar5 = iVar5 + 1;
                    } while (iVar5 < this->constructionTileCount);
                    pXVar11 = &DAT_TerrainDefinedData::instance.field555_0x68c + iVar13 * 5;
                    iVar5 = 0;
                    do {
                        iVar6 = DAT_ViewportRenderState::instance.translationMatrix[pXVar11->y + iVar3 + y].addXgetTile
                            + pXVar11->x + iVar15 + iVar1;
                        if (iVar5 < 1) {
                            this->ConstructionGFXLayer[iVar6]
                                = (short)GMTotalPicturesProcessed::instance[0x34] + 0x60e + (short)iVar5;
                        } else {
                            iVar7 = DAT_TerrainDefinedData::instance.field600_0x7c8[iVar5 + iVar13 * 4]
                                - this->mapOrientation;
                            if (iVar7 < 0) {
                                iVar7 = iVar7 + 8;
                            }
                            this->ConstructionGFXLayer[iVar6] = (short)GMTotalPicturesProcessed::instance[0x34]
                                + (short)(iVar7 / 2) * 4 + 0x60e + (short)iVar5;
                        }
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar6] = this->MiscDisplayLayer[iVar6] | 0x8000;
                        }
                        iVar5 = iVar5 + 1;
                        pXVar11 = pXVar11 + 1;
                    } while (iVar5 < 5);
                    iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 0x518);
                    iVar3 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 0x51c);
                    iVar13 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 0x520);
                    iVar4 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar4, 2);
                        iVar5 = DAT_ViewportRenderState::instance.translationMatrix[iVar3 + y + this->buildingY]
                                    .addXgetTile
                            + this->buildingX + iVar15 + iVar1;
                        this->ConstructionGFXLayer[iVar5] = (short)this->buildingRotationRelatedValue
                            + (short)GMTotalPicturesProcessed::instance[0x34];
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar5] = this->MiscDisplayLayer[iVar5] | 0x8000;
                        }
                        iVar4 = iVar4 + 1;
                    } while (iVar4 < this->constructionTileCount);
                    pXVar11 = &DAT_TerrainDefinedData::instance.field555_0x68c + iVar13 * 5;
                    iVar4 = 0;
                    do {
                        iVar5 = DAT_ViewportRenderState::instance.translationMatrix[pXVar11->y + iVar3 + y].addXgetTile
                            + pXVar11->x + iVar15 + iVar1;
                        if (iVar4 < 1) {
                            this->ConstructionGFXLayer[iVar5]
                                = (short)GMTotalPicturesProcessed::instance[0x34] + 0x60e + (short)iVar4;
                        } else {
                            iVar6 = DAT_TerrainDefinedData::instance.field600_0x7c8[iVar4 + iVar13 * 4]
                                - this->mapOrientation;
                            if (iVar6 < 0) {
                                iVar6 = iVar6 + 8;
                            }
                            this->ConstructionGFXLayer[iVar5] = (short)GMTotalPicturesProcessed::instance[0x34]
                                + (short)(iVar6 / 2) * 4 + 0x60e + (short)iVar4;
                        }
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar5] = this->MiscDisplayLayer[iVar5] | 0x8000;
                        }
                        iVar4 = iVar4 + 1;
                        pXVar11 = pXVar11 + 1;
                    } while (iVar4 < 5);
                    piVar12 = (int*)((int)DAT_TerrainDefinedData::ptr + (MVar10 * 3 + -0x1a4) * 0x10 + 0x5cc);
                    type = OpenSHC::Commands::M_MAPPER_FOREST;
                    do {
                        iVar15 = DAT_ViewportRenderState::instance.translationMatrix[piVar12[1] + y].addXgetTile + iVar1
                            + *piVar12;
                        this->ConstructionGFXLayer[iVar15] = ((byte)this->RandomLayer[iVar15] & 3) + 0x138
                            + (short)GMTotalPicturesProcessed::instance[6];
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                        }
                        piVar12 = piVar12 + 2;
                        type = (MappersEnum)(type - OpenSHC::Commands::M_MAPPER_AREA);
                    } while (type != OpenSHC::Commands::M_MAPPER_NULL);
                } else {
                    if (command == OpenSHC::Commands::M_MAPPER_WHEATFARM) {
                        iVar15 = 0;
                        do {
                            iVar3 = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .unkWheatFarmOrientation;
                            iVar3 = DAT_ViewportRenderState::instance
                                        .translationMatrix
                                            [DAT_TerrainDefinedData::instance.WheatFarmTiles[iVar3][iVar15].y + y]
                                        .addXgetTile
                                + DAT_TerrainDefinedData::instance.WheatFarmTiles[iVar3][iVar15].x + iVar1;
                            this->ConstructionGFXLayer[iVar3]
                                = ((byte)this->RandomLayer[iVar3] & 3) + (short)GMTotalPicturesProcessed::instance[0xe];
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < 0x24);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_HOPSFARM) {
                        iVar15 = 0;
                        do {
                            iVar3 = *(int*)&DAT_GameState::instance
                                         .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                         .unkHopFarmVariation;
                            iVar3 = DAT_ViewportRenderState::instance
                                        .translationMatrix
                                            [DAT_TerrainDefinedData::instance.HopFarmProperty1[iVar3][iVar15].y + y]
                                        .addXgetTile
                                + DAT_TerrainDefinedData::instance.HopFarmProperty1[iVar3][iVar15].x + iVar1;
                            this->ConstructionGFXLayer[iVar3] = ((byte)this->RandomLayer[iVar3] & 1) * 9 + 0x25
                                + (short)GMTotalPicturesProcessed::instance[0xe];
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < 0x18);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_CATTLEFARM) {
                        iVar15 = 0;
                        do {
                            iVar3 = DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .dairyFarmVariationMod4;
                            iVar13
                                = DAT_ViewportRenderState::instance
                                      .translationMatrix
                                          [DAT_TerrainDefinedData::instance.field1009_0xf5c[iVar3][iVar15 + 4].offset.y
                                              + y]
                                      .addXgetTile
                                + DAT_TerrainDefinedData::instance.field1009_0xf5c[iVar3][iVar15 + 4].offset.x + iVar1;
                            iVar3 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::getRubbleGraphicStageForDamageLevel, this)(
                                DAT_TerrainDefinedData::instance.field1009_0xf5c[iVar3][iVar15 + 4].property);
                            iVar3 = iVar3 + 0x37 + GMTotalPicturesProcessed::instance[0xe];
                            this->ConstructionGFXLayer[iVar13] = (ushort)iVar3;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar13] = this->MiscDisplayLayer[iVar13] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < 0x17);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
                        pXVar11 = DAT_TerrainDefinedData::instance.AppleFarmOffsets;
                        do {
                            iVar15 = DAT_ViewportRenderState::instance.translationMatrix[pXVar11->y + y].addXgetTile
                                + pXVar11->x + iVar1;
                            this->ConstructionGFXLayer[iVar15] = (short)GMTotalPicturesProcessed::instance[0xe] + 0x3d;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                            }
                            pXVar11 = pXVar11 + 1;
                        } while ((int)pXVar11 < 0xb49eb0);
                        return iVar15;
                    }
                    if ((command == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO) || (command == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB)) {
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 5);
                            iVar13 = this->buildingX;
                            iVar3
                                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile;
                            this->ConstructionGFXLayer[iVar1 + this->buildingX + iVar3 + 5]
                                = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x48;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar1 + iVar13 + iVar3 + 5]
                                    = this->MiscDisplayLayer[iVar1 + iVar13 + iVar3 + 5] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 5);
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5]
                                        .addXgetTile
                                + this->buildingX + iVar1;
                            this->ConstructionGFXLayer[iVar3] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x7a;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 5);
                            iVar13 = this->buildingX;
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5]
                                        .addXgetTile;
                            iVar4 = iVar3 + this->buildingX;
                            this->ConstructionGFXLayer[iVar1 + this->buildingX + iVar3 + 5]
                                = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x61;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar1 + iVar13 + iVar3 + 5]
                                    = this->MiscDisplayLayer[iVar1 + iVar13 + iVar3 + 5] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        return iVar4 + iVar1 + 5;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD) {
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 5);
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5]
                                        .addXgetTile
                                + this->buildingX + iVar1;
                            this->ConstructionGFXLayer[iVar3] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x93;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 5);
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 5]
                                        .addXgetTile
                                + this->buildingX + iVar1;
                            this->ConstructionGFXLayer[iVar3] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0xac;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 4);
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[y + this->buildingY + 4]
                                        .addXgetTile
                                + this->buildingX + iVar1;
                            this->ConstructionGFXLayer[iVar3] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x128;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        return iVar3;
                    }
                    if (command == OpenSHC::Commands::M_MAPPER_KEEP1) {
                        uVar9 = (ushort)(this->mapOrientation == 2);
                        iVar15 = DAT_ViewportRenderState::instance
                                     .translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[0][0].y + y]
                                     .addXgetTile
                            + DAT_TerrainDefinedData::instance.field130_0x264[0][0].x + iVar1;
                        this->ConstructionGFXLayer[iVar15]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x523 + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                        }
                        iVar15 = DAT_ViewportRenderState::instance
                                     .translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[0][1].y + y]
                                     .addXgetTile
                            + DAT_TerrainDefinedData::instance.field130_0x264[0][1].x + iVar1;
                        this->ConstructionGFXLayer[iVar15]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x52e + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                        }
                        iVar15 = DAT_ViewportRenderState::instance
                                     .translationMatrix[DAT_TerrainDefinedData::instance.field130_0x264[0][2].y + y]
                                     .addXgetTile
                            + DAT_TerrainDefinedData::instance.field130_0x264[0][2].x + iVar1;
                        this->ConstructionGFXLayer[iVar15]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x527 + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                        }
                        iVar3 = iVar1 + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][0].xOffset;
                        iVar13 = y + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][0].yOffset;
                        iVar15 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar15, 7);
                            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + iVar13]
                                        .addXgetTile
                                + this->buildingX + iVar3;
                            this->ConstructionGFXLayer[iVar4] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x17;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar4] = this->MiscDisplayLayer[iVar4] | 0x8000;
                            }
                            iVar15 = iVar15 + 1;
                        } while (iVar15 < this->constructionTileCount);
                        iVar1 = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][0].xOffset + iVar1;
                        iVar15 = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][0].yOffset + y;
                        iVar3 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar3, 5);
                            iVar13 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + iVar15]
                                         .addXgetTile
                                + this->buildingX + iVar1;
                            this->ConstructionGFXLayer[iVar13] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[7] + 0x19;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar13] = this->MiscDisplayLayer[iVar13] | 0x8000;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < this->constructionTileCount);
                        return iVar13;
                    }
                    if ((command == OpenSHC::Commands::M_MAPPER_KEEP2) || (command == OpenSHC::Commands::M_MAPPER_KEEP3)) {
                        uVar9 = (ushort)(this->mapOrientation == 2);
                        iVar15 = (MVar10 - OpenSHC::Commands::M_MAPPER_KEEP1) * 0x60;
                        iVar3 = DAT_ViewportRenderState::instance
                                    .translationMatrix[*(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x268) + y]
                                    .addXgetTile
                            + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x264) + iVar1;
                        this->ConstructionGFXLayer[iVar3]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x521 + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                        }
                        iVar3 = DAT_ViewportRenderState::instance
                                    .translationMatrix[*(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x270) + y]
                                    .addXgetTile
                            + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x26c) + iVar1;
                        this->ConstructionGFXLayer[iVar3]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x529 + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar3] = this->MiscDisplayLayer[iVar3] | 0x8000;
                        }
                        iVar15 = DAT_ViewportRenderState::instance
                                     .translationMatrix[*(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x278) + y]
                                     .addXgetTile
                            + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar15 + 0x274) + iVar1;
                        this->ConstructionGFXLayer[iVar15]
                            = (short)GMTotalPicturesProcessed::instance[0x34] + 0x525 + uVar9;
                        if (iVar14 != 0) {
                            this->MiscDisplayLayer[iVar15] = this->MiscDisplayLayer[iVar15] | 0x8000;
                        }
                        iVar13 = (MVar10 - OpenSHC::Commands::M_MAPPER_KEEP1) * 0x20;
                        iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar13 + 900);
                        iVar3 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar13 + 0x388);
                        iVar4 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar4, 7);
                            iVar5 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y + iVar3]
                                        .addXgetTile
                                + this->buildingX + iVar1 + iVar15;
                            this->ConstructionGFXLayer[iVar5] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[6] + 0x17;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar5] = this->MiscDisplayLayer[iVar5] | 0x8000;
                            }
                            iVar4 = iVar4 + 1;
                        } while (iVar4 < this->constructionTileCount);
                        iVar15 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar13 + 0x3e4);
                        iVar3 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar13 + 1000);
                        iVar13 = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                iVar13, 5);
                            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + iVar3 + y]
                                        .addXgetTile
                                + this->buildingX + iVar15 + iVar1;
                            this->ConstructionGFXLayer[iVar4] = (short)this->buildingRotationRelatedValue
                                + (short)GMTotalPicturesProcessed::instance[7] + 0x19;
                            if (iVar14 != 0) {
                                this->MiscDisplayLayer[iVar4] = this->MiscDisplayLayer[iVar4] | 0x8000;
                            }
                            iVar13 = iVar13 + 1;
                        } while (iVar13 < this->constructionTileCount);
                        return iVar4;
                    }
                }
                return iVar15;
            }
        } while (true);
    }

}
}
