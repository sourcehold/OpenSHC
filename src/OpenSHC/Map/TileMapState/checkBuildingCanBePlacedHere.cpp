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

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005037B0
    void TileMapState::checkBuildingCanBePlacedHere(
        int playerID, uint x, uint y__fertileLandCount, MappersEnum commandBuildingType, int buildingSize)
    {
        BuildingType _buildingType;
        MappersEnum _commandBuildingType;
        int noEnemyNearby;
        int siteClear;
        int _grassCount;
        int _distance;
        int _range;
        int _boulderCount;
        int _ironCount;
        int _oilCount;
        int keepRangeBonus;
        uint _x;
        uint _y;
        /* the parameter carries the y position in, then is reused as a tile counter */
        _y = y__fertileLandCount;
        _x = x;
        keepRangeBonus = 0;
        int sizeDefaulted = 0;
        if (buildingSize < 0) {
            buildingSize = 2;
            sizeDefaulted = 1;
        }
        _commandBuildingType = (MappersEnum)(short)(undefined2)commandBuildingType;
        this->buildingPlacementFail = FALSE;
        this->placementWarning = 0;
        this->field_0x554944 = 0;
        this->uiBuildingRotation = 0xf;
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingSpriteSheetID_1
            = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[_buildingType].intValue;
        this->buildingSpriteID1 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingSpriteID2 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID2, DAT_BuildingsState::ptr)(_commandBuildingType);
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingHeightLimit = DAT_BuildingDefinedData::instance.BuildingPlacement_HeightLimit[_buildingType];
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingMaxHeightDifference
            = DAT_BuildingDefinedData::instance.BuildingPlacement_MaxHeightDifference[_buildingType];
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingPlacementProperty_3
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_3[_buildingType];
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingPlacementProperty_4
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_4[_buildingType];
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
            || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
            || DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
            this->buildingPlacementProperty_4 = 0;
        }
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingPlacementProperty_5
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_5[_buildingType];
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingPlacementProperty_6
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_6[_buildingType];
        _buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(_commandBuildingType);
        this->buildingPlacementProperty_7
            = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_7[_buildingType];
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_SIEGE_TOWER_BASE) {
            return;
        }
        _boulderCount = 0;
        _ironCount = 0;
        _oilCount = 0;
        y__fertileLandCount = 0;
        _grassCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::storeMinAndMaxHeightOfArea, this)(x, _y, buildingSize);
        if (sizeDefaulted == 0) {
            switch (_commandBuildingType) {
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
                goto tileChecks;
            case OpenSHC::Commands::M_MAPPER_STORES:
            case OpenSHC::Commands::M_MAPPER_GRANARY:
            case OpenSHC::Commands::M_MAPPER_ARMOURY:
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + _y, 3)
                            != FALSE) {
                            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i += 1;
                    } while (i < this->constructionTileCount);
                }
                break;
            case OpenSHC::Commands::M_MAPPER_DOG_CAGE:
                if (DAT_GameState::instance.playerDataArray[playerID].dogCageCount >= 10) {
                    this->buildingPlacementFail = TRUE;
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)1000);
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
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    int i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                DAT_PathFindingState::ptr)(
                                playerID, (int)(this->buildingX + x), (int)(this->buildingY + _y), 7, -1, -1, -1)
                            != 0) {
                            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i += 1;
                    } while (i < this->constructionTileCount);
                } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(playerID);
                        _distance = 15;
                        _range = 7;
                    } else {
                        _distance = 30;
                        _range = 30;
                    }
                    x = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            x, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + _x, this->buildingY + _y, _distance)
                            != FALSE) {
                            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                            siteClear = false;
                            break;
                        }
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                    DAT_PathFindingState::ptr)(playerID, (int)(this->buildingX + _x),
                                    (int)(this->buildingY + _y), _range, -1, -1, -1)
                                != 0) {
                                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                                siteClear = false;
                                break;
                            }
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                                    DAT_PathFindingState::ptr)(playerID, this->buildingX + _x, this->buildingY + _y,
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)()
                                        + keepRangeBonus)
                                != 0) {
                                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                                siteClear = false;
                                break;
                            }
                        }
                        x += 1;
                        siteClear = true;
                    } while ((int)x < this->constructionTileCount);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(
                            _x, _y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                        != FALSE) {
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x15);
                    } else if (siteClear) {
                        break;
                    }
                    this->buildingPlacementFail = TRUE;
                    if (this->buildingPlacementFailReason
                        == OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                    }
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
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + _y, 3)
                            != FALSE) {
                            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                            this->buildingPlacementFail = TRUE;
                            break;
                        }
                        i += 1;
                    } while (i < this->constructionTileCount);
                }
                break;
            default:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    int const distance
                        = DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY ? 15 : 30;
                    noEnemyNearby = true;
                    x = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            x, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + _x, this->buildingY + _y, distance)
                            != FALSE) {
                            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                            noEnemyNearby = false;
                            break;
                        }
                        x += 1;
                    } while ((int)x < this->constructionTileCount);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(
                            _x, _y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                        != FALSE) {
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x15);
                        this->buildingPlacementFail = TRUE;
                    } else if (!noEnemyNearby) {
                        this->buildingPlacementFail = TRUE;
                    }
                }
                break;
            }
            if (this->buildingPlacementFail == FALSE) {
                int i = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        i, buildingSize);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                            DAT_PathFindingState::ptr)(playerID, this->buildingX + _x, this->buildingY + _y, 2)
                        != 0) {
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                        this->buildingPlacementFail = TRUE;
                        break;
                    }
                    i += 1;
                } while (i < this->constructionTileCount);
            }
        }
    tileChecks:
        if ((short)commandBuildingType == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE && this->buildingMaxHeight > 0xc) {
            this->buildingPlacementFail = TRUE;
        }
        x = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, buildingSize);
            uint const tileX = this->buildingX + _x;
            uint const tileY = this->buildingY + _y;
            if (tileX > 399 || tileY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                this->buildingPlacementFail = 2;
                return;
            }
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + _x;
            uint const logic = this->LogicLayer[tile];
            if ((logic & 0x30) != 0) {
                this->buildingPlacementFail = 2;
                return;
            }
            if ((logic & 0x20000) != 0) {
                _boulderCount += 1;
            }
            if ((logic & 0x80000) != 0) {
                _ironCount += 1;
            }
            if ((int)logic < 0) {
                _oilCount += 1;
            }
            if ((logic & 0x100000) == 0) {
                char const logic2 = this->Logic2Layer[tile];
                if ((logic2 & 0x10) != 0) {
                    // grass
                    y__fertileLandCount = y__fertileLandCount + 1;
                    _grassCount += 1;
                }
                if (logic2 < 0) {
                    // thick scrub
                    y__fertileLandCount = y__fertileLandCount + 1;
                    _grassCount += 1;
                }
                if ((logic2 & 1) != 0) {
                    // scrub
                    y__fertileLandCount = y__fertileLandCount + 1;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                    tile, playerID, _commandBuildingType, 0)
                != 0) {
                this->buildingPlacementFail = TRUE;
            }
            x += 1;
        } while ((int)x < this->constructionTileCount);
        short const command = (short)commandBuildingType;
        if (command == OpenSHC::Commands::M_MAPPER_CATTLEFARM || command == OpenSHC::Commands::M_MAPPER_WHEATFARM
            || command == OpenSHC::Commands::M_MAPPER_HOPSFARM || command == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
            if ((int)y__fertileLandCount < this->constructionTileCount) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x16);
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (_grassCount < 50) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x17);
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_QUARRY) {
            if (_boulderCount < 8) {
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_KEEP1 || command == OpenSHC::Commands::M_MAPPER_KEEP2
            || command == OpenSHC::Commands::M_MAPPER_KEEP3) {
            int const keepIndex = _commandBuildingType - OpenSHC::Commands::M_MAPPER_KEEP1;
            for (int part = 0; part < 3; part++) {
                XYPair const& offset = DAT_TerrainDefinedData::instance.field_0x264[keepIndex][part];
                uint const partY = offset.y + _y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(offset.x + _x, partY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[partY].addXgetTile + offset.x + _x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
            }
            int const outbuildingX
                = _x + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].xOffset;
            int const outbuildingY
                = _y + DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x384[keepIndex][0].yOffset;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 7);
                uint const tileY = this->buildingY + outbuildingY;
                uint const tileX = this->buildingX + outbuildingX;
                if (tileX > 399 || tileY > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + outbuildingX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            int const outbuilding2X
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].xOffset + _x;
            int const outbuilding2Y
                = DAT_TerrainDefinedData::instance.keepOutbuildingOffsets_0x3e4[keepIndex][0].yOffset + _y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                uint const tileY = this->buildingY + outbuilding2Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(outbuilding2X + this->buildingX, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + outbuilding2X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C
            || command == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D) {
            // TerrainDefinedData + 0x56C: the two tower origins of each gate command, 24 bytes apart
            int const* const gateTowers = (int const*)((char const*)&DAT_TerrainDefinedData::instance + 0x56c
                + (_commandBuildingType - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A) * 0x18);
            int const tower1X = _x + gateTowers[0];
            int const tower1Y = _y + gateTowers[1];
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 3);
                uint const tileY = this->buildingY + tower1Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + tower1X, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + tower1X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            int const tower2X = gateTowers[3] + _x;
            int const tower2Y = gateTowers[4] + _y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 3);
                uint const tileY = this->buildingY + tower2Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(tower2X + this->buildingX, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + this->buildingX + tower2X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            for (int part = 0; part < 6; part++) {
                uint const partY
                    = DAT_TerrainDefinedData::instance
                          .gateHouseTiles[_commandBuildingType - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                          .y
                    + _y;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(_x
                            + DAT_TerrainDefinedData::instance
                                .gateHouseTiles[_commandBuildingType - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                                .x,
                        partY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[partY].addXgetTile
                    + DAT_TerrainDefinedData::instance
                          .gateHouseTiles[_commandBuildingType - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A][part]
                          .x
                    + _x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
            }
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_IRON_MINE) {
            if (_ironCount < 4) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_IRON_ORE;
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS) {
            if (_oilCount < 1) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_OIL_MARSH;
                this->buildingPlacementFail = TRUE;
            }
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_STORES) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                    .id
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_STOCKPILE)
                >= 0x20) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour, DAT_BuildingsState::ptr)(
                    playerID, (int)(_x), (int)(_y), buildingSize, OpenSHC::Map::Buildings::BT_STOCKPILE)
                != FALSE) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_STOCKPILE;
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_GRANARY) {
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
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour, DAT_BuildingsState::ptr)(
                    playerID, (int)(_x), (int)(_y), buildingSize, OpenSHC::Map::Buildings::BT_GRANARY)
                != FALSE) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_GRANARY;
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_ARMOURY) {
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
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour, DAT_BuildingsState::ptr)(
                    playerID, (int)(_x), (int)(_y), buildingSize, OpenSHC::Map::Buildings::BT_ARMORY)
                != FALSE) {
                return;
            }
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_ARMORY;
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO
            || command == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB) {
            int const part0X
                = _x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].x;
            int const part0Y
                = _y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                uint const tileY = this->buildingY + part0Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + part0X, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + part0X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            int const part1X
                = _x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x;
            int const part1Y
                = _y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                uint const tileY = this->buildingY + part1Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + part1X, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + part1X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            int const part2X
                = _x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].x;
            int const part2Y
                = _y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                uint const tileY = this->buildingY + part2Y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + part2X, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + part2X;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD
            || command == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
            int const partX
                = _x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x;
            int const partY
                = _y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                uint const tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + partX, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, _commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
            int const partX = _x + DAT_TerrainDefinedData::instance.field_0x19c[this->DAT_TempBuildingRotation].x;
            int const partY = _y + DAT_TerrainDefinedData::instance.field_0x19c[this->DAT_TempBuildingRotation].y;
            x = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 4);
                uint const tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + partX, tileY)
                    == FALSE) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementFail = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                        tile, playerID, OpenSHC::Commands::M_MAPPER_OIL_SMELTER, 0)
                    != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                x += 1;
            } while ((int)x < this->constructionTileCount);
            return;
        }
        if (command == OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::algTunnelerFindTarget,
                DAT_PathFindingState::ptr)(playerID, 0, 76, (int)(_x), (int)(_y));
            if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                this->buildingPlacementFail = TRUE;
            }
        }
    }

}
}
