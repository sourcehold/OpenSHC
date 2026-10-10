#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
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

    using AI::Tribes::AITribeType;
    using Game::GameMode;
    using Map::Buildings::BuildingLogicalState;
    using Map::Units::UnitInstructionType;
    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::States::UnitState;
    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041E240
    void Buildings::UpdateFireBallistaBuilding()
    {
        int* piVar1;
        short sVar2;
        int _offset;
        int _lordType;
        int _fireballistaUnit;
        int _engineer;
        short* _pWorkers;
        short* _pBuildingWorkerID;
        int _owner2;
        int _counter1;
        short* _pWorkerID;
        int _owner;
        int* _pBuildingWorkerUID;
        int _buildingID2;
        int _counter2;
        int* _pWorkerUID;
        bool _menuIsBuildingAndStatus;
        int _employeeCount3;
        int _buildingID;
        int _wave;
        int _fullID;
        short _employeeCount;
        int* _pProgress1;
        int* _pProgress2;
        short _employeeCount2;
        _fireballistaUnit = DAT_CurrentBuildingID::instance;
        _owner = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        _wave = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave;
        if (((0 < _wave) && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY))
            && ((char)DAT_TroopValueState::instance.attackInfo.nof_tribes[_wave] <= '\0')) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = Map::Buildings::BLS_REMOVE;
        }
        if (DAT_BuildingsState::instance.buildings[_fireballistaUnit].oldVisualActiveState == -1) {
            _fullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner];
            DAT_BuildingsState::instance.buildings[_fireballistaUnit].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[_fireballistaUnit].playerColorUnk
                = (int)DAT_BuildingsState::instance.buildings[_fireballistaUnit].owner;
            DAT_BuildingsState::instance.buildings[_fireballistaUnit].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[_fireballistaUnit].displayOwnerFlag = 0;
            if (_fullID == -1) {
                _lordType = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(_owner);
                _fireballistaUnit = DAT_CurrentBuildingID::instance;
                if (!_lordType) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
                }
            } else {
                DAT_BuildingsState::instance.buildings[_fireballistaUnit].animationFrame = 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                _fireballistaUnit);
            _fireballistaUnit = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        _pProgress1 = &DAT_BuildingsState::instance.buildings[_fireballistaUnit].buildingProgress;
        /*
          update building progress with the amount of employees in it
         */
        *_pProgress1
            = *_pProgress1 + (int)DAT_BuildingsState::instance.buildings[_fireballistaUnit].currentEmployeeCount;
        if (320 < DAT_BuildingsState::instance.buildings[_fireballistaUnit].buildingProgress) {
            /*
              if progress > 320
             */
            _owner2 = (int)DAT_BuildingsState::instance.buildings[_fireballistaUnit].owner;
            _fireballistaUnit = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                _owner2, _owner2, (int)((int)((short)DAT_BuildingsState::instance.buildings[_fireballistaUnit].x * 8)),
                (int)((int)((short)DAT_BuildingsState::instance.buildings[_fireballistaUnit].y * 8)),
                (int)((int)(DAT_BuildingsState::instance.buildings[_fireballistaUnit].terrainHeightUnk)),
                Map::Units::UT_S_FBALLISTA);
            if (!_fireballistaUnit) {
                _pProgress2 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
                *_pProgress2 = *_pProgress2
                    - (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            }
            MACRO_CALL_MEMBER(AI::AICState_Func::generateSiegeCreationInformation, DAT_AICState::ptr)(
                (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                DAT_CurrentBuildingID::instance, _fireballistaUnit);
            _employeeCount
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            if (_employeeCount == 2) {
                _pWorkers = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                if (DAT_UnitsState::instance
                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0]]
                        .aiUnitBehaviourType
                    == 0x16) {
                    DAT_UnitsState::instance.units[_fireballistaUnit].aiUnitBehaviourType = 0x15;
                }
                _counter1 = 2;
                do {
                    sVar2 = *_pWorkers;
                    _pWorkers = _pWorkers + 1;
                    _counter1 = _counter1 + -1;
                    DAT_UnitsState::instance.units[sVar2].state.generic = Map::Units::States::US_AIM_WEAPONUnk;
                } while (_counter1);
            } else {
                _counter2 = 0;
                if (0 < _employeeCount) {
                    do {
                        _engineer = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .workerID[_counter2];
                        DAT_UnitsState::instance.units[_engineer].state.generic
                            = Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[_engineer].disappearFadeAlphaCountdown = 0x20;
                        DAT_UnitsState::instance.units[_engineer].engineerManningSiegeStateRef_checkType = 0xfe;
                        DAT_UnitsState::instance.units[_engineer].cachedState
                            = Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[_engineer].totalSizeOfPathPlan = 0;
                        DAT_UnitsState::instance.units[_engineer].movementCooldown = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::resetUnitMovementState,
                            DAT_UnitsState::ptr)(_engineer);
                        sVar2 = DAT_UnitsState::instance.units[_engineer].aiUnitBehaviourType;
                        DAT_UnitsState::instance.units[_engineer].targetingType
                            = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                        DAT_UnitsState::instance.units[_engineer].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            = (short)_fireballistaUnit;
                        if (sVar2 == 0x16) {
                            DAT_UnitsState::instance.units[_fireballistaUnit].aiUnitBehaviourType = 0x15;
                        }
                        _counter2 = _counter2 + 1;
                    } while (_counter2
                        < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
            }
            MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_fireballistaUnit].x,
                (int)((int)(DAT_UnitsState::instance.units[_fireballistaUnit].y)),
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.xEntry,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.yEntry);
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[_owner] == 0)) {
                DAT_UnitsState::instance.units[_fireballistaUnit].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            } else {
                _buildingID2 = DAT_GameState::instance.playerDataArray[_owner].keep.id;
                DAT_UnitsState::instance.units[_fireballistaUnit].facingDirection = 0;
                if (!_buildingID2) {
                    piVar1 = &DAT_GameState::instance.playerDataArray[_owner].counter;
                    *piVar1 = *piVar1 + 2;
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
                _fireballistaUnit, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave,
                ((AITribeType)0x18), (undefined4)((int)(_owner)));
            _buildingID2 = DAT_CurrentBuildingID::instance;
            DAT_UnitsState::instance.units[_fireballistaUnit].unknownSiegeTentRelated02
                = (char)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                      .unknownSiegeTentRelated01
                + 1;
            _employeeCount2 = DAT_BuildingsState::instance.buildings[_buildingID2].currentEmployeeCount;
            _employeeCount3 = (int)_employeeCount2;
            DAT_UnitsState::instance.units[_fireballistaUnit].logicalState = ((UnitLogicState)5);
            if (0 < _employeeCount3) {
                _pBuildingWorkerUID = DAT_BuildingsState::instance.buildings[_buildingID2].workerUID;
                _pWorkerUID = DAT_UnitsState::instance.units[_fireballistaUnit].manningEngineerUIDRef;
                _pWorkerID = DAT_UnitsState::instance.units[_fireballistaUnit].manningEngineerRef;
                _pBuildingWorkerID = DAT_BuildingsState::instance.buildings[_buildingID2].workerID;
                do {
                    *_pWorkerID = *_pBuildingWorkerID;
                    *_pWorkerUID = *_pBuildingWorkerUID;
                    _pBuildingWorkerID = _pBuildingWorkerID + 1;
                    _pWorkerID = _pWorkerID + 1;
                    _pBuildingWorkerUID = _pBuildingWorkerUID + 1;
                    _pWorkerUID = _pWorkerUID + 1;
                    _employeeCount3 = _employeeCount3 + -1;
                    _buildingID2 = DAT_CurrentBuildingID::instance;
                } while (_employeeCount3);
            }
            _menuIsBuildingAndStatus
                = DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
            DAT_UnitsState::instance.units[_fireballistaUnit]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = _employeeCount2;
            if ((_menuIsBuildingAndStatus) && (_buildingID2 == DAT_BuildingsState::instance.menuSelectedBuildingID)) {
                DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 2;
                DAT_BuildingsState::instance.unitID = _fireballistaUnit;
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                _buildingID2);
        }
    }

}
}
