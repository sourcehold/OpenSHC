#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Location::GateTowerPlacement;

    // FUNCTION: STRONGHOLDCRUSADER 0x00504F10
    void TileMapState::setConstructionGFXLayerBasedOnPlacementChecks(int x, int y, short command, int size)
    {
        int const skipPlacementFailChecks = this->skipPlacementFailChecks;
        int keepSpriteVariant = 0;
        int i = 0;
        int const originX = x;
        int const originY = y;
        this->skipPlacementFailChecks = 0;
        if (skipPlacementFailChecks != 0) {
            BuildingType const buildingType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)((MappersEnum)command);
            this->buildingSpriteSheetID_1
                = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[buildingType].intValue;
            this->buildingSpriteID1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID,
                DAT_BuildingsState::ptr)((MappersEnum)command);
            this->buildingSpriteID2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID2,
                DAT_BuildingsState::ptr)((MappersEnum)command);
        } else {
            if (this->buildingPlacementFail == 2) {
                return;
            }
            if (this->buildingPlacementFail != FALSE) {
                // colour every tile of the footprint by whether it can be built on
                while (true) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, size);
                    int const tile
                        = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + originY].addXgetTile
                        + this->buildingX + originX;
                    if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE)) == 0) {
                        this->ConstructionGFXLayer[tile]
                            = MACRO_CALL_MEMBER(
                                  OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                                  tile, DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                            ? 55
                            : 62;
                    }
                    i++;
                    if (i >= this->constructionTileCount) {
                        break;
                    }
                }
                if (command == OpenSHC::Commands::M_MAPPER_KEEP1 || command == OpenSHC::Commands::M_MAPPER_KEEP2
                    || command == OpenSHC::Commands::M_MAPPER_KEEP3) {
                    int const keepIndex = command - OpenSHC::Commands::M_MAPPER_KEEP1;
                    for (int part = 0; part != 3; part++) {
                        XYPair const& offset = DAT_TerrainDefinedData::instance.field_0x264[keepIndex][part];
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[offset.y + originY].addXgetTile
                            + offset.x + originX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                    }
                    x = originX + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].xOffset;
                    y = originY + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].yOffset;
                    i = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 7);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + x;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        i++;
                        if (i >= this->constructionTileCount) {
                            break;
                        }
                    }
                    x = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].xOffset + originX;
                    y = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].yOffset + originY;
                    int j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + x;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                }
                if (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A
                    || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
                    || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C
                    || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D) {
                    MappersEnum const gateCommand = (MappersEnum)command;
                    int const tower1X = DAT_TerrainDefinedData::instance
                                            .gateTowerChecks[gateCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A]
                                            .x1
                        + originX;
                    int const tower1Y = DAT_TerrainDefinedData::instance
                                            .gateTowerChecks[gateCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A]
                                            .y1
                        + originY;
                    int j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 3);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + tower1Y].addXgetTile
                            + this->buildingX + tower1X;
                        this->ConstructionGFXLayer[tile]
                            = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                  this)(tile, DAT_GameSynchronyState::instance.currentPlayerSlotID, gateCommand, 0)
                            ? 55
                            : 62;
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                    int const tower2X = DAT_TerrainDefinedData::instance
                                            .gateTowerChecks[gateCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A]
                                            .x2
                        + originX;
                    int const tower2Y = DAT_TerrainDefinedData::instance
                                            .gateTowerChecks[gateCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A]
                                            .y2
                        + originY;
                    j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 3);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + tower2Y].addXgetTile
                            + this->buildingX + tower2X;
                        this->ConstructionGFXLayer[tile]
                            = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                  this)(tile, DAT_GameSynchronyState::instance.currentPlayerSlotID, gateCommand, 0)
                            ? 55
                            : 62;
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                    for (int j = 0; j != 6; j++) {
                        int const tile = DAT_ViewportRenderState::instance
                                             .translationMatrix[DAT_TerrainDefinedData::instance
                                                                    .gateHouseTiles[gateCommand
                                                                        - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][j]
                                                                    .y
                                                 + originY]
                                             .addXgetTile
                            + DAT_TerrainDefinedData::instance
                                  .gateHouseTiles[gateCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][j]
                                  .x
                            + originX;
                        this->ConstructionGFXLayer[tile]
                            = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                  this)(tile, DAT_GameSynchronyState::instance.currentPlayerSlotID, gateCommand, 0)
                            ? 55
                            : 62;
                    }
                } else if (command == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO
                    || command == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB) {
                    int const rightX = originX + 5;
                    int j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + originY].addXgetTile
                            + this->buildingX + rightX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                    y = originY + 5;
                    j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + originX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                    j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + rightX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                } else if (command == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD
                    || command == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
                    y = originY + 5;
                    int j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + originX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                } else if (command == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
                    y = originY + 4;
                    int j = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 4);
                        int const tile
                            = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                            + this->buildingX + originX;
                        if ((this->LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_BUILDING | L_WALL_OR_GATEHOUSE))
                            == 0) {
                            this->ConstructionGFXLayer[tile]
                                = MACRO_CALL_MEMBER(
                                      OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(tile,
                                      DAT_GameSynchronyState::instance.currentPlayerSlotID, (MappersEnum)command, 0)
                                ? 55
                                : 62;
                        }
                        j++;
                        if (j >= this->constructionTileCount) {
                            break;
                        }
                    }
                }
                return;
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
        } else if (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C || command == OpenSHC::Commands::M_MAPPER_GATE_STONE1A
            || command == OpenSHC::Commands::M_MAPPER_GATE_STONE2A) {
            this->gateOrientationVariant = 81;
        } else if (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D || command == OpenSHC::Commands::M_MAPPER_GATE_STONE1B
            || command == OpenSHC::Commands::M_MAPPER_GATE_STONE2B) {
            this->gateOrientationVariant = 80;
        }
        MappersEnum const buildingCommand = (MappersEnum)command;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, size);
            int rotation = this->uiBuildingRotation;
            if (rotation != 15 && rotation != 8) {
                rotation -= this->mapOrientation;
                if (rotation < 0) {
                    rotation += 8;
                }
            }
            int sprite;
            if (this->mapOrientation == 2 || this->mapOrientation == 6) {
                if (this->gateOrientationVariant == 81) {
                    sprite = this->buildingSpriteID1;
                } else {
                    sprite = this->buildingSpriteID2;
                }
            } else if (this->gateOrientationVariant == 81) {
                sprite = this->buildingSpriteID2;
            } else {
                sprite = this->buildingSpriteID1;
            }
            if (command == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE && rotation != 0) {
                if (rotation == 2) {
                    rotation = 3;
                } else if (rotation == 4) {
                    rotation = 2;
                } else if (rotation == 6) {
                    rotation = 1;
                }
            }
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + originY].addXgetTile
                + this->buildingX + originX;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(buildingCommand)
                == OpenSHC::Map::Buildings::BT_UNKNOWN1) {
                sprite += DAT_BuildingDefinedData::instance
                              .UnknownVariations[buildingCommand - OpenSHC::Commands::M_MAPPER_UNKNOWN_248];
            } else if (MACRO_CALL_MEMBER(
                           OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                           DAT_BuildingsState::ptr)(buildingCommand)
                == OpenSHC::Map::Buildings::BT_HOVEL) {
                sprite = DAT_BuildingDefinedData::instance.SomeSpriteArray1[DAT_GameState::instance
                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .hovelCountUpToEight];
            }
            if (this->uiBuildingRotation != 15) {
                this->ConstructionGFXLayer[tile] = (short)(rotation * size * size)
                    + (short)GMFirstPictureIndex::instance[this->buildingSpriteSheetID_1] + (short)sprite
                    + (short)this->buildingRotationRelatedValue - 1;
            } else {
                this->ConstructionGFXLayer[tile] = (short)GMFirstPictureIndex::instance[this->buildingSpriteSheetID_1]
                    + (short)sprite + (short)this->buildingRotationRelatedValue - 1;
            }
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile] |= 0x8000;
            }
            i++;
            if (i >= this->constructionTileCount) {
                break;
            }
        }
        if (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D) {
            int const gateIndex = buildingCommand - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A;
            int const tower1X = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].x1;
            int const tower1Y = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].y1;
            int const tower1Rotation = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].rotationIndex1;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 2);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tower1Y + originY + this->buildingY]
                          .addXgetTile
                    + this->buildingX + tower1X + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[52];
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            for (int j = 0; j < 5; j++) {
                XYPair const& offset = DAT_TerrainDefinedData::instance.gateTowerTileOffsets[tower1Rotation][j];
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[offset.y + tower1Y + originY].addXgetTile
                    + offset.x + tower1X + originX;
                if (j <= 0) {
                    this->ConstructionGFXLayer[tile] = GMFirstPictureIndex::instance[52] + j + 1550;
                } else {
                    int towerRotation
                        = DAT_TerrainDefinedData::instance.constructionSpriteRotationTable[tower1Rotation][j - 1]
                        - this->mapOrientation;
                    if (towerRotation < 0) {
                        towerRotation += 8;
                    }
                    this->ConstructionGFXLayer[tile]
                        = GMFirstPictureIndex::instance[52] + (towerRotation / 2) * 4 + j + 1550;
                }
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
            int const tower2X = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].x2;
            int const tower2Y = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].y2;
            int const tower2Rotation = DAT_TerrainDefinedData::instance.gateTowerPlacements[gateIndex].rotationIndex2;
            j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 2);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tower2Y + originY + this->buildingY]
                          .addXgetTile
                    + this->buildingX + tower2X + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[52];
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            for (int j = 0; j < 5; j++) {
                XYPair const& offset = DAT_TerrainDefinedData::instance.gateTowerTileOffsets[tower2Rotation][j];
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[offset.y + tower2Y + originY].addXgetTile
                    + offset.x + tower2X + originX;
                if (j <= 0) {
                    this->ConstructionGFXLayer[tile] = GMFirstPictureIndex::instance[52] + j + 1550;
                } else {
                    int towerRotation
                        = DAT_TerrainDefinedData::instance.constructionSpriteRotationTable[tower2Rotation][j - 1]
                        - this->mapOrientation;
                    if (towerRotation < 0) {
                        towerRotation += 8;
                    }
                    this->ConstructionGFXLayer[tile]
                        = GMFirstPictureIndex::instance[52] + (towerRotation / 2) * 4 + j + 1550;
                }
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
            for (int j = 0; j != 6; j++) {
                int const tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_TerrainDefinedData::instance.gateHouseTiles[gateIndex][j].y + originY]
                          .addXgetTile
                    + originX + DAT_TerrainDefinedData::instance.gateHouseTiles[gateIndex][j].x;
                this->ConstructionGFXLayer[tile]
                    = (this->RandomLayer[tile] & 3) + GMFirstPictureIndex::instance[6] + 312;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_WHEATFARM) {
            for (int j = 0; j != 36; j++) {
                int const tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix
                              [DAT_TerrainDefinedData::instance
                                      .WheatFarmTiles[DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .unkWheatFarmOrientation][j]
                                      .y
                                  + originY]
                          .addXgetTile
                    + DAT_TerrainDefinedData::instance
                          .WheatFarmTiles[DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .unkWheatFarmOrientation][j]
                          .x
                    + originX;
                this->ConstructionGFXLayer[tile] = (this->RandomLayer[tile] & 3) + GMFirstPictureIndex::instance[14];
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_HOPSFARM) {
            for (int j = 0; j != 24; j++) {
                int const tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix
                              [DAT_TerrainDefinedData::instance
                                      .HopFarmProperty1[*(int*)&DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .unkHopFarmVariation][j]
                                      .y
                                  + originY]
                          .addXgetTile
                    + DAT_TerrainDefinedData::instance
                          .HopFarmProperty1[*(int*)&DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .unkHopFarmVariation][j]
                          .x
                    + originX;
                this->ConstructionGFXLayer[tile]
                    = (this->RandomLayer[tile] & 1) * 9 + 37 + GMFirstPictureIndex::instance[14];
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_CATTLEFARM) {
            for (int j = 0; j != 23; j++) {
                int const tile
                    = DAT_ViewportRenderState::instance
                          .translationMatrix
                              [DAT_TerrainDefinedData::instance
                                      .field_0xf5c[DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .dairyFarmVariationMod4][j + 4]
                                      .offset.y
                                  + originY]
                          .addXgetTile
                    + DAT_TerrainDefinedData::instance
                          .field_0xf5c[DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .dairyFarmVariationMod4][j + 4]
                          .offset.x
                    + originX;
                this->ConstructionGFXLayer[tile]
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getRubbleGraphicStageForDamageLevel, this)(
                          DAT_TerrainDefinedData::instance
                              .field_0xf5c[DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .dairyFarmVariationMod4][j + 4]
                              .property)
                    + 55 + GMFirstPictureIndex::instance[14];
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
            for (int j = 0; j != 8; j++) {
                XYPair const& offset = DAT_TerrainDefinedData::instance.AppleFarmOffsets[j];
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[offset.y + originY].addXgetTile
                    + offset.x + originX;
                this->ConstructionGFXLayer[tile] = GMFirstPictureIndex::instance[14] + 61;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO
            || command == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB) {
            x = originX + 5;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + originY].addXgetTile
                    + this->buildingX + x;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 72;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            y = originY + 5;
            j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + this->buildingX + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 122;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + this->buildingX + x;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 97;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD) {
            y = originY + 5;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + this->buildingX + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 147;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
            y = originY + 5;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + this->buildingX + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 172;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
            y = originY + 4;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 4);
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                    + this->buildingX + originX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 296;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_KEEP1) {
            if (this->mapOrientation == 2) {
                keepSpriteVariant = 1;
            }
            int const tile1 = DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[0][0].y + originY]
                                  .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][0].x + originX;
            this->ConstructionGFXLayer[tile1] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1315;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile1] |= 0x8000;
            }
            int const tile2 = DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[0][1].y + originY]
                                  .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][1].x + originX;
            this->ConstructionGFXLayer[tile2] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1326;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile2] |= 0x8000;
            }
            int const tile3 = DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[0][2].y + originY]
                                  .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[0][2].x + originX;
            this->ConstructionGFXLayer[tile3] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1319;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile3] |= 0x8000;
            }
            int const outbuildingX
                = originX + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][0].xOffset;
            int const outbuildingY
                = originY + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[0][0].yOffset;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 7);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + outbuildingY].addXgetTile
                    + this->buildingX + outbuildingX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 23;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            int const outbuilding2X
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][0].xOffset + originX;
            int const outbuilding2Y
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[0][0].yOffset + originY;
            j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + outbuilding2Y].addXgetTile
                    + this->buildingX + outbuilding2X;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[7] + 25;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        } else if (command == OpenSHC::Commands::M_MAPPER_KEEP2 || command == OpenSHC::Commands::M_MAPPER_KEEP3) {
            if (this->mapOrientation == 2) {
                keepSpriteVariant = 1;
            }
            int const keepIndex = buildingCommand - OpenSHC::Commands::M_MAPPER_KEEP1;
            int const tile1
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[keepIndex][0].y + originY]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[keepIndex][0].x + originX;
            this->ConstructionGFXLayer[tile1] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1313;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile1] |= 0x8000;
            }
            int const tile2
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[keepIndex][1].y + originY]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[keepIndex][1].x + originX;
            this->ConstructionGFXLayer[tile2] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1321;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile2] |= 0x8000;
            }
            int const tile3
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.field_0x264[keepIndex][2].y + originY]
                      .addXgetTile
                + DAT_TerrainDefinedData::instance.field_0x264[keepIndex][2].x + originX;
            this->ConstructionGFXLayer[tile3] = GMFirstPictureIndex::instance[52] + keepSpriteVariant + 1317;
            if (skipPlacementFailChecks != 0) {
                this->MiscDisplayLayer[tile3] |= 0x8000;
            }
            int const outbuildingX
                = originX + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].xOffset;
            int const outbuildingY
                = originY + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].yOffset;
            int j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 7);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + outbuildingY].addXgetTile
                    + this->buildingX + outbuildingX;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[6] + 23;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
            int const outbuilding2X
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].xOffset + originX;
            int const outbuilding2Y
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].yOffset + originY;
            j = 0;
            while (true) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + outbuilding2Y].addXgetTile
                    + this->buildingX + outbuilding2X;
                this->ConstructionGFXLayer[tile]
                    = (short)this->buildingRotationRelatedValue + (short)GMFirstPictureIndex::instance[7] + 25;
                if (skipPlacementFailChecks != 0) {
                    this->MiscDisplayLayer[tile] |= 0x8000;
                }
                j++;
                if (j >= this->constructionTileCount) {
                    break;
                }
            }
        }
    }

}
}
