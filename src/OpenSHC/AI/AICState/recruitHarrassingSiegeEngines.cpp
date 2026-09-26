#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD2A0
    void AICState::recruitHarrassingSiegeEngines(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        int engineersGuild = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;

        if (aiType == 0) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
            < 500) {
            return;
        }

        int aicIndex = aiType - 1;
        int harrassingSiegeEnginesMax = this->aics[aicIndex].HarassingSiegeEnginesMax;
        if (harrassingSiegeEnginesMax <= 0) {
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout != 0) {
            DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout -= 1;
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].harassingSiegeEnginesCountUnk
            >= harrassingSiegeEnginesMax) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].unknownHarrassingSiegeRelated >= 20) {
            return;
        }

        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[165];
        if (tribeID == 0
            || DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[165]
            || DAT_TribesState::instance.tribes[tribeID].size < 2) {
            // Not enough engineers yet: recruit one at the engineers guild
            if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0
                || DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    < 30
                || engineersGuild <= 0
                || DAT_BuildingsState::instance.buildings[engineersGuild].buildingType
                    != OpenSHC::Map::Buildings::BT_ENGINEERSGUILD) {
                return;
            }

            uint unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                OpenSHC::Map::Units::UT_E_ENGINEER, engineersGuild, playerID, 0);
            if (unitID == 0) {
                return;
            }

            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[165]) {
                tribeID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            }

            DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[165] = (short)tribeID;
            DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[165]
                = DAT_TribesState::instance.tribes[tribeID].uid;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                unitID, tribeID);
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = OpenSHC::AI::AIUBT_HARASS_SIEGE;
        } else {
            // Enough engineers: pick the next siege engine from the AIC list and place its tent
            if (DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex >= 8) {
                DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex = 0;
            }
            if ((&this->aics[aicIndex].HarassingSiegeEngine1)[DAT_GameState::instance.playerDataArray[playerID]
                        .harrassingSiegeEnginesIndex]
                == 0) {
                DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex = 0;
            }

            int engineIndex = DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex;
            MappersEnum siegeEngineToBuild = (MappersEnum)(&this->aics[aicIndex].HarassingSiegeEngine1)[engineIndex];
            DAT_GameState::instance.playerDataArray[playerID].harrassingSiegeEnginesIndex = engineIndex + 1;

            if (MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::findSpotNearEngineersGuild, DAT_AIVState::ptr)(playerID)
                == 0) {
                return;
            }

            DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;
            DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType
                = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;

            // Place the siege tent
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
                DAT_AIVState::instance.buildingApproriateGridXPosition * 5,
                DAT_AIVState::instance.buildingAppropriateGridYPosition * 5, siegeEngineToBuild, 3, 15);
            if (DAT_TileMapState::instance.buildingPlacementFail != FALSE) {
                return;
            }

            int buildingID = DAT_TileMapState::instance.placedBuildingID;
            DAT_BuildingsState::instance.buildings[buildingID].attackWave = 0;
            DAT_BuildingsState::instance.buildings[buildingID].unknownSiegeTentRelated01 = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
        }

        // Point all harassing siege engines at the currently attacked player
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                && DAT_UnitsState::instance.units[unitID].dying == 0
                && (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                    || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA)
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType == OpenSHC::AI::AIUBT_SIEGE_01) {
                DAT_UnitsState::instance.units[unitID].siegeTargetPlayerID
                    = (short)DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
            }
        }

        DAT_GameState::instance.playerDataArray[playerID].harrasingEngineRecruitTimeout = 8;
    }

}
}
