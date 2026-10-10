#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x0041F3B0
    void Buildings::UpdateCatapultBuilding()
    {
        short sVar1;
        int unitID;
        short* psVar2;
        short* psVar3;
        int iVar4;
        int iVar5;
        int* piVar6;
        int iVar7;
        int* piVar8;
        bool bVar9;
        iVar7 = DAT_CurrentBuildingID::instance;
        iVar5 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        iVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave;
        if (((0 < iVar4) && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY))
            && ((char)DAT_TroopValueState::instance.attackInfo.nof_tribes[iVar4] <= '\0')) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = Map::Buildings::BLS_REMOVE;
        }
        if (DAT_BuildingsState::instance.buildings[iVar7].oldVisualActiveState == -1) {
            iVar4 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar5];
            DAT_BuildingsState::instance.buildings[iVar7].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[iVar7].playerColorUnk
                = (int)DAT_BuildingsState::instance.buildings[iVar7].owner;
            DAT_BuildingsState::instance.buildings[iVar7].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[iVar7].displayOwnerFlag = 0;
            if (iVar4 == -1) {
                iVar4 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(iVar5);
                iVar7 = DAT_CurrentBuildingID::instance;
                if (!iVar4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
                }
            } else {
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame = 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar7);
            iVar7 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        piVar6 = &DAT_BuildingsState::instance.buildings[iVar7].buildingProgress;
        *piVar6 = *piVar6 + (int)DAT_BuildingsState::instance.buildings[iVar7].currentEmployeeCount;
        if (0x140 < DAT_BuildingsState::instance.buildings[iVar7].buildingProgress) {
            /*
              Spawn catapult.
             */
            iVar4 = (int)DAT_BuildingsState::instance.buildings[iVar7].owner;
            iVar4 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(iVar4,
                iVar4, (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].x * 8)),
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y * 8)),
                (int)((int)(DAT_BuildingsState::instance.buildings[iVar7].terrainHeightUnk)),
                Map::Units::UT_S_CATAPULT);
            if (!iVar4) {
                piVar6 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
                *piVar6 = *piVar6
                    - (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            }
            sVar1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            if (sVar1 == 2) {
                psVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                if (DAT_UnitsState::instance
                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0]]
                        .aiUnitBehaviourType
                    == 0x16) {
                    DAT_UnitsState::instance.units[iVar4].aiUnitBehaviourType = 0x15;
                }
                iVar7 = 2;
                do {
                    sVar1 = *psVar2;
                    psVar2 = psVar2 + 1;
                    iVar7 = iVar7 + -1;
                    DAT_UnitsState::instance.units[sVar1].state.generic = Map::Units::States::US_AIM_WEAPONUnk;
                } while (iVar7);
            } else {
                iVar7 = 0;
                if (0 < sVar1) {
                    do {
                        unitID = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                     .workerID[iVar7];
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0x20;
                        DAT_UnitsState::instance.units[unitID].engineerManningSiegeStateRef_checkType = 0xfe;
                        DAT_UnitsState::instance.units[unitID].cachedState
                            = Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan = 0;
                        DAT_UnitsState::instance.units[unitID].movementCooldown = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(unitID);
                        sVar1 = DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType;
                        DAT_UnitsState::instance.units[unitID].targetingType
                            = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                        DAT_UnitsState::instance.units[unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            = (short)iVar4;
                        if (sVar1 == 0x16) {
                            DAT_UnitsState::instance.units[iVar4].aiUnitBehaviourType = 0x15;
                        }
                        iVar7 = iVar7 + 1;
                    } while (iVar7
                        < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
            }
            MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[iVar4].x,
                (int)((int)(DAT_UnitsState::instance.units[iVar4].y)),
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.xEntry,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.yEntry);
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar5] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[iVar5] == 0)) {
                DAT_UnitsState::instance.units[iVar4].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            } else {
                iVar7 = DAT_GameState::instance.playerDataArray[iVar5].keep.id;
                DAT_UnitsState::instance.units[iVar4].facingDirection = 0;
                if (!iVar7) {
                    piVar6 = &DAT_GameState::instance.playerDataArray[iVar5].counter;
                    *piVar6 = *piVar6 + 2;
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
                iVar4, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave,
                ((AITribeType)0x16), (undefined4)((int)(iVar5)));
            iVar7 = DAT_CurrentBuildingID::instance;
            sVar1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unknownSiegeTentRelated01;
            bVar9 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER;
            DAT_UnitsState::instance.units[iVar4].logicalState = ((UnitLogicState)5);
            DAT_UnitsState::instance.units[iVar4].unknownSiegeTentRelated02 = (char)sVar1 + 1;
            if (bVar9) {
                DAT_UnitsState::instance.units[iVar4].siegeTargetPlayerID
                    = (short)DAT_GameState::instance.playerDataArray[iVar5].attackedPlayerID;
            }
            sVar1 = DAT_BuildingsState::instance.buildings[iVar7].currentEmployeeCount;
            iVar5 = (int)sVar1;
            if (0 < iVar5) {
                piVar6 = DAT_BuildingsState::instance.buildings[iVar7].workerUID;
                piVar8 = DAT_UnitsState::instance.units[iVar4].manningEngineerUIDRef;
                psVar2 = DAT_UnitsState::instance.units[iVar4].manningEngineerRef;
                psVar3 = DAT_BuildingsState::instance.buildings[iVar7].workerID;
                do {
                    *psVar2 = *psVar3;
                    *piVar8 = *piVar6;
                    psVar3 = psVar3 + 1;
                    psVar2 = psVar2 + 1;
                    piVar6 = piVar6 + 1;
                    piVar8 = piVar8 + 1;
                    iVar5 = iVar5 + -1;
                    iVar7 = DAT_CurrentBuildingID::instance;
                } while (iVar5);
            }
            bVar9 = DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
            DAT_UnitsState::instance.units[iVar4].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                = sVar1;
            if ((bVar9) && (iVar7 == DAT_BuildingsState::instance.menuSelectedBuildingID)) {
                DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 2;
                DAT_BuildingsState::instance.unitID = iVar4;
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                iVar7);
        }
    }

}
}
