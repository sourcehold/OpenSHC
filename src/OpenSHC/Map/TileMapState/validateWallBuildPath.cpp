
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x005029D0
    void TileMapState::validateWallBuildPath(
        int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command)
    {
        int budget = 0;
        int overshoot = 2;
        int enemyRange;
        int searchRange;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            enemyRange = 0xf;
            searchRange = 7;
        } else {
            enemyRange = 0x1e;
            searchRange = 0x1e;
        }
        this->buildingPlacementFail = FALSE;
        this->illegalBuild = TRUE;
        this->field118_0x554920 = 0;
        if (x1 > 399 || y1 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        if (x2 > 399 || y2 > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == 0) {
            this->buildingPlacementFail = TRUE;
            return;
        }

        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        int tile = *translation + x1;
        this->DAT_SomeY = y1;
        this->DAT_SomeTile = tile;
        if ((short)command == 0x1b) {
            /* a stair needs an enclosed wall to lean against, and enough height on it */
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWallsOrGates, this)(tile, y1) == FALSE) {
                return;
            }
            this->field119_0x554924 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getMaxWallHeightInBrushArea, this)(tile, y1);
            if (this->field119_0x554924 < 0x11) {
                return;
            }
            budget = this->field119_0x554924;
        } else if ((short)command == 0x1a
            && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWalls, this)(tile, y1) == 0) {
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x13;
            return;
        }

        int upY = y1 - y2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        this->field118_0x554920 = 1;
        uint y = y1;
        uint x = x1;
        int leftX = x1 - x2;
        do {
            tile = *translation + x;
            uint logic = this->LogicLayer[tile];
            if ((logic & (L_PLAIN1_AND_FARM | L_BORDER)) != 0) {
                return;
            }
            if ((logic & (L_SEA | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT)) != 0) {
                return;
            }
            if (this->BuildingLayer[tile] != 0) {
                return;
            }
            if ((logic & (L_TREE | L_TREE_VARIATION)) != 0 && this->OrganismLayer[tile] != 0
                && this->OrganismLayer[tile] < 2000) {
                /* scrub can be built through, a real tree cannot */
                switch (DAT_LandscapeState::instance.trees[this->OrganismLayer[tile]].treeType) {
                case (TreeType)5:
                case (TreeType)6:
                case (TreeType)7:
                case (TreeType)8:
                case (TreeType)9:
                case (TreeType)0xa:
                case (TreeType)0xb:
                case (TreeType)0xc:
                case (TreeType)0xd:
                case (TreeType)0xe:
                case (TreeType)0x10:
                case (TreeType)0x11:
                case (TreeType)0x12:
                case (TreeType)0x13:
                    break;
                default:
                    return;
                }
            }
            if ((logic & (L_RIVER | L_FORD)) != 0) {
                return;
            }
            if ((char)logic < 0) {
                return;
            }
            if (this->UnitLayer[tile] != 0 && (logic & L_WALL_OR_GATEHOUSE) == 0
                && DAT_UnitsState::instance.units[(short)this->UnitLayer[tile]].unitType != OpenSHC::Map::Units::UT_CHICKEN) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(
                       playerID, x, y, enemyRange)
                    != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x11;
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange, DAT_PathFindingState::ptr)(
                        playerID, x, y, searchRange, -1, -1, -1)
                    != 0) {
                    if (this->buildingPlacementFailReason == (BuildingFailReasonEnum)0x12) {
                        return;
                    }
                    this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x13;
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int buildRange = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange, DAT_PathFindingState::ptr)(
                            playerID, x, y, buildRange)
                        != 0) {
                        if (this->buildingPlacementFailReason == (BuildingFailReasonEnum)0x12) {
                            return;
                        }
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x13;
                        return;
                    }
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange, DAT_PathFindingState::ptr)(
                       playerID, x, y, 7, -1, -1, -1)
                    != 0) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x11;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk, DAT_PathFindingState::ptr)(
                    playerID, x, y, 2)
                != 0) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x11;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance, DAT_PathFindingState::ptr)(
                    x, y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x15;
                return;
            }
            if ((short)command == 0x1a) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWalls, this)(tile, y) == 0) {
                    this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x13;
                    return;
                }
            } else if ((short)command == 0x1b
                && (budget < 0x11 || (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0)) {
                break;
            }

            int stepX = leftX;
            if ((int)x < (int)x2) {
                stepX = rightX;
            }
            int stepY = upY;
            if ((int)y < (int)y2) {
                stepY = downY;
            }
            if ((short)command == 0x1b) {
                if (stepY < stepX) {
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y < (int)y2) {
                        translation = translation + 3;
                        upY = upY + 1;
                        y = y + 1;
                        downY = downY - 1;
                    } else {
                        translation = translation - 3;
                        upY = upY - 1;
                        y = y - 1;
                        downY = downY + 1;
                    }
                } else {
                    overshoot = overshoot - 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y < (int)y2) {
                        translation = translation + 3;
                        upY = upY + 1;
                        y = y + 1;
                        downY = downY - 1;
                    } else {
                        translation = translation - 3;
                        upY = upY - 1;
                        y = y - 1;
                        downY = downY + 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot = overshoot - 1;
                }
            }
            if (budget > 0x10) {
                budget = budget - 0x10;
            }
        } while (x != x2 || y != y2 || overshoot != 0);
        this->illegalBuild = FALSE;
    }

}
}
