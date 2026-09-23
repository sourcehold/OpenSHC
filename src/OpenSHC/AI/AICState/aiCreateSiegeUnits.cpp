#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2000
    void AICState::aiCreateSiegeUnits(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int guildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
        if (guildID <= 0)
            return;
        if (DAT_BuildingsState::instance.buildings[guildID].buildingType != OpenSHC::Map::Buildings::BT_ENGINEERSGUILD)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;

        // The original also processes index 4, one past the end of SiegeEngineMetaInfoArray.
        for (int siegeIndex = 0; siegeIndex < 5; siegeIndex++) {
            UnitType unitType
                = (UnitType)DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex].unitType;
            int slot = DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex].slot;
            int locationCount
                = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[slot];
            if (locationCount >= 4)
                locationCount = 3;

            for (int i = 0; i < locationCount; i++) {
                int location = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[slot][i];
                if (location <= 0)
                    continue;

                int existingBuildingID = (short)DAT_TileMapState::instance.BuildingLayer[location];
                int unitID = DAT_GameState::instance.playerDataArray[playerID]
                                 .aiSiegeCreationInformation[siegeIndex][i]
                                 .unitID;
                int uid
                    = DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].uid;
                int buildingID = DAT_GameState::instance.playerDataArray[playerID]
                                     .aiSiegeCreationInformation[siegeIndex][i]
                                     .buildingID;

                if (unitID != 0 && DAT_UnitsState::instance.units[unitID].uid != uid) {
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].unitID
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].uid = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].delay
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].unknown
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID]
                        .aiSiegeCreationInformation[siegeIndex][i]
                        .buildingID = 0;
                    continue;
                }
                if (buildingID != 0 && DAT_BuildingsState::instance.buildings[buildingID].uid != uid) {
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].unitID
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].uid = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].delay
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].unknown
                        = 0;
                    DAT_GameState::instance.playerDataArray[playerID]
                        .aiSiegeCreationInformation[siegeIndex][i]
                        .buildingID = 0;
                    continue;
                }

                if (unitID == 0) {
                    if (buildingID != 0) {
                        int requiredEngineers = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getRequiredEngineerCountForSiegeBuilding,
                            DAT_BuildingsState::ptr)(buildingID);
                        if (DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount
                            == requiredEngineers)
                            continue;
                        if (requiredEngineers
                            > DAT_GameState::instance.playerDataArray[playerID].engineerCountRelated) {
                            DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = TRUE;
                            continue;
                        }
                        int tribeID
                            = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                                this)(playerID, requiredEngineers);
                        DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                            = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction,
                            DAT_TribesState::ptr)(tribeID,
                            OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                            DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
                        return;
                    }

                    if (existingBuildingID == 0) {
                        if (siegeIndex < 2)
                            continue;
                    } else if (siegeIndex < 2) {
                        if (DAT_BuildingsState::instance.buildings[existingBuildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_TOWER4
                            && DAT_BuildingsState::instance.buildings[existingBuildingID].buildingType
                                != OpenSHC::Map::Buildings::BT_TOWER5)
                            continue;
                    }

                    int requiredGold
                        = DAT_BuildingsState::instance
                              .buildingCosts[DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex]
                                      .buildingType]
                              .requiredGold;
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].delay++;
                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                            + this->aics[aiType - 1].defSiegeEngineGoldThreshold
                        < requiredGold)
                        continue;
                    if (DAT_GameState::instance.playerDataArray[playerID]
                            .aiSiegeCreationInformation[siegeIndex][i]
                            .delay
                        < this->aics[aiType - 1].defSiegeEngineBuildDelay)
                        continue;

                    int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[location];
                    int x = location - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    if (siegeIndex < 2) {
                        int spawnedUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                            DAT_UnitsState::ptr)(playerID, playerID, x * 8 + 4, y * 8 + 4,
                            DAT_BuildingsState::instance.buildings[existingBuildingID].terrainHeightUnk, unitType);
                        DAT_GameState::instance.playerDataArray[playerID]
                            .aiSiegeCreationInformation[siegeIndex][i]
                            .unitID = spawnedUnitID;
                        DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].uid
                            = DAT_UnitsState::instance.units[spawnedUnitID].uid;
                        DAT_GameState::instance.playerDataArray[playerID]
                            .aiSiegeCreationInformation[siegeIndex][i]
                            .buildingID = 0;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
                            DAT_BuildingsState::ptr)(playerID,
                            (BuildingType)DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex]
                                .buildingType,
                            0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                            playerID, x, y,
                            (MappersEnum)(ushort)DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex]
                                .commandBuildingType,
                            3, 15);
                        if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                            DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                                -= requiredGold;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[siegeIndex][i]
                                .unitID = 0;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[siegeIndex][i]
                                .uid
                                = DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID]
                                      .uid;
                            DAT_GameState::instance.playerDataArray[playerID]
                                .aiSiegeCreationInformation[siegeIndex][i]
                                .buildingID = DAT_TileMapState::instance.placedBuildingID;
                        }
                    }
                    DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].delay
                        = 0;
                    return;
                }

                if (unitID != 0) {
                    if (buildingID != 0) {
                        int requiredEngineers = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getRequiredEngineerCountForSiegeBuilding,
                            DAT_BuildingsState::ptr)(buildingID);
                        if (DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount
                            == requiredEngineers)
                            continue;
                        if (requiredEngineers
                            > DAT_GameState::instance.playerDataArray[playerID].engineerCountRelated) {
                            DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = TRUE;
                            continue;
                        }
                        int tribeID
                            = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                                this)(playerID, requiredEngineers);
                        DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                        DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                            = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction,
                            DAT_TribesState::ptr)(tribeID,
                            OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                            DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
                        return;
                    }
                    int remainingEngineers
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                            DAT_UnitsState::ptr)(unitID);
                    if (remainingEngineers <= 0)
                        continue;
                    if (DAT_GameState::instance.playerDataArray[playerID].engineerCountRelated < remainingEngineers) {
                        DAT_GameState::instance.playerDataArray[playerID].isEngineerRequired = TRUE;
                        continue;
                    }
                    int tribeID = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::assignRequiredIdleEngineersToNewTribe,
                        this)(playerID, remainingEngineers);
                    int targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                    if (targetUnitID == 0)
                        continue;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                            (short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[targetUnitID].tile],
                            0)
                        == 0)
                        continue;
                    DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = OpenSHC::Map::Units::STBT_0x41c;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        tribeID, OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT, unitID,
                        DAT_UnitsState::instance.units[unitID].uid, 0);
                    return;
                }
            }
        }
    }
}
}
