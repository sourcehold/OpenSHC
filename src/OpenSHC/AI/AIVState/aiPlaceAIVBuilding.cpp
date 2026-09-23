#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ED410
    BOOLEnum AIVState::aiPlaceAIVBuilding(PlayerID playerID, int step, int isPausing)
    {
        int const aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
        MappersEnum const mapper = (MappersEnum)this->aivs[aivID].aivBuildingSteps[step].buildingType;

        // when pausing, only hovels are built
        if (isPausing && mapper != Commands::M_MAPPER_HOVEL) {
            return FALSE;
        }
        // disabled steps and steps without room are never built
        if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_disabled) {
            return FALSE;
        }
        if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_insufficient_roomUnk) {
            return FALSE;
        }
        if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_insufficient_resources
            && this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
            // wait for more resources
            --this->aivs[aivID].aivBuildingSteps[step].wait;
            return FALSE;
        }
        if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built) {
            if (DAT_GameState::instance.playerDataArray[playerID].closestEnemyDistanceToTheLord < 120) {
                return FALSE;
            }
        } else if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                       DAT_GameState::ptr)(mapper, playerID, FALSE)) {
            return FALSE;
        }
        if (DAT_BuildingsState::instance.unknownCountdown01 < 20) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::mapperIsWoodCuttersHutWhileNoWoodAvailable, DAT_AICState::ptr)(
                playerID, mapper)) {
            return FALSE;
        }

        if (mapper == Commands::M_MAPPER_MOAT) {
            if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built
                && this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
                --this->aivs[aivID].aivBuildingSteps[step].wait;
                return FALSE;
            }
            for (int i = 0; i < this->aivs[aivID].aivBuildingSteps[step].quantity; ++i) {
                int const tile
                    = this->aivs[aivID].locationsArray[this->aivs[aivID].aivBuildingSteps[step].location.tile.tile + i];
                MACRO_CALL_MEMBER(Map::TileMapState_Func::planMoat, DAT_TileMapState::ptr)(
                    playerID, tile, DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
            }
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
            this->aivs[aivID].aivBuildingSteps[step].wait = 50;
            return FALSE;
        }

        if (mapper == Commands::M_MAPPER_PITCH_DITCH) {
            if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built) {
                if (this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
                    --this->aivs[aivID].aivBuildingSteps[step].wait;
                    return FALSE;
                }
                if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                        DAT_GameState::ptr)(Commands::M_MAPPER_PITCH_DITCH, playerID, FALSE)) {
                    return FALSE;
                }
            }
            for (int i = 0; i < this->aivs[aivID].aivBuildingSteps[step].quantity; ++i) {
                int const tile
                    = this->aivs[aivID].locationsArray[this->aivs[aivID].aivBuildingSteps[step].location.tile.tile + i];
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID, x, y,
                    Commands::M_MAPPER_PITCH_DITCH,
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeForCommandBuildingType,
                        DAT_TileMapState::ptr)(Commands::M_MAPPER_PITCH_DITCH),
                    15);
            }
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
            this->aivs[aivID].aivBuildingSteps[step].wait = 200;
            return FALSE;
        }

        // walls
        if (mapper == Commands::M_MAPPER_WALL || mapper == Commands::M_MAPPER_WOODWALL
            || mapper == Commands::M_MAPPER_CRENAL || mapper == Commands::M_MAPPER_CRENAL2) {
            if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built) {
                if (this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
                    --this->aivs[aivID].aivBuildingSteps[step].wait;
                    return FALSE;
                }
                if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_STONE]
                    <= 0) {
                    // no stone, request some
                    if (DAT_GameState::instance.playerDataArray[playerID]
                            .resourcesToAcquireArray[Game::Resources::RT_STONE]
                        > 0) {
                        return FALSE;
                    }
                    DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[Game::Resources::RT_STONE]
                        = 5;
                    return FALSE;
                }
            }
            for (int i = 0; i < this->aivs[aivID].aivBuildingSteps[step].quantity; ++i) {
                int const tile
                    = this->aivs[aivID].locationsArray[this->aivs[aivID].aivBuildingSteps[step].location.tile.tile + i];
                uint const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                uint const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                    playerID, x, y, mapper, 1);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeDefensiveStructureTile, DAT_TileMapState::ptr)(
                    playerID, x, y, mapper);
            }
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
            this->aivs[aivID].aivBuildingSteps[step].wait = 20;
            if (!DAT_TileMapState::instance.illegalBuild) {
                return TRUE;
            }
            return FALSE;
        }

        // stairs
        if (mapper == Commands::M_MAPPER_STAIR1 || mapper == Commands::M_MAPPER_STAIR2
            || mapper == Commands::M_MAPPER_STAIR3 || mapper == Commands::M_MAPPER_STAIR4
            || mapper == Commands::M_MAPPER_STAIR5 || mapper == Commands::M_MAPPER_STAIR6) {
            if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built
                && this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
                --this->aivs[aivID].aivBuildingSteps[step].wait;
                return FALSE;
            }
            uint const y
                = DAT_ViewportRenderState::instance
                      .tileTranslationMatrix_YComponent[this->aivs[aivID].aivBuildingSteps[step].location.tile.tile];
            uint const x = this->aivs[aivID].aivBuildingSteps[step].location.tile.tile
                - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
                playerID, x, y, mapper, 1);
            MACRO_CALL_MEMBER(Map::TileMapState_Func::placeDefensiveStructureTile, DAT_TileMapState::ptr)(
                playerID, x, y, mapper);
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
            this->aivs[aivID].aivBuildingSteps[step].wait = 1;
            if (!DAT_TileMapState::instance.illegalBuild) {
                return TRUE;
            }
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_insufficient_resources;
            this->aivs[aivID].aivBuildingSteps[step].wait = 4;
            return FALSE;
        }

        if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBeBuildingGranary, DAT_AICState::ptr)(playerID, mapper)) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBeBuildingArmoury, DAT_AICState::ptr)(playerID, mapper)) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBeBuildingHovel, DAT_AICState::ptr)(playerID, mapper)) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBuildMarketArmoryGranaryBarracksMercenarypost, DAT_AICState::ptr)(
                playerID, mapper)) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldNotBuildKillingPits, DAT_AICState::ptr)(playerID, mapper)) {
            return FALSE;
        }

        int const tile = this->aivs[aivID].aivBuildingSteps[step].location.tile.tile;
        int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
        int orientation = 15;
        if (mapper == Commands::M_MAPPER_BARRACKS_ARAB || mapper == Commands::M_MAPPER_BARRACKS_EURO
            || mapper == Commands::M_MAPPER_ENGINEERS_GUILD || mapper == Commands::M_MAPPER_TUNNELERS_GUILD
            || mapper == Commands::M_MAPPER_OIL_SMELTER) {
            orientation = this->aivs[aivID].keepOrientation;
        } else if (mapper == Commands::M_MAPPER_GATE_STONE1A || mapper == Commands::M_MAPPER_GATE_STONE2A) {
            if (this->aivs[aivID].keepOrientation == 0 || this->aivs[aivID].keepOrientation == 4) {
                orientation = 81;
            } else {
                orientation = 80;
            }
        } else if (mapper == Commands::M_MAPPER_GATE_STONE1B || mapper == Commands::M_MAPPER_GATE_STONE2B) {
            if (this->aivs[aivID].keepOrientation == 2 || this->aivs[aivID].keepOrientation == 6) {
                orientation = 81;
            } else {
                orientation = 80;
            }
        } else if (mapper == Commands::M_MAPPER_POLETURNER || mapper == Commands::M_MAPPER_BLACKSMITH
            || mapper == Commands::M_MAPPER_ARMOURER || mapper == Commands::M_MAPPER_TANNER
            || mapper == Commands::M_MAPPER_FLETCHER || mapper == Commands::M_MAPPER_BAKER
            || mapper == Commands::M_MAPPER_BREWER) {
            orientation = 8;
        } else if (mapper == Commands::M_MAPPER_DRAWBRIDGE) {
            DAT_TileMapState::instance.buildingPlacementFail = FALSE;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::checkDrawbridgePlacement, DAT_TileMapState::ptr)(x, y);
            if (DAT_TileMapState::instance.buildingPlacementFail) {
                return FALSE;
            }
            orientation = DAT_TileMapState::instance.uiBuildingRotation;
        }

        if (this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built) {
            // rebuild a destroyed building
            int const buildingID = (short)DAT_TileMapState::instance.BuildingLayer[tile];
            if ((short)DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(mapper)) {
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].aiBuildingDestroyChoiceTracker == 0
                && DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker == 0
                && this->aivs[aivID].aivBuildingSteps[step].wait > 0) {
                --this->aivs[aivID].aivBuildingSteps[step].wait;
                return FALSE;
            }
            if (!MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(mapper, playerID, FALSE)) {
                return FALSE;
            }
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldWaitWithBuildingAPositiveFearFactor, DAT_AICState::ptr)(
                playerID, mapper)) {
            return FALSE;
        }
        if (MACRO_CALL_MEMBER(AICState_Func::shouldWaitWithBuildingNegativeFearFactor, DAT_AICState::ptr)(
                playerID, mapper)) {
            return FALSE;
        }

        if (orientation == 15) {
            DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
        } else {
            DAT_TileMapState::instance.DAT_TempBuildingRotation = orientation / 2;
        }
        int const buildingSize = MACRO_CALL_MEMBER(
            Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(mapper);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(
            playerID, x, y, mapper, buildingSize);
        // keep orientation is 0, 2, 4 or 6, halving it gives the index of the part offsets
        if (mapper == Commands::M_MAPPER_BARRACKS_EURO || mapper == Commands::M_MAPPER_BARRACKS_ARAB) {
            // the three fields in front of the barracks
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][0].x + x,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][0].y + y,
                mapper, buildingSize);
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].x + x,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].y + y,
                mapper, buildingSize);
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][2].x + x,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][2].y + y,
                mapper, buildingSize);

        } else if (mapper == Commands::M_MAPPER_ENGINEERS_GUILD || mapper == Commands::M_MAPPER_TUNNELERS_GUILD) {
            // the guild field
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(playerID,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].x + x,
                DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->aivs[aivID].keepOrientation / 2][1].y + y,
                mapper, buildingSize);
        } else if (mapper == Commands::M_MAPPER_OIL_SMELTER) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareAreaForBuildingPlacement, DAT_TileMapState::ptr)(playerID,
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
        }
        if (!DAT_TileMapState::instance.buildingPlacementFail) {
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_built;
        } else if (mapper == Commands::M_MAPPER_WHEATFARM || mapper == Commands::M_MAPPER_HOPSFARM
            || mapper == Commands::M_MAPPER_APPLEFARM || mapper == Commands::M_MAPPER_CATTLEFARM) {
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_insufficient_roomUnk;
        } else {
            this->aivs[aivID].aivBuildingSteps[step].buildStatus = AIVBSS_insufficient_resources;
        }
        this->aivs[aivID].aivBuildingSteps[step].wait
            = this->aivs[aivID].aivBuildingSteps[step].buildStatus == AIVBSS_built ? 10 : 16;
        if (DAT_TileMapState::instance.buildingPlacementFail) {
            return FALSE;
        }
        return TRUE;
    }

}
}
