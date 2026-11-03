#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041E240
    void Buildings::UpdateFireBallistaBuilding()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        // nof_tribes is declared byte, but the original reads it signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave > 0
            && DAT_GameSynchronyState::instance.currentGameMode == 0
            && (char)DAT_TroopValueState::instance.attackInfo
                    .nof_tribes[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave]
                <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = OpenSHC::Map::Buildings::BLS_REMOVE;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState == -1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] != -1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 1;
            } else if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                           DAT_GameSynchronyState::ptr)(owner)
                == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress
            += DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress <= 320) {
            return;
        }
        int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x * 8,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y * 8,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].terrainHeightUnk,
            OpenSHC::Map::Units::UT_S_FBALLISTA);
        if (unitID == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress
                -= DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::generateSiegeCreationInformation, DAT_AICState::ptr)(
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
            DAT_CurrentBuildingID::instance, unitID);
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount != 2) {
            for (int i = 0;
                i < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount; ++i) {
                int const workerID
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i];
                DAT_UnitsState::instance.units[workerID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[workerID].disappearFadeAlphaCountdown = 32;
                DAT_UnitsState::instance.units[workerID].engineerManningSiegeStateRef_checkType = 0xfe;
                DAT_UnitsState::instance.units[workerID].cachedState = 0;
                DAT_UnitsState::instance.units[workerID].totalSizeOfPathPlan = 0;
                DAT_UnitsState::instance.units[workerID].movementCooldown = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    workerID);
                DAT_UnitsState::instance.units[workerID].targetingType = OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                DAT_UnitsState::instance.units[workerID].targetedUnitID__OR__engineerMannedSiegeEngineRef = unitID;
                if (DAT_UnitsState::instance.units[workerID].aiUnitBehaviourType == OpenSHC::AI::AIUBT_HARASS_SIEGE) {
                    DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = OpenSHC::AI::AIUBT_SIEGE_01;
                }
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
        } else {
            if (DAT_UnitsState::instance
                    .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0]]
                    .aiUnitBehaviourType
                == OpenSHC::AI::AIUBT_HARASS_SIEGE) {
                DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = OpenSHC::AI::AIUBT_SIEGE_01;
            }
            for (int i = 0; i != 2; ++i) {
                DAT_UnitsState::instance
                    .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i]]
                    .state.generic = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
            DAT_UnitsState::instance.units[unitID].y,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.xEntry,
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .campground.yEntry);
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[owner] == 0) {
            DAT_UnitsState::instance.units[unitID].facingDirection = DAT_DirectionAlgorithmState::instance.orientation;
        } else {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            if (DAT_GameState::instance.playerDataArray[owner].keep.id == 0) {
                DAT_GameState::instance.playerDataArray[owner].counter += 2;
            }
        }
        // AI tribe type 24 and unit logic state 5 have no constants.
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
            unitID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave,
            (OpenSHC::AI::Tribes::AITribeType)24, owner);
        DAT_UnitsState::instance.units[unitID].logicalState = 5;
        DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownSiegeTentRelated01 + 1;
        short const employeeCount
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
        for (int i = 0; i < employeeCount; ++i) {
            DAT_UnitsState::instance.units[unitID].manningEngineerRef[i]
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i];
            DAT_UnitsState::instance.units[unitID].manningEngineerUIDRef[i]
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[i];
        }
        DAT_UnitsState::instance.units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
            = employeeCount;
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
            && DAT_CurrentBuildingID::instance == DAT_BuildingsState::instance.menuSelectedBuildingID) {
            DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 2;
            DAT_BuildingsState::instance.unitID = unitID;
        }
        DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
            DAT_CurrentBuildingID::instance);
    }

}
}
