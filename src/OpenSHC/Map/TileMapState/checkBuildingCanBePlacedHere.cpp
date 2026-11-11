#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_OIL;
    using OpenSHC::Map::LogicHelpers::L_RIVER;

    // FUNCTION: STRONGHOLDCRUSADER 0x005037B0
    void TileMapState::checkBuildingCanBePlacedHere(
        int playerID, uint x, uint y, MappersEnum commandBuildingType, int buildingSize)
    {
        uint const startX = x;
        uint const startY = y;
        int keepRangeBonus = 0;
        BOOLEnum sizeDefaulted = FALSE;
        if (buildingSize < 0) {
            buildingSize = 2;
            sizeDefaulted = TRUE;
        }
        this->buildingPlacementFail = FALSE;
        this->placementWarning = 0;
        this->field_0x554944 = 0;
        this->uiBuildingRotation = 15;
        MappersEnum const command = (MappersEnum)(short)commandBuildingType;
        this->buildingSpriteSheetID_1
            = DAT_BuildingDefinedData::instance
                  .Building_SpriteSheet_ID_Array_1[MACRO_CALL_MEMBER(
                      OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                      DAT_BuildingsState::ptr)(command)]
                  .intValue;
        this->buildingSpriteID1 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, DAT_BuildingsState::ptr)(command);
        this->buildingSpriteID2 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID2, DAT_BuildingsState::ptr)(command);
        this->buildingHeightLimit = DAT_BuildingDefinedData::instance.BuildingPlacement_HeightLimit[MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)(command)];
        this->buildingMaxHeightDifference
            = DAT_BuildingDefinedData::instance.BuildingPlacement_MaxHeightDifference[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        this->buildingPlacementProperty_3
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_3[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        this->buildingPlacementProperty_4
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_4[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
            || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
            || DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
            this->buildingPlacementProperty_4 = 0;
        }
        this->buildingPlacementProperty_5
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_5[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        this->buildingPlacementProperty_6
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_6[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        this->buildingPlacementProperty_7
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_7[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(command)];
        if ((short)commandBuildingType == OpenSHC::Commands::M_MAPPER_SIEGE_TOWER_BASE) {
            return;
        }
        int boulderCount = 0;
        int ironCount = 0;
        int oilCount = 0;
        int fertileCount = 0;
        int grassCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::storeMinAndMaxHeightOfArea, this)(x, y, buildingSize);
        if (!sizeDefaulted) {
            BOOLEnum checkSuitability = TRUE;
            switch ((short)commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_WOODSMAN:
            case OpenSHC::Commands::M_MAPPER_OXENBASE:
            case OpenSHC::Commands::M_MAPPER_QUARRY:
            case OpenSHC::Commands::M_MAPPER_TUNNEL:
            case OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
            case OpenSHC::Commands::M_MAPPER_WHEATFARM:
            case OpenSHC::Commands::M_MAPPER_HOPSFARM:
            case OpenSHC::Commands::M_MAPPER_APPLEFARM:
            case OpenSHC::Commands::M_MAPPER_CATTLEFARM:
            case OpenSHC::Commands::M_MAPPER_IRON_MINE:
            case OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS:
            case OpenSHC::Commands::M_MAPPER_QUARRYPILE:
            case OpenSHC::Commands::M_MAPPER_POND1:
            case OpenSHC::Commands::M_MAPPER_POND2_SMALL:
            case OpenSHC::Commands::M_MAPPER_POND3_LARGE1:
            case OpenSHC::Commands::M_MAPPER_POND4_LARGE2:
                // resource buildings and ponds skip the enemy and suitability checks
                checkSuitability = FALSE;
                break;
            case OpenSHC::Commands::M_MAPPER_STORES:
            case OpenSHC::Commands::M_MAPPER_GRANARY:
            case OpenSHC::Commands::M_MAPPER_ARMOURY:
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 3)) {
                            this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i++;
                    } while (i < this->constructionTileCount);
                }
                break;
            case OpenSHC::Commands::M_MAPPER_DOG_CAGE:
                if (DAT_GameState::instance.playerDataArray[playerID].dogCageCount >= 10) {
                    this->buildingPlacementFail = TRUE;
                    this->buildingPlacementFailReason = (BuildingFailReasonEnum)1000;
                    return;
                }
                // fall through
            case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
            case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
            case OpenSHC::Commands::M_MAPPER_DRAWBRIDGE:
                keepRangeBonus = 5;
                // fall through
            case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
            case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
            case OpenSHC::Commands::M_MAPPER_GATE_INNER:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
            case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
            case OpenSHC::Commands::M_MAPPER_MOAT:
            case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
            case OpenSHC::Commands::M_MAPPER_TOWER1:
            case OpenSHC::Commands::M_MAPPER_TOWER2:
            case OpenSHC::Commands::M_MAPPER_TOWER3:
            case OpenSHC::Commands::M_MAPPER_TOWER4:
            case OpenSHC::Commands::M_MAPPER_TOWER5:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        break;
                    }
                    int distance;
                    int range;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(playerID);
                        distance = 15;
                        range = 7;
                    } else {
                        distance = 30;
                        range = 30;
                    }
                    BOOLEnum siteClear;
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + x, this->buildingY + y, distance)) {
                            this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                            siteClear = FALSE;
                            break;
                        }
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                    DAT_PathFindingState::ptr)(
                                    playerID, this->buildingX + x, this->buildingY + y, range, -1, -1, -1)) {
                                this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                                siteClear = FALSE;
                                break;
                            }
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                                    DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y,
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)()
                                        + keepRangeBonus)) {
                                this->buildingPlacementFailReason = (BuildingFailReasonEnum)18;
                                siteClear = FALSE;
                                break;
                            }
                        }
                        siteClear = TRUE;
                        i++;
                    } while (i < this->constructionTileCount);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(
                            x, y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)) {
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)21;
                    } else if (siteClear) {
                        break;
                    }
                    this->buildingPlacementFail = TRUE;
                    if (this->buildingPlacementFailReason
                        == OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)18;
                    }
                } else {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + x, this->buildingY + y, 7, -1, -1, -1)) {
                            this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i++;
                    } while (i < this->constructionTileCount);
                }
                break;
            case OpenSHC::Commands::M_MAPPER_CATAPULT:
            case OpenSHC::Commands::M_MAPPER_TREBUCHET:
            case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
            case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
            case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
            case OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 3)) {
                            this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i++;
                    } while (i < this->constructionTileCount);
                }
                break;
            default:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    int const distance
                        = DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY ? 15 : 30;
                    BOOLEnum noEnemyNearby = TRUE;
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + x, this->buildingY + y, distance)) {
                            this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                            noEnemyNearby = FALSE;
                            break;
                        }
                        i++;
                    } while (i < this->constructionTileCount);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(
                            x, y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)) {
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)21;
                        this->buildingPlacementFail = TRUE;
                    } else if (!noEnemyNearby) {
                        this->buildingPlacementFail = TRUE;
                    }
                }
                break;
            }
            if (checkSuitability && this->buildingPlacementFail == FALSE) {
                int i = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        i, buildingSize);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                            DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 2)) {
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                        this->buildingPlacementFail = TRUE;
                        break;
                    }
                    i++;
                } while (i < this->constructionTileCount);
            }
        }
        if ((short)commandBuildingType == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE && this->buildingMaxHeight > 12) {
            this->buildingPlacementFail = TRUE;
        }
        int tileIndex = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                tileIndex, buildingSize);
            uint const tileX = this->buildingX + x;
            uint const tileY = this->buildingY + y;
            if (tileX > 399 || tileY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                this->buildingPlacementFail = 2;
                return;
            }
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
            uint const logic = this->LogicLayer[tile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->buildingPlacementFail = 2;
                return;
            }
            if ((logic & L_BOULDERS) != 0) {
                boulderCount++;
            }
            if ((logic & L_IRON) != 0) {
                ironCount++;
            }
            if ((logic & L_OIL) != 0) {
                oilCount++;
            }
            if ((logic & L_RIVER) == 0) {
                char const logic2 = this->Logic2Layer[tile];
                if ((logic2 & L2_OASIS_GRASS) != 0) {
                    fertileCount++;
                    grassCount++;
                }
                if ((logic2 & L2_THICK_SCRUB) != 0) {
                    fertileCount++;
                    grassCount++;
                }
                if ((logic2 & L2_SCRUB) != 0) {
                    fertileCount++;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                    tile, playerID, command, 0)) {
                this->buildingPlacementFail = TRUE;
            }
            tileIndex++;
        } while (tileIndex < this->constructionTileCount);
        short const commandShort = (short)commandBuildingType;
        if (commandShort == OpenSHC::Commands::M_MAPPER_CATTLEFARM
            || commandShort == OpenSHC::Commands::M_MAPPER_WHEATFARM
            || commandShort == OpenSHC::Commands::M_MAPPER_HOPSFARM
            || commandShort == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
            if (fertileCount < this->constructionTileCount) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)22;
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (grassCount < 50) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)23;
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_QUARRY) {
            if (boulderCount < 8) {
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_KEEP1 || commandShort == OpenSHC::Commands::M_MAPPER_KEEP2
            || commandShort == OpenSHC::Commands::M_MAPPER_KEEP3) {
            int const keepIndex = command - OpenSHC::Commands::M_MAPPER_KEEP1;
            for (int part = 0; part < 3; part++) {
                uint const partY = DAT_TerrainDefinedData::instance.field_0x264[keepIndex][part].y + y;
                if (!MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                        DAT_TerrainDefinedData::instance.field_0x264[keepIndex][part].x + x, partY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[partY].addXgetTile
                    + DAT_TerrainDefinedData::instance.field_0x264[keepIndex][part].x + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
            }
            x += DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].xOffset;
            y += DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].yOffset;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 7);
                uint const tileY = this->buildingY + y;
                uint const tileX = this->buildingX + x;
                if (tileX > 399 || tileY > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                i++;
            } while (i < this->constructionTileCount);
            int const outbuilding2X
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].xOffset + startX;
            int const outbuilding2Y
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].yOffset + startY;
            int j = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                uint const tileY = this->buildingY + outbuilding2Y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(outbuilding2X + this->buildingX, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + outbuilding2X;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                j++;
            } while (j < this->constructionTileCount);
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A
            || commandShort == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
            || commandShort == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C
            || commandShort == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D) {
            int const gateIndex = command - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A;
            x += DAT_TerrainDefinedData::instance.gateTowerChecks[gateIndex].x1;
            y += DAT_TerrainDefinedData::instance.gateTowerChecks[gateIndex].y1;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 3);
                uint const tileY = this->buildingY + y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                i++;
            } while (i < this->constructionTileCount);
            int const tower2X = DAT_TerrainDefinedData::instance.gateTowerChecks[gateIndex].x2 + startX;
            int const tower2Y = DAT_TerrainDefinedData::instance.gateTowerChecks[gateIndex].y2 + startY;
            int j = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 3);
                uint const tileY = this->buildingY + tower2Y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(tower2X + this->buildingX, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + tower2X;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                j++;
            } while (j < this->constructionTileCount);
            for (int part = 0; part < 6; part++) {
                uint const partY = DAT_TerrainDefinedData::instance
                                       .gateHouseTiles[command - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                                       .y
                    + startY;
                if (!MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(startX
                            + DAT_TerrainDefinedData::instance
                                .gateHouseTiles[command - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                                .x,
                        partY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[partY].addXgetTile
                    + DAT_TerrainDefinedData::instance
                          .gateHouseTiles[command - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                          .x
                    + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
            }
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_IRON_MINE) {
            if (ironCount < 4) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_IRON_ORE;
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS) {
            if (oilCount < 1) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_OIL_MARSH;
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_STORES) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                    .id
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_STOCKPILE)
                >= 32) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, x, y, buildingSize, OpenSHC::Map::Buildings::BT_STOCKPILE)) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_STOCKPILE;
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_GRANARY) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                    .id
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_GRANARY)
                >= 8) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, x, y, buildingSize, OpenSHC::Map::Buildings::BT_GRANARY)) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_GRANARY;
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_ARMOURY) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                    .id
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_ARMORY)
                >= 8) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, x, y, buildingSize, OpenSHC::Map::Buildings::BT_ARMORY)) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_ARMORY;
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO
            || commandShort == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB) {
            x += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].x;
            y += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].y;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                uint const tileY = this->buildingY + y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                i++;
            } while (i < this->constructionTileCount);
            int const part1X
                = startX + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x;
            int const part1Y
                = startY + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y;
            int j = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(j, 5);
                uint const tileY = this->buildingY + part1Y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + part1X, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + part1X;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                j++;
            } while (j < this->constructionTileCount);
            int const part2X
                = startX + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].x;
            int const part2Y
                = startY + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].y;
            int k = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(k, 5);
                uint const tileY = this->buildingY + part2Y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + part2X, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + part2X;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                k++;
            } while (k < this->constructionTileCount);
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD
            || commandShort == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
            x += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x;
            y += DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                uint const tileY = this->buildingY + y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, command, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                i++;
            } while (i < this->constructionTileCount);
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
            x += DAT_TerrainDefinedData::instance.field_0x19c[this->DAT_TempBuildingRotation].x;
            y += DAT_TerrainDefinedData::instance.field_0x19c[this->DAT_TempBuildingRotation].y;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 4);
                uint const tileY = this->buildingY + y;
                if (!MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, OpenSHC::Commands::M_MAPPER_OIL_SMELTER, 0)) {
                    this->buildingPlacementFail = TRUE;
                }
                i++;
            } while (i < this->constructionTileCount);
            return;
        }
        if (commandShort == OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::algTunnelerFindTarget,
                DAT_PathFindingState::ptr)(playerID, 0, 76, x, y);
            if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                this->buildingPlacementFail = TRUE;
            }
        }
    }

}
}
