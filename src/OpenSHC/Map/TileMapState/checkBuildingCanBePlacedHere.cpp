
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
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

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Unable to use type for symbol _x
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
    // FUNCTION: STRONGHOLDCRUSADER 0x005037B0
    void TileMapState::checkBuildingCanBePlacedHere(
        int playerID, uint x, uint y__fertileLandCount, MappersEnum commandBuildingType, int buildingSize)
    {
        uint uVar1;
        byte bVar2;
        BuildingType _buildingType;
        int _buildRange;
        BOOLEnum BVar3;
        int iVar4;
        uint uVar5;
        int iVar6;
        int iVar7;
        MappersEnum _commandBuildingType;
        int iVar8;
        int* piVar9;
        int bVar10;
        int bVar11;
        int _grassCount;
        int _distance;
        int _range;
        int _boulderCount;
        int _ironCount;
        int _oilCount;
        int local_4;
        uint _x;
        uint _y;
        /* the parameter carries the y position in, then is reused as a tile counter */
        _y = y__fertileLandCount;
        _x = x;
        local_4 = 0;
        int sizeDefaulted = 0;
        if (buildingSize < 0) {
            buildingSize = 2;
            sizeDefaulted = 1;
        }
        _commandBuildingType = (MappersEnum)(short)(undefined2)commandBuildingType;
        this->buildingPlacementFail = FALSE;
        this->placementWarning = 0;
        this->field127_0x554944 = 0;
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
        if (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1))
            || (DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0)) {
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
        if (sizeDefaulted != 0)
            goto switchD_0050397c_caseD_33;
        if (0x138 < (int)_commandBuildingType) {
            if (325 < (int)_commandBuildingType) {
                if ((int)_commandBuildingType < 328)
                    goto switchD_0050397c_caseD_33;
                if (_commandBuildingType == 358)
                    goto switchD_0050397c_caseD_be;
            }
        switchD_0050397c_caseD_35:
            if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                bVar10 = DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY;
                bVar11 = true;
                x = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        x, buildingSize);
                    BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                        DAT_PathFindingState::ptr)(playerID, this->buildingX + _x, this->buildingY + _y,
                        (int)((int)((-(uint)bVar10 & 0xfffffff1) + 0x1e)));
                    if (BVar3 != FALSE) {
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                        bVar11 = false;
                        break;
                    }
                    x = x + 1;
                } while ((int)x < this->constructionTileCount);
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                    DAT_PathFindingState::ptr)(_x, _y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5);
                if (BVar3 == FALSE) {
                    if (bVar11)
                        goto LAB_00503d46;
                } else {
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x15);
                }
            LAB_00503d3c:
                this->buildingPlacementFail = TRUE;
            }
            goto LAB_00503d46;
        }
        if (_commandBuildingType == OpenSHC::Commands::M_MAPPER_DOG_CAGE) {
            if (9 < DAT_GameState::instance.playerDataArray[playerID].dogCageCount) {
                this->buildingPlacementFail = TRUE;
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)1000);
                return;
            }
        switchD_0050397c_caseD_62:
            local_4 = 5;
        switchD_0050397c_caseD_64:
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                iVar8 = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        iVar8, buildingSize);
                    iVar4
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                            DAT_PathFindingState::ptr)(playerID, (int)((int)(this->buildingX + x)),
                            (int)((int)(this->buildingY + _y)), 7, -1, -1, -1);
                    if (iVar4 != 0)
                        goto LAB_005039d6;
                    iVar8 = iVar8 + 1;
                } while (iVar8 < this->constructionTileCount);
            } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    _distance = 30;
                    _range = 30;
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(playerID);
                    _distance = 15;
                    _range = 7;
                }
                x = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        x, buildingSize);
                    BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                        DAT_PathFindingState::ptr)(playerID, this->buildingX + _x, this->buildingY + _y, _distance);
                    if (BVar3 != FALSE) {
                    LAB_00503b32:
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                    LAB_00503b48:
                        bVar11 = false;
                        break;
                    }
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        iVar8 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                            DAT_PathFindingState::ptr)(playerID, (int)((int)(this->buildingX + _x)),
                            (int)((int)(this->buildingY + _y)), _range, -1, -1, -1);
                        if (iVar8 != 0)
                            goto LAB_00503b32;
                        _buildRange
                            = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                        iVar8 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                            DAT_PathFindingState::ptr)(
                            playerID, this->buildingX + _x, this->buildingY + _y, _buildRange + local_4);
                        if (iVar8 == 0)
                            goto LAB_00503b11;
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                        goto LAB_00503b48;
                    }
                LAB_00503b11:
                    x = x + 1;
                    bVar11 = true;
                } while ((int)x < this->constructionTileCount);
                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                    DAT_PathFindingState::ptr)(_x, _y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5);
                if (BVar3 == FALSE) {
                    if (bVar11)
                        goto LAB_00503d46;
                } else {
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x15);
                }
                this->buildingPlacementFail = TRUE;
                if (this->buildingPlacementFailReason == OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                }
            }
        } else {
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
                goto switchD_0050397c_caseD_33;
            case OpenSHC::Commands::M_MAPPER_STORES:
            case OpenSHC::Commands::M_MAPPER_GRANARY:
            case OpenSHC::Commands::M_MAPPER_ARMOURY:
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    iVar8 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar8, buildingSize);
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                            DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + _y, 3);
                        if (BVar3 != FALSE)
                            goto LAB_005039d6;
                        iVar8 = iVar8 + 1;
                    } while (iVar8 < this->constructionTileCount);
                }
                break;
            default:
                goto switchD_0050397c_caseD_35;
            case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
            case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
            case OpenSHC::Commands::M_MAPPER_DRAWBRIDGE:
                goto switchD_0050397c_caseD_62;
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
                goto switchD_0050397c_caseD_64;
            case OpenSHC::Commands::M_MAPPER_CATAPULT:
            case OpenSHC::Commands::M_MAPPER_TREBUCHET:
            case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
            case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
            case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
            switchD_0050397c_caseD_be:
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                    iVar8 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            iVar8, buildingSize);
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                            DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + _y, 3);
                        if (BVar3 != FALSE)
                            goto LAB_005039d6;
                        iVar8 = iVar8 + 1;
                    } while (iVar8 < this->constructionTileCount);
                }
            }
        }
    LAB_00503d46:
        if (this->buildingPlacementFail == FALSE) {
            iVar8 = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                    iVar8, buildingSize);
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                    DAT_PathFindingState::ptr)(playerID, this->buildingX + _x, this->buildingY + _y, 2);
                if (iVar4 != 0) {
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
                    this->buildingPlacementFail = TRUE;
                    break;
                }
                iVar8 = iVar8 + 1;
            } while (iVar8 < this->constructionTileCount);
        }
    switchD_0050397c_caseD_33:
        if (((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE) && (0xc < this->buildingMaxHeight)) {
            this->buildingPlacementFail = TRUE;
        }
        x = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, buildingSize);
            uVar5 = this->buildingY + _y;
            if (399 < this->buildingX + _x) {
                this->buildingPlacementFail = 2;
                return;
            }
            if (399 < uVar5) {
                this->buildingPlacementFail = 2;
                return;
            }
            if (*(char*)(uVar5 * 400 + 0x21aec98 + this->buildingX + _x) == '\0') {
                this->buildingPlacementFail = 2;
                return;
            }
            iVar8 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile + this->buildingX + _x;
            uVar5 = this->LogicLayer[iVar8];
            if ((uVar5 & 0x30) != 0) {
                this->buildingPlacementFail = 2;
                return;
            }
            if ((uVar5 & 0x20000) != 0) {
                _boulderCount = _boulderCount + 1;
            }
            if ((uVar5 & 0x80000) != 0) {
                _ironCount = _ironCount + 1;
            }
            if ((int)uVar5 < 0) {
                _oilCount = _oilCount + 1;
            }
            if ((uVar5 & 0x100000) == 0) {
                bVar2 = this->Logic2Layer[iVar8];
                if ((bVar2 & 0x10) != 0) {
                    /*
                      grass
                     */
                    y__fertileLandCount = y__fertileLandCount + 1;
                    _grassCount = _grassCount + 1;
                }
                if ((char)bVar2 < '\0') {
                    /*
                      thick scrub
                     */
                    y__fertileLandCount = y__fertileLandCount + 1;
                    _grassCount = _grassCount + 1;
                }
                if ((bVar2 & 1) != 0) {
                    /*
                      scrub
                     */
                    y__fertileLandCount = y__fertileLandCount + 1;
                }
            }
            iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                iVar8, playerID, _commandBuildingType, 0);
            if (iVar8 != 0) {
                this->buildingPlacementFail = TRUE;
            }
            x = x + 1;
        } while ((int)x < this->constructionTileCount);
        if (((((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_CATTLEFARM)
                 || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_WHEATFARM))
                || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_HOPSFARM))
            || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_APPLEFARM)) {
            if ((int)y__fertileLandCount < this->constructionTileCount) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x16);
                this->buildingPlacementFail = TRUE;
                return;
            }
            if (_grassCount < 50) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x17);
                this->buildingPlacementFail = TRUE;
            }
        } else {
            if ((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_QUARRY) {
                if ((((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP1)
                        || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP2))
                    || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP3)) {
                    buildingSize = (_commandBuildingType - OpenSHC::Commands::M_MAPPER_KEEP1) * 0x60 + 0xb491b8;
                    commandBuildingType = OpenSHC::Commands::M_MAPPER_NULL;
                    do {
                        uVar5 = *(int*)(buildingSize + 4) + _y;
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(*(int*)buildingSize + _x, uVar5);
                        if (BVar3 == FALSE) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar8 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile
                            + *(int*)buildingSize + _x;
                        if ((this->LogicLayer[iVar8] & 0x30) != 0) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar8, playerID, _commandBuildingType, 0);
                        if (iVar8 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        buildingSize = buildingSize + 8;
                        commandBuildingType = (MappersEnum)(commandBuildingType + OpenSHC::Commands::M_MAPPER_AREA);
                    } while ((int)commandBuildingType < 3);
                    iVar4 = (_commandBuildingType - OpenSHC::Commands::M_MAPPER_KEEP1) * 0x20;
                    iVar6 = _x + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 900);
                    iVar8 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 904);
                    x = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 7);
                        uVar5 = this->buildingY + _y + iVar8;
                        uVar1 = this->buildingX + iVar6;
                        if (399 < uVar1) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        if (399 < uVar5) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        if (*(char*)(uVar5 * 400 + 0x21aec98 + uVar1) == '\0') {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile + this->buildingX
                            + iVar6;
                        if ((this->LogicLayer[iVar7] & 0x30) != 0) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar7, playerID, _commandBuildingType, 0);
                        if (iVar7 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        x = x + 1;
                    } while ((int)x < this->constructionTileCount);
                    iVar8 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 1000);
                    iVar4 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 + 0x3e4) + _x;
                    x = 0;
                    while (true) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                        iVar6 = this->buildingX;
                        uVar5 = this->buildingY + iVar8 + _y;
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(iVar4 + this->buildingX, uVar5);
                        if ((BVar3 == FALSE)
                            || (iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile + iVar6
                                    + iVar4,
                                (this->LogicLayer[iVar6] & 0x30) != 0))
                            break;
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar6, playerID, _commandBuildingType, 0);
                        if (iVar6 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        x = x + 1;
                        if (this->constructionTileCount <= (int)x) {
                            return;
                        }
                    }
                } else {
                    if (((((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_GATE_WOOD1A)
                             && ((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_GATE_WOOD1B))
                            && ((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_GATE_WOOD1C))
                        && ((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_GATE_WOOD1D)) {
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_IRON_MINE) {
                            if (3 < _ironCount) {
                                return;
                            }
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_IRON_ORE;
                            this->buildingPlacementFail = TRUE;
                            return;
                        }
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS) {
                            if (0 < _oilCount) {
                                return;
                            }
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_OIL_MARSH;
                            this->buildingPlacementFail = TRUE;
                            return;
                        }
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_STORES) {
                            if (DAT_GameState::instance.playerDataArray[playerID].stockpile.id == 0) {
                                return;
                            }
                            iVar8
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_STOCKPILE);
                            if (iVar8 < 0x20) {
                                BVar3 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                                    DAT_BuildingsState::ptr)(playerID, (int)((int)(_x)), (int)((int)(_y)), buildingSize,
                                    OpenSHC::Map::Buildings::BT_STOCKPILE);
                                if (BVar3 != FALSE) {
                                    return;
                                }
                                this->buildingPlacementFail = TRUE;
                                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_STOCKPILE;
                                return;
                            }
                            this->buildingPlacementFail = TRUE;
                            return;
                        }
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GRANARY) {
                            if (DAT_GameState::instance.playerDataArray[playerID].granary.id == 0) {
                                return;
                            }
                            iVar8
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_GRANARY);
                            if (iVar8 < 8) {
                                BVar3 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                                    DAT_BuildingsState::ptr)(playerID, (int)((int)(_x)), (int)((int)(_y)), buildingSize,
                                    OpenSHC::Map::Buildings::BT_GRANARY);
                                if (BVar3 != FALSE) {
                                    return;
                                }
                                this->buildingPlacementFail = TRUE;
                                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_GRANARY;
                                return;
                            }
                            this->buildingPlacementFail = TRUE;
                            return;
                        }
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_ARMOURY) {
                            if (DAT_GameState::instance.playerDataArray[playerID].armory.id == 0) {
                                return;
                            }
                            iVar8
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_ARMORY);
                            if (iVar8 < 8) {
                                BVar3 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                                    DAT_BuildingsState::ptr)(playerID, (int)((int)(_x)), (int)((int)(_y)), buildingSize,
                                    OpenSHC::Map::Buildings::BT_ARMORY);
                                if (BVar3 != FALSE) {
                                    return;
                                }
                                this->buildingPlacementFail = TRUE;
                                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_ARMORY;
                                return;
                            }
                            this->buildingPlacementFail = TRUE;
                            return;
                        }
                        if (((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO)
                            || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB)) {
                            iVar4 = _x
                                + DAT_TerrainDefinedData::instance
                                      .BuildingPartsOffsets[this->DAT_TempBuildingRotation][0]
                                      .x;
                            iVar8 = DAT_TerrainDefinedData::instance
                                        .BuildingPartsOffsets[this->DAT_TempBuildingRotation][0]
                                        .y;
                            x = 0;
                            while (true) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                                uVar5 = this->buildingY + _y + iVar8;
                                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->buildingX + iVar4, uVar5);
                                if (BVar3 == FALSE) {
                                    this->buildingPlacementFail = 2;
                                    return;
                                }
                                iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile
                                    + this->buildingX + iVar4;
                                if ((this->LogicLayer[iVar6] & 0x30) != 0)
                                    break;
                                iVar6 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                                    iVar6, playerID, _commandBuildingType, 0);
                                if (iVar6 != 0) {
                                    this->buildingPlacementFail = TRUE;
                                }
                                x = x + 1;
                                if (this->constructionTileCount <= (int)x) {
                                    iVar4 = DAT_TerrainDefinedData::instance
                                                .BuildingPartsOffsets[this->DAT_TempBuildingRotation][1]
                                                .x
                                        + _x;
                                    iVar8 = DAT_TerrainDefinedData::instance
                                                .BuildingPartsOffsets[this->DAT_TempBuildingRotation][1]
                                                .y;
                                    x = 0;
                                    while (true) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                            x, 5);
                                        iVar6 = this->buildingX;
                                        uVar5 = this->buildingY + iVar8 + _y;
                                        BVar3 = MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                            DAT_ViewportRenderState::ptr)(this->buildingX + iVar4, uVar5);
                                        if (BVar3 == FALSE) {
                                            this->buildingPlacementFail = 2;
                                            return;
                                        }
                                        iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile
                                            + iVar6 + iVar4;
                                        if ((this->LogicLayer[iVar6] & 0x30) != 0)
                                            break;
                                        iVar6 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                                            iVar6, playerID, _commandBuildingType, 0);
                                        if (iVar6 != 0) {
                                            this->buildingPlacementFail = TRUE;
                                        }
                                        x = x + 1;
                                        if (this->constructionTileCount <= (int)x) {
                                            iVar4 = DAT_TerrainDefinedData::instance
                                                        .BuildingPartsOffsets[this->DAT_TempBuildingRotation][2]
                                                        .x
                                                + _x;
                                            iVar8 = DAT_TerrainDefinedData::instance
                                                        .BuildingPartsOffsets[this->DAT_TempBuildingRotation][2]
                                                        .y;
                                            x = 0;
                                            while (true) {
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                                                    this)(x, 5);
                                                iVar6 = this->buildingX;
                                                uVar5 = this->buildingY + iVar8 + _y;
                                                BVar3 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                                    DAT_ViewportRenderState::ptr)(this->buildingX + iVar4, uVar5);
                                                if (BVar3 == FALSE) {
                                                    this->buildingPlacementFail = 2;
                                                    return;
                                                }
                                                iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5]
                                                            .addXgetTile
                                                    + iVar6 + iVar4;
                                                if ((this->LogicLayer[iVar6] & 0x30) != 0)
                                                    break;
                                                iVar6 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                                                    this)(iVar6, playerID, _commandBuildingType, 0);
                                                if (iVar6 != 0) {
                                                    this->buildingPlacementFail = TRUE;
                                                }
                                                x = x + 1;
                                                if (this->constructionTileCount <= (int)x) {
                                                    return;
                                                }
                                            }
                                            this->buildingPlacementFail = 2;
                                            return;
                                        }
                                    }
                                    this->buildingPlacementFail = 2;
                                    return;
                                }
                            }
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        if (((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD)
                            || ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD)) {
                            iVar4 = _x
                                + DAT_TerrainDefinedData::instance
                                      .BuildingPartsOffsets[this->DAT_TempBuildingRotation][1]
                                      .x;
                            iVar8 = DAT_TerrainDefinedData::instance
                                        .BuildingPartsOffsets[this->DAT_TempBuildingRotation][1]
                                        .y;
                            x = 0;
                            while (true) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 5);
                                uVar5 = this->buildingY + _y + iVar8;
                                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->buildingX + iVar4, uVar5);
                                if (BVar3 == FALSE) {
                                    this->buildingPlacementFail = 2;
                                    return;
                                }
                                iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile
                                    + this->buildingX + iVar4;
                                if ((this->LogicLayer[iVar6] & 0x30) != 0)
                                    break;
                                iVar6 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                                    iVar6, playerID, _commandBuildingType, 0);
                                if (iVar6 != 0) {
                                    this->buildingPlacementFail = TRUE;
                                }
                                x = x + 1;
                                if (this->constructionTileCount <= (int)x) {
                                    return;
                                }
                            }
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
                            iVar4
                                = _x + DAT_TerrainDefinedData::instance.field63_0x19c[this->DAT_TempBuildingRotation].x;
                            iVar8 = DAT_TerrainDefinedData::instance.field63_0x19c[this->DAT_TempBuildingRotation].y;
                            x = 0;
                            while (true) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 4);
                                uVar5 = this->buildingY + _y + iVar8;
                                BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(this->buildingX + iVar4, uVar5);
                                if (BVar3 == FALSE) {
                                    this->buildingPlacementFail = 2;
                                    return;
                                }
                                iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile
                                    + this->buildingX + iVar4;
                                if ((this->LogicLayer[iVar6] & 0x30) != 0)
                                    break;
                                iVar6 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, this)(
                                    iVar6, playerID, OpenSHC::Commands::M_MAPPER_OIL_SMELTER, 0);
                                if (iVar6 != 0) {
                                    this->buildingPlacementFail = TRUE;
                                }
                                x = x + 1;
                                if (this->constructionTileCount <= (int)x) {
                                    return;
                                }
                            }
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        if ((undefined2)commandBuildingType != OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION) {
                            return;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::algTunnelerFindTarget,
                            DAT_PathFindingState::ptr)(
                            playerID, 0, (int)((int)(76)), (int)((int)(_x)), (int)((int)(_y)));
                        if (DAT_PathFindingState::instance.ALG_TargetTile != 0) {
                            return;
                        }
                        this->buildingPlacementFail = TRUE;
                        return;
                    }
                    iVar8 = _commandBuildingType * 3 + -0x1a4;
                    iVar6 = _x + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 * 8 + 0x56c);
                    iVar8 = iVar8 * 8;
                    iVar4 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x570);
                    x = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 3);
                        uVar5 = this->buildingY + _y + iVar4;
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(this->buildingX + iVar6, uVar5);
                        if (BVar3 == FALSE) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile + this->buildingX
                            + iVar6;
                        if ((this->LogicLayer[iVar7] & 0x30) != 0) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar7, playerID, _commandBuildingType, 0);
                        if (iVar7 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        x = x + 1;
                    } while ((int)x < this->constructionTileCount);
                    iVar4 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x57c);
                    iVar8 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x578) + _x;
                    x = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(x, 3);
                        iVar6 = this->buildingX;
                        uVar5 = this->buildingY + iVar4 + _y;
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(iVar8 + this->buildingX, uVar5);
                        if (BVar3 == FALSE) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar6 = DAT_ViewportRenderState::instance.translationMatrix[uVar5].addXgetTile + iVar6 + iVar8;
                        if ((this->LogicLayer[iVar6] & 0x30) != 0) {
                            this->buildingPlacementFail = 2;
                            return;
                        }
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar6, playerID, _commandBuildingType, 0);
                        if (iVar6 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        x = x + 1;
                    } while ((int)x < this->constructionTileCount);
                    commandBuildingType = OpenSHC::Commands::M_MAPPER_NULL;
                    piVar9
                        = (int*)((int)DAT_TerrainDefinedData::ptr + (_commandBuildingType * 3 + -0x1a4) * 0x10 + 0x5cc);
                    while (true) {
                        iVar8 = piVar9[1];
                        iVar4 = *piVar9;
                        BVar3 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                            DAT_ViewportRenderState::ptr)(_x + iVar4, iVar8 + _y);
                        if ((BVar3 == FALSE)
                            || (iVar8 = DAT_ViewportRenderState::instance.translationMatrix[iVar8 + _y].addXgetTile
                                    + iVar4 + _x,
                                (this->LogicLayer[iVar8] & 0x30) != 0))
                            break;
                        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementAllowedAtTile,
                            this)(iVar8, playerID, _commandBuildingType, 0);
                        if (iVar8 != 0) {
                            this->buildingPlacementFail = TRUE;
                        }
                        commandBuildingType = (MappersEnum)(commandBuildingType + OpenSHC::Commands::M_MAPPER_AREA);
                        piVar9 = piVar9 + 2;
                        if (5 < (int)commandBuildingType) {
                            return;
                        }
                    }
                }
                this->buildingPlacementFail = 2;
                return;
            }
            if (_boulderCount < 8) {
                this->buildingPlacementFail = TRUE;
                return;
            }
        }
        return;
    LAB_005039d6:
        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
        goto LAB_00503d3c;
    }

}
}
