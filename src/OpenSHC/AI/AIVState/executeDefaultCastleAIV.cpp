#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // builds a generic castle for AIs without an AIV, the number of each building depends on the AI character
    // FUNCTION: STRONGHOLDCRUSADER 0x004F0060
    BOOLEnum AIVState::executeDefaultCastleAIV(PlayerID playerID, int isPausing)
    {
        int const aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
        int stockpiles = 0;
        int hovels = 0;
        int granaries = 1;
        int marketplaces = 1;
        int armories = 0;
        int barracks = 0;
        int mercenaryPosts = 0;
        int cathedrals = 0;
        int chapels = 0;
        int inns = 0;
        int breweries = 0;
        int bakeries = 0;
        int mills = 0;
        int poleturners = 0;
        int fletchers = 0;
        int tanners = 0;
        int blacksmiths = 0;
        int armourers = 0;
        int engineersGuilds = 0;
        int tunnelersGuilds = 0;
        int stables = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_RAT) {
            stockpiles = 0;
            hovels = 3;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            inns = 0;
            breweries = 0;
            bakeries = 0;
            mills = 0;
            poleturners = 1;
            fletchers = 1;
            tanners = 0;
            blacksmiths = 0;
            engineersGuilds = 0;
            chapels = 0;
            armourers = 0;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_SNAKE) {
            mercenaryPosts = 1;
            tanners = 0;
            blacksmiths = 0;
            poleturners = 2;
            stockpiles = 2;
            inns = 0;
            mills = 0;
            bakeries = 0;
            breweries = 0;
            armories = 1;
            barracks = 1;
            hovels = 4;
            engineersGuilds = 1;
            fletchers = 2;
            chapels = 0;
            armourers = 0;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_PIG) {
            mercenaryPosts = 0;
            poleturners = 0;
            tanners = 2;
            blacksmiths = 2;
            stockpiles = 2;
            inns = 0;
            mills = 0;
            bakeries = 0;
            breweries = 0;
            armories = 1;
            barracks = 1;
            hovels = 4;
            engineersGuilds = 1;
            fletchers = 2;
            chapels = 0;
            armourers = 0;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_WOLF) {
            stockpiles = 3;
            hovels = 5;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 1;
            chapels = 2;
            inns = 2;
            breweries = 3;
            bakeries = 0;
            mills = 0;
            poleturners = 2;
            fletchers = 2;
            tanners = 1;
            blacksmiths = 2;
            armourers = 1;
            engineersGuilds = 1;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_SALADIN) {
            stockpiles = 3;
            hovels = 8;
            inns = 0;
            breweries = 0;
            bakeries = 4;
            mills = 2;
            mercenaryPosts = 1;
            barracks = 0;
            armories = 0;
            poleturners = 0;
            fletchers = 0;
            tanners = 0;
            blacksmiths = 0;
            engineersGuilds = 1;
            chapels = 0;
            armourers = 0;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_CALIPH) {
            stockpiles = 2;
            inns = 2;
            breweries = 5;
            bakeries = 0;
            mills = 0;
            hovels = 6;
            mercenaryPosts = 1;
            barracks = 0;
            armories = 0;
            poleturners = 0;
            fletchers = 0;
            tanners = 0;
            blacksmiths = 0;
            engineersGuilds = 1;
            chapels = 0;
            armourers = 0;
            cathedrals = 0;
            stables = 0;
            tunnelersGuilds = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_SULTAN) {
            stockpiles = 0;
            hovels = 3;
            armories = 0;
            barracks = 0;
            mercenaryPosts = 1;
            cathedrals = 0;
            chapels = 0;
            inns = 0;
            breweries = 0;
            bakeries = 0;
            mills = 0;
            poleturners = 0;
            fletchers = 0;
            tanners = 0;
            blacksmiths = 0;
            armourers = 0;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_RICHARD) {
            stockpiles = 2;
            hovels = 6;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            cathedrals = 0;
            chapels = 2;
            inns = 0;
            breweries = 0;
            bakeries = 0;
            mills = 0;
            poleturners = 2;
            fletchers = 2;
            tanners = 0;
            blacksmiths = 2;
            armourers = 2;
            engineersGuilds = 1;
            tunnelersGuilds = 1;
            stables = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_FREDERICK) {
            hovels = 7;
            stockpiles = 3;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            cathedrals = 1;
            chapels = 0;
            inns = 2;
            breweries = 2;
            bakeries = 0;
            mills = 0;
            poleturners = 0;
            fletchers = 2;
            tanners = 2;
            blacksmiths = 2;
            armourers = 2;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 2;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_PHILIPP) {
            stockpiles = 2;
            hovels = 5;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            cathedrals = 0;
            chapels = 2;
            inns = 0;
            breweries = 0;
            bakeries = 0;
            mills = 0;
            poleturners = 3;
            fletchers = 2;
            tanners = 0;
            blacksmiths = 2;
            armourers = 2;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 5;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_WAZIR) {
            hovels = 6;
            armories = 0;
            barracks = 0;
            inns = 0;
            breweries = 0;
            bakeries = 3;
            fletchers = 0;
            mercenaryPosts = 1;
            stockpiles = 2;
            poleturners = 0;
            chapels = 0;
            cathedrals = 0;
            tanners = 0;
            blacksmiths = 0;
            armourers = 0;
            tunnelersGuilds = 0;
            stables = 0;
            mills = 1;
            engineersGuilds = 1;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_EMIR) {
            hovels = 7;
            armories = 1;
            barracks = 1;
            inns = 1;
            breweries = 2;
            bakeries = 2;
            fletchers = 1;
            mercenaryPosts = 1;
            stockpiles = 3;
            poleturners = 0;
            chapels = 0;
            cathedrals = 0;
            tanners = 0;
            blacksmiths = 0;
            armourers = 0;
            tunnelersGuilds = 0;
            stables = 0;
            mills = 1;
            engineersGuilds = 1;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_NIZAR) {
            hovels = 8;
            armories = 0;
            barracks = 0;
            mercenaryPosts = 1;
            cathedrals = 0;
            chapels = 0;
            inns = 1;
            breweries = 3;
            mills = 1;
            fletchers = 0;
            stockpiles = 2;
            poleturners = 0;
            bakeries = 4;
            tanners = 0;
            blacksmiths = 0;
            armourers = 0;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_SHERIFF) {
            stockpiles = 3;
            hovels = 6;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 1;
            cathedrals = 1;
            chapels = 2;
            inns = 2;
            breweries = 2;
            bakeries = 0;
            mills = 0;
            poleturners = 0;
            fletchers = 2;
            tanners = 2;
            blacksmiths = 2;
            armourers = 0;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_MARSHAL) {
            stockpiles = 2;
            hovels = 5;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            cathedrals = 0;
            chapels = 0;
            inns = 2;
            breweries = 3;
            bakeries = 0;
            mills = 0;
            poleturners = 0;
            fletchers = 2;
            tanners = 0;
            blacksmiths = 2;
            armourers = 2;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 4;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_ABBOT) {
            mills = 2;
            chapels = 5;
            hovels = 6;
            armories = 1;
            barracks = 1;
            mercenaryPosts = 0;
            cathedrals = 1;
            inns = 3;
            breweries = 6;
            fletchers = 3;
            stockpiles = 2;
            poleturners = 0;
            bakeries = 4;
            tanners = 0;
            blacksmiths = 0;
            armourers = 0;
            engineersGuilds = 1;
            tunnelersGuilds = 0;
            stables = 0;
        }

        for (int step = 0; step <= 50; ++step) {
            if (this->aivs[aivID].currentStepGoal < step) {
                return FALSE;
            }
            if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_disabled) {
                // use the step for the next building that is still missing
                if (stockpiles > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_STORES;
                } else if (hovels > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_HOVEL;
                } else if (granaries > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_GRANARY;
                } else if (marketplaces > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_TRADEPOST;
                } else if (barracks > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_BARRACKS_ARAB;
                } else if (mercenaryPosts > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_BARRACKS_EURO;
                } else if (armories > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_ARMOURY;
                } else if (breweries > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_BREWER;
                } else if (bakeries > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_BAKER;
                } else if (mills > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_MILL;
                } else if (poleturners > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_POLETURNER;
                } else if (fletchers > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_FLETCHER;
                } else if (tanners > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_TANNER;
                } else if (blacksmiths > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_BLACKSMITH;
                } else if (armourers > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_ARMOURER;
                } else if (chapels > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_CHURCH1;
                } else if (inns > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_INN;
                } else if (engineersGuilds > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_ENGINEERS_GUILD;
                } else if (tunnelersGuilds > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_TUNNELERS_GUILD;
                } else if (stables > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_STABLES;
                } else if (cathedrals > 0) {
                    this->aivs[aivID].aivBuildingSteps[step].buildingType = Commands::M_MAPPER_CHURCH3;
                } else {
                    continue;
                }
                this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_unbuilt;
            }

            AIVBuildingStepStatusByte const status = this->aivs[aivID].aivBuildingSteps[step].buildStatus;
            if (status != AIVBSS_disabled) {
                if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_HOVEL) {
                    --hovels;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_STORES) {
                    --stockpiles;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_GRANARY) {
                    --granaries;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_TRADEPOST) {
                    --marketplaces;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_BARRACKS_ARAB) {
                    --barracks;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_BARRACKS_EURO) {
                    --mercenaryPosts;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_ARMOURY) {
                    --armories;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_BREWER) {
                    --breweries;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_BAKER) {
                    --bakeries;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_MILL) {
                    --mills;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_POLETURNER) {
                    --poleturners;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_FLETCHER) {
                    --fletchers;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_TANNER) {
                    --tanners;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_BLACKSMITH) {
                    --blacksmiths;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_ARMOURER) {
                    --armourers;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_CHURCH1) {
                    --chapels;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_INN) {
                    --inns;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType
                    == Commands::M_MAPPER_ENGINEERS_GUILD) {
                    --engineersGuilds;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType
                    == Commands::M_MAPPER_TUNNELERS_GUILD) {
                    --tunnelersGuilds;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_STABLES) {
                    --stables;
                } else if (this->aivs[aivID].aivBuildingSteps[step].buildingType == Commands::M_MAPPER_CHURCH3) {
                    --cathedrals;
                }
            }

            MappersEnum const mapper = (MappersEnum)this->aivs[aivID].aivBuildingSteps[step].buildingType;
            if (isPausing && mapper != Commands::M_MAPPER_HOVEL) {
                continue;
            }
            if (status == AIVBSS_built) {
                // only rebuild buildings that were destroyed
                short const buildingID
                    = DAT_TileMapState::instance
                          .BuildingLayer[this->aivs[aivID].aivBuildingSteps[step].location.tile.tile];
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == MACRO_CALL_MEMBER(
                            Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                            DAT_BuildingsState::ptr)(mapper)) {
                    continue;
                }
            }
            if (DAT_GameState::instance.playerDataArray[playerID].closestEnemyDistanceToTheLord < 120) {
                continue;
            }
            if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(mapper, playerID, FALSE)
                || DAT_BuildingsState::instance.unknownCountdown01 < 20) {
                continue;
            }
            if (mapper == Commands::M_MAPPER_WOODSMAN) {
                if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0) {
                    continue;
                }
            } else if (mapper == Commands::M_MAPPER_GRANARY
                && !DAT_GameState::instance.playerDataArray[playerID].granaryIsAlmostFilledUp) {
                continue;
            }
            if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBeBuildingArmoury, DAT_AICState::ptr)(playerID, mapper)
                || MACRO_CALL_MEMBER(AICState_Func::shouldNotBeBuildingHovel, DAT_AICState::ptr)(playerID, mapper)
                || MACRO_CALL_MEMBER(AICState_Func::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost,
                    DAT_AICState::ptr)(playerID, mapper)) {
                continue;
            }

            int orientation = 15;
            if (mapper == Commands::M_MAPPER_BARRACKS_ARAB || mapper == Commands::M_MAPPER_BARRACKS_EURO
                || mapper == Commands::M_MAPPER_ENGINEERS_GUILD || mapper == Commands::M_MAPPER_TUNNELERS_GUILD
                || mapper == Commands::M_MAPPER_OIL_SMELTER) {
                orientation = this->aivs[aivID].keepOrientation;
            } else if (mapper == Commands::M_MAPPER_POLETURNER || mapper == Commands::M_MAPPER_BLACKSMITH
                || mapper == Commands::M_MAPPER_ARMOURER || mapper == Commands::M_MAPPER_TANNER
                || mapper == Commands::M_MAPPER_FLETCHER || mapper == Commands::M_MAPPER_BAKER
                || mapper == Commands::M_MAPPER_BREWER) {
                orientation = 8;
            }
            if (MACRO_CALL_MEMBER(AICState_Func::shouldWaitWithBuildingAPositiveFearFactor, DAT_AICState::ptr)(
                    playerID, mapper)
                || MACRO_CALL_MEMBER(AICState_Func::shouldWaitWithBuildingNegativeFearFactor, DAT_AICState::ptr)(
                    playerID, mapper)) {
                continue;
            }
            if (orientation == 15) {
                DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
            } else {
                DAT_TileMapState::instance.DAT_TempBuildingRotation = orientation / 2;
            }
            uint const buildingSize = MACRO_CALL_MEMBER(
                Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(mapper);

            uint x;
            uint y;
            if (mapper == Commands::M_MAPPER_STORES) {
                // stockpiles are placed next to each other at the campground
                if (stockpiles == 0) {
                    y = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry - 11;
                    x = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry + 9;
                } else if (stockpiles == 1) {
                    y = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry - 11;
                    x = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry + 4;
                } else if (stockpiles == 2) {
                    y = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry - 6;
                    x = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry + 9;
                }
            } else {
                if (mapper == Commands::M_MAPPER_BARRACKS_ARAB || mapper == Commands::M_MAPPER_BARRACKS_EURO
                    || mapper == Commands::M_MAPPER_ENGINEERS_GUILD || mapper == Commands::M_MAPPER_TUNNELERS_GUILD
                    || mapper == Commands::M_MAPPER_CHURCH3) {
                    MACRO_CALL_MEMBER(AIVState_Func::findAppropriateGridLocationForBuilding, this)(
                        DAT_GameState::instance.playerDataArray[playerID].campground.xEntry / 5,
                        DAT_GameState::instance.playerDataArray[playerID].campground.yEntry / 5);
                } else {
                    MACRO_CALL_MEMBER(AIVState_Func::findSuitableGridLocationFittingCriteria, this)(
                        DAT_GameState::instance.playerDataArray[playerID].campground.xEntry / 5,
                        DAT_GameState::instance.playerDataArray[playerID].campground.yEntry / 5);
                }
                if (this->buildingApproriateGridXPosition == -1 || this->buildingAppropriateGridYPosition == -1) {
                    continue;
                }
                x = this->buildingApproriateGridXPosition * 5;
                y = this->buildingAppropriateGridYPosition * 5;
            }

            int const rowTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                playerID, x, y, mapper, buildingSize);
            // keep orientation is 0, 2, 4 or 6, halving it gives the index of the part offsets
            if (mapper == Commands::M_MAPPER_BARRACKS_EURO || mapper == Commands::M_MAPPER_BARRACKS_ARAB) {
                // the three fields in front of the barracks
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][0].x
                        + x,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][0].y
                        + y,
                    mapper, buildingSize);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].x
                        + x,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].y
                        + y,
                    mapper, buildingSize);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][2].x
                        + x,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][2].y
                        + y,
                    mapper, buildingSize);
            } else if (mapper == Commands::M_MAPPER_ENGINEERS_GUILD || mapper == Commands::M_MAPPER_TUNNELERS_GUILD) {
                // the guild field
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].x
                        + x,
                    DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].y
                        + y,
                    mapper, buildingSize);
            } else if (mapper == Commands::M_MAPPER_OIL_SMELTER) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID,
                    DAT_TerrainDefinedData::instance.field63_0x19c[this->aivs[aivID].keepOrientation / 2].x + x,
                    DAT_TerrainDefinedData::instance.field63_0x19c[this->aivs[aivID].keepOrientation / 2].y + y, mapper,
                    buildingSize);
            }

            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID, x, y, mapper,
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(
                    mapper),
                orientation);
            int const placedID = DAT_TileMapState::instance.placedBuildingID;
            if (!DAT_TileMapState::instance.buildingPlacementFail) {
                DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].field245_0x2c8 = 1;
                MACRO_CALL_MEMBER(AICState_Func::setupWorkshopProductionType, DAT_AICState::ptr)(playerID, placedID);
                this->aivs[aivID].aivBuildingSteps[step].location.tile.tile = rowTile + x;
                if (!DAT_TileMapState::instance.buildingPlacementFail) {
                    this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
                }
            }
            this->aivs[aivID].aivBuildingSteps[step].wait
                = this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built ? 10 : 16;
            if (!DAT_TileMapState::instance.buildingPlacementFail) {
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
