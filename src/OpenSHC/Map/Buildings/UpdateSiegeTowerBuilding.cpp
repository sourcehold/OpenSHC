#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x0041FC90
    void Buildings::UpdateSiegeTowerBuilding()
    {
        byte bVar1;
        short sVar2;
        ushort uVar3;
        ushort uVar4;
        short sVar5;
        int iVar6;
        int iVar7;
        short* psVar8;
        short* psVar9;
        int iVar10;
        int iVar11;
        int playerID;
        int* piVar12;
        int _unitID;
        uint uVar13;
        int* piVar14;
        bool bVar15;
        int local_c;
        int _buildingID;
        iVar11 = DAT_CurrentBuildingID::instance;
        playerID = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        iVar10 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave;
        if (((0 < iVar10) && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY))
            && ((char)DAT_TroopValueState::instance.attackInfo.nof_tribes[iVar10] <= '\0')) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = Map::Buildings::BLS_REMOVE;
        }
        if (DAT_BuildingsState::instance.buildings[iVar11].oldVisualActiveState == -1) {
            iVar10 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            DAT_BuildingsState::instance.buildings[iVar11].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[iVar11].playerColorUnk
                = (int)DAT_BuildingsState::instance.buildings[iVar11].owner;
            DAT_BuildingsState::instance.buildings[iVar11].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[iVar11].displayOwnerFlag = 0;
            if (iVar10 == -1) {
                iVar10 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(playerID);
                iVar11 = DAT_CurrentBuildingID::instance;
                if (!iVar10) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
                }
            } else {
                DAT_BuildingsState::instance.buildings[iVar11].animationFrame = 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar11);
            iVar11 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        piVar12 = &DAT_BuildingsState::instance.buildings[iVar11].buildingProgress;
        *piVar12 = *piVar12 + (int)DAT_BuildingsState::instance.buildings[iVar11].currentEmployeeCount;
        if (0x500 < DAT_BuildingsState::instance.buildings[iVar11].buildingProgress) {
            iVar10 = (int)DAT_BuildingsState::instance.buildings[iVar11].owner;
            iVar10 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(iVar10,
                iVar10, (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar11].x * 8)),
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar11].y * 8)),
                (int)((int)(DAT_BuildingsState::instance.buildings[iVar11].terrainHeightUnk)),
                Map::Units::UT_S_TOWER);
            if (!iVar10) {
                piVar12 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
                *piVar12 = *piVar12
                    - (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            }
            iVar11 = 4;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount == 4) {
                psVar8 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                do {
                    sVar2 = *psVar8;
                    psVar8 = psVar8 + 1;
                    iVar11 = iVar11 + -1;
                    DAT_UnitsState::instance.units[sVar2].state.generic = Map::Units::States::US_AIM_WEAPONUnk;
                } while (iVar11);
            } else {
                uVar13 = (int)SEC_RNG::instance.currentNumber2 & 0x8000000f;
                if ((int)uVar13 < 0) {
                    uVar13 = (uVar13 - 1 | 0xfffffff0) + 1;
                }
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                local_c = 0;
                iVar11 = DAT_CurrentBuildingID::instance;
                if (0 < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount) {
                    do {
                        _unitID = (int)DAT_BuildingsState::instance.buildings[iVar11].workerID[local_c];
                        sVar2 = DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[uVar13][0];
                        uVar3 = DAT_BuildingsState::instance.buildings[iVar11].x;
                        uVar4 = DAT_BuildingsState::instance.buildings[iVar11].y;
                        sVar5 = DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[uVar13][1];
                        uVar13 = uVar13 + 1 & 0x8000000f;
                        DAT_UnitsState::instance.units[_unitID].state.generic
                            = Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[_unitID].disappearFadeAlphaCountdown = 0x20;
                        DAT_UnitsState::instance.units[_unitID].engineerManningSiegeStateRef_checkType = 0xfe;
                        DAT_UnitsState::instance.units[_unitID].cachedState
                            = Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        if ((int)uVar13 < 0) {
                            uVar13 = (uVar13 - 1 | 0xfffffff0) + 1;
                        }
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                            DAT_PathFindingState::ptr)(
                            -1, (int)((int)(sVar2 + (short)uVar3)), (int)((int)(sVar5 + (short)uVar4)));
                        iVar7 = DAT_PathFindingState::instance.ALG_ResultTile;
                        iVar6 = DAT_PathFindingState::instance.ALG_ResultY;
                        iVar11 = DAT_PathFindingState::instance.ALG_ResultX;
                        bVar1 = DAT_TileMapState::instance.HeightLayer[DAT_PathFindingState::instance.ALG_ResultTile];
                        DAT_UnitsState::instance.units[_unitID].tile = DAT_PathFindingState::instance.ALG_ResultTile;
                        DAT_UnitsState::instance.units[_unitID].nextTileUnk = iVar7;
                        sVar2 = (short)iVar11;
                        DAT_UnitsState::instance.units[_unitID].x = sVar2;
                        DAT_UnitsState::instance.units[_unitID].mimicCurrentXPosition = sVar2;
                        DAT_UnitsState::instance.units[_unitID].terrainOrClimbHeight = (ushort)bVar1;
                        sVar5 = (short)iVar6;
                        DAT_UnitsState::instance.units[_unitID].y = sVar5;
                        DAT_UnitsState::instance.units[_unitID].mimicCurrentYPosition = sVar5;
                        DAT_UnitsState::instance.units[_unitID].microXPosition = sVar2 * 8 + 4;
                        DAT_UnitsState::instance.units[_unitID].microYPosition = sVar5 * 8 + 4;
                        DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan = 0;
                        DAT_UnitsState::instance.units[_unitID].movementCooldown = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::updateMicroPosition, DAT_UnitsState::ptr)(_unitID);
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(_unitID);
                        iVar11 = DAT_CurrentBuildingID::instance;
                        DAT_UnitsState::instance.units[_unitID].targetingType
                            = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                        DAT_UnitsState::instance.units[_unitID].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            = (short)iVar10;
                        local_c = local_c + 1;
                    } while (local_c < DAT_BuildingsState::instance.buildings[iVar11].currentEmployeeCount);
                }
                DAT_BuildingsState::instance.buildings[iVar11].currentEmployeeCount = 0;
            }
            MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[iVar10].x,
                (int)((int)(DAT_UnitsState::instance.units[iVar10].y)),
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.xEntry,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.yEntry);
            iVar11 = DAT_CurrentBuildingID::instance;
            sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[sVar2] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[sVar2] == 0)) {
                DAT_UnitsState::instance.units[iVar10].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            } else {
                DAT_UnitsState::instance.units[iVar10].facingDirection = 0;
            }
            iVar6 = DAT_BuildingsState::instance.buildings[iVar11].attackWave;
            DAT_UnitsState::instance.units[iVar10].unknownSiegeTentRelated02
                = (char)DAT_BuildingsState::instance.buildings[iVar11].unknownSiegeTentRelated01 + 1;
            DAT_UnitsState::instance.units[iVar10].logicalState = ((UnitLogicState)5);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
                iVar10, iVar6, ((AITribeType)0x14), (undefined4)((int)(playerID)));
            sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            if (0 < sVar2) {
                local_c = (int)sVar2;
                piVar12 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID;
                piVar14 = DAT_UnitsState::instance.units[iVar10].manningEngineerUIDRef;
                psVar8 = DAT_UnitsState::instance.units[iVar10].manningEngineerRef;
                psVar9 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                do {
                    *psVar8 = *psVar9;
                    *piVar14 = *piVar12;
                    psVar9 = psVar9 + 1;
                    psVar8 = psVar8 + 1;
                    piVar12 = piVar12 + 1;
                    piVar14 = piVar14 + 1;
                    local_c = local_c + -1;
                } while (local_c);
            }
            iVar11 = DAT_CurrentBuildingID::instance;
            bVar15 = DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
            DAT_UnitsState::instance.units[iVar10]
                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = sVar2;
            if ((bVar15) && (iVar11 == DAT_BuildingsState::instance.menuSelectedBuildingID)) {
                DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 2;
                DAT_BuildingsState::instance.unitID = iVar10;
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                iVar11);
        }
    }

}
}
