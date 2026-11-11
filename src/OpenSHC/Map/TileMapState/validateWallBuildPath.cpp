#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
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
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x005029D0
    void TileMapState::validateWallBuildPath(int playerID, uint x1, uint y1, uint x2, uint y2, short command)
    {
        int budget = 0;
        int overshoot = 2;
        int enemyRange;
        int searchRange;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            enemyRange = 15;
            searchRange = 7;
        } else {
            enemyRange = 30;
            searchRange = 30;
        }
        this->buildingPlacementFail = FALSE;
        this->illegalBuild = TRUE;
        this->field_0x554920 = 0;
        if (x1 > 399 || y1 > 399) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        if (x2 > 399) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        if (y2 > 399) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == 0) {
            this->buildingPlacementFail = TRUE;
            return;
        }

        uint x = x1;
        uint y = y1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        this->DAT_SomeTile = *translation + x1;
        this->DAT_SomeY = y1;
        if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
            // a stair needs an enclosed wall to lean against, and enough height on it
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWallsOrGates, this)(
                    this->DAT_SomeTile, y1)
                == FALSE) {
                return;
            }
            int const height = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getMaxWallHeightInBrushArea, this)(
                this->DAT_SomeTile, y1);
            this->maxWallHeightInPath = height;
            if (height <= 16) {
                return;
            }
            budget = height;
            overshoot = 2;
        } else if (command == OpenSHC::Commands::M_MAPPER_CRENAL
            && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWalls, this)(this->DAT_SomeTile, y1)
                == FALSE) {
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)19;
            return;
        }

        int upY = y1 - y2;
        int leftX = x1 - x2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        this->field_0x554920 = 1;
        do {
            int const tile = *translation + x;
            uint const logic = this->LogicLayer[tile];
            if ((logic & (L_PLAIN1_AND_FARM | L_BORDER)) != 0) {
                return;
            }
            if ((logic & (L_SEA | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT)) != 0) {
                return;
            }
            if (this->BuildingLayer[tile] != 0) {
                return;
            }
            if ((logic & (L_TREE | L_TREE_VARIATION)) != 0) {
                int const organism = this->OrganismLayer[tile];
                if (organism != 0 && organism < 2000) {
                    // scrub can be built through, a real tree cannot
                    switch (DAT_LandscapeState::instance.trees[organism].treeType) {
                    case OpenSHC::Map::Trees::TT_UNKNOWN_5:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_6:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_7:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_8:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_9:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_10:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_11:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_12:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_13:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_14:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_16:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_17:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_18:
                    case OpenSHC::Map::Trees::TT_UNKNOWN_19:
                        break;
                    default:
                        return;
                    }
                }
            }
            if ((logic & (L_RIVER | L_FORD)) != 0) {
                return;
            }
            if ((logic & L_ROCKY) != 0) {
                return;
            }
            if (this->UnitLayer[tile] != 0 && (logic & L_WALL_OR_GATEHOUSE) == 0
                && DAT_UnitsState::instance.units[(short)this->UnitLayer[tile]].unitType
                    != OpenSHC::Map::Units::UT_CHICKEN) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                       DAT_PathFindingState::ptr)(playerID, x, y, enemyRange)
                    != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                        DAT_PathFindingState::ptr)(playerID, x, y, searchRange, -1, -1, -1)
                    != FALSE) {
                    if (this->buildingPlacementFailReason == (BuildingFailReasonEnum)18) {
                        return;
                    }
                    this->buildingPlacementFailReason = (BuildingFailReasonEnum)19;
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int buildRange
                        = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                            DAT_PathFindingState::ptr)(playerID, x, y, buildRange)
                        != FALSE) {
                        if (this->buildingPlacementFailReason == (BuildingFailReasonEnum)18) {
                            return;
                        }
                        this->buildingPlacementFailReason = (BuildingFailReasonEnum)19;
                        return;
                    }
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                       DAT_PathFindingState::ptr)(playerID, x, y, 7, -1, -1, -1)
                    != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                    DAT_PathFindingState::ptr)(playerID, x, y, 2)
                != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)17;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                    DAT_PathFindingState::ptr)(x, y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                != FALSE) {
                this->buildingPlacementFailReason = (BuildingFailReasonEnum)21;
                return;
            }
            if (command == OpenSHC::Commands::M_MAPPER_CRENAL) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isTileEnclosedByWalls, this)(tile, y) == FALSE) {
                    this->buildingPlacementFailReason = (BuildingFailReasonEnum)19;
                    return;
                }
            } else if (command == OpenSHC::Commands::M_MAPPER_STAIR
                && (budget <= 16 || (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0)) {
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
            if (command == OpenSHC::Commands::M_MAPPER_STAIR) {
                if (stepX > stepY) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y >= (int)y2) {
                        translation -= 3;
                        upY -= 1;
                        y -= 1;
                        downY += 1;
                    } else {
                        translation += 3;
                        upY += 1;
                        y += 1;
                        downY -= 1;
                    }
                } else {
                    overshoot -= 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y >= (int)y2) {
                        translation -= 3;
                        upY -= 1;
                        y -= 1;
                        downY += 1;
                    } else {
                        translation += 3;
                        upY += 1;
                        y += 1;
                        downY -= 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot -= 1;
                }
            }
            if (budget > 16) {
                budget -= 16;
            }
        } while (x != x2 || y != y2 || overshoot != 0);
        this->illegalBuild = FALSE;
    }

}
}
