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

    // FUNCTION: STRONGHOLDCRUSADER 0x004205B0
    void Buildings::UpdateShieldBuilding()
    {
        byte bVar1;
        short sVar2;
        ushort uVar3;
        ushort uVar4;
        short sVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        short* psVar9;
        short* psVar10;
        int iVar11;
        int iVar12;
        int playerID;
        int* piVar13;
        uint uVar14;
        int* piVar15;
        bool bVar16;
        int local_c;
        iVar8 = DAT_CurrentBuildingID::instance;
        playerID = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        iVar12 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].attackWave;
        if (((0 < iVar12) && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY))
            && ((char)DAT_TroopValueState::instance.attackInfo.nof_tribes[iVar12] <= '\0')) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = Map::Buildings::BLS_REMOVE;
        }
        iVar12 = 1;
        if (DAT_BuildingsState::instance.buildings[iVar8].oldVisualActiveState == -1) {
            iVar11 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID];
            DAT_BuildingsState::instance.buildings[iVar8].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[iVar8].playerColorUnk
                = (int)DAT_BuildingsState::instance.buildings[iVar8].owner;
            DAT_BuildingsState::instance.buildings[iVar8].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[iVar8].displayOwnerFlag = 0;
            if (iVar11 == -1) {
                iVar11 = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                    DAT_GameSynchronyState::ptr)(playerID);
                iVar8 = DAT_CurrentBuildingID::instance;
                if (!iVar11) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 3;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 2;
                }
            } else {
                DAT_BuildingsState::instance.buildings[iVar8].animationFrame = 1;
            }
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar8);
            iVar8 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        piVar13 = &DAT_BuildingsState::instance.buildings[iVar8].buildingProgress;
        *piVar13 = *piVar13 + (int)DAT_BuildingsState::instance.buildings[iVar8].currentEmployeeCount;
        if (0x78 < DAT_BuildingsState::instance.buildings[iVar8].buildingProgress) {
            iVar11 = (int)DAT_BuildingsState::instance.buildings[iVar8].owner;
            iVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(iVar11,
                iVar11, (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar8].x * 8)),
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar8].y * 8)),
                (int)((int)(DAT_BuildingsState::instance.buildings[iVar8].terrainHeightUnk)),
                Map::Units::UT_S_SHIELD);
            if (!iVar8) {
                piVar13 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress;
                *piVar13 = *piVar13
                    - (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount == 1) {
                psVar9 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                do {
                    sVar2 = *psVar9;
                    psVar9 = psVar9 + 1;
                    iVar12 = iVar12 + -1;
                    DAT_UnitsState::instance.units[sVar2].state.generic = Map::Units::States::US_AIM_WEAPONUnk;
                } while (iVar12);
            } else {
                uVar14 = (int)SEC_RNG::instance.currentNumber2 & 0x8000000f;
                if ((int)uVar14 < 0) {
                    uVar14 = (uVar14 - 1 | 0xfffffff0) + 1;
                }
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                local_c = 0;
                iVar12 = DAT_CurrentBuildingID::instance;
                if (0 < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount) {
                    do {
                        iVar11 = (int)DAT_BuildingsState::instance.buildings[iVar12].workerID[local_c];
                        sVar2 = DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[uVar14][0];
                        uVar3 = DAT_BuildingsState::instance.buildings[iVar12].x;
                        uVar4 = DAT_BuildingsState::instance.buildings[iVar12].y;
                        sVar5 = DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[uVar14][1];
                        uVar14 = uVar14 + 1 & 0x8000000f;
                        DAT_UnitsState::instance.units[iVar11].state.generic
                            = Map::Units::States::US_JESTER_ROAM_TO;
                        DAT_UnitsState::instance.units[iVar11].disappearFadeAlphaCountdown = 0x20;
                        DAT_UnitsState::instance.units[iVar11].engineerManningSiegeStateRef_checkType = 0xfe;
                        DAT_UnitsState::instance.units[iVar11].cachedState
                            = Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        if ((int)uVar14 < 0) {
                            uVar14 = (uVar14 - 1 | 0xfffffff0) + 1;
                        }
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                            DAT_PathFindingState::ptr)(
                            -1, (int)((int)(sVar2 + (short)uVar3)), (int)((int)(sVar5 + (short)uVar4)));
                        iVar7 = DAT_PathFindingState::instance.ALG_ResultTile;
                        iVar6 = DAT_PathFindingState::instance.ALG_ResultY;
                        iVar12 = DAT_PathFindingState::instance.ALG_ResultX;
                        bVar1 = DAT_TileMapState::instance.HeightLayer[DAT_PathFindingState::instance.ALG_ResultTile];
                        DAT_UnitsState::instance.units[iVar11].tile = DAT_PathFindingState::instance.ALG_ResultTile;
                        DAT_UnitsState::instance.units[iVar11].nextTileUnk = iVar7;
                        sVar2 = (short)iVar12;
                        DAT_UnitsState::instance.units[iVar11].x = sVar2;
                        DAT_UnitsState::instance.units[iVar11].mimicCurrentXPosition = sVar2;
                        DAT_UnitsState::instance.units[iVar11].terrainOrClimbHeight = (ushort)bVar1;
                        sVar5 = (short)iVar6;
                        DAT_UnitsState::instance.units[iVar11].y = sVar5;
                        DAT_UnitsState::instance.units[iVar11].mimicCurrentYPosition = sVar5;
                        DAT_UnitsState::instance.units[iVar11].microXPosition = sVar2 * 8 + 4;
                        DAT_UnitsState::instance.units[iVar11].microYPosition = sVar5 * 8 + 4;
                        DAT_UnitsState::instance.units[iVar11].totalSizeOfPathPlan = 0;
                        DAT_UnitsState::instance.units[iVar11].movementCooldown = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::updateMicroPosition, DAT_UnitsState::ptr)(iVar11);
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(iVar11);
                        iVar12 = DAT_CurrentBuildingID::instance;
                        DAT_UnitsState::instance.units[iVar11].targetingType
                            = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                        DAT_UnitsState::instance.units[iVar11].targetedUnitID__OR__engineerMannedSiegeEngineRef
                            = (short)iVar8;
                        local_c = local_c + 1;
                    } while (local_c < DAT_BuildingsState::instance.buildings[iVar12].currentEmployeeCount);
                }
                DAT_BuildingsState::instance.buildings[iVar12].currentEmployeeCount = 0;
            }
            MACRO_CALL_MEMBER(
                Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[iVar8].x,
                (int)((int)(DAT_UnitsState::instance.units[iVar8].y)),
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.xEntry,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .campground.yEntry);
            iVar12 = DAT_CurrentBuildingID::instance;
            sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[sVar2] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[sVar2] == 0)) {
                DAT_UnitsState::instance.units[iVar8].facingDirection
                    = (short)DAT_DirectionAlgorithmState::instance.orientation;
            } else {
                DAT_UnitsState::instance.units[iVar8].facingDirection = 0;
            }
            iVar11 = DAT_BuildingsState::instance.buildings[iVar12].attackWave;
            DAT_UnitsState::instance.units[iVar8].unknownSiegeTentRelated02
                = (char)DAT_BuildingsState::instance.buildings[iVar12].unknownSiegeTentRelated01 + 1;
            DAT_UnitsState::instance.units[iVar8].logicalState = ((UnitLogicState)5);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::addUnitToNewTribe, DAT_TroopValueState::ptr)(
                iVar8, iVar11, ((AITribeType)0x15), (undefined4)((int)(playerID)));
            sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount;
            if (0 < sVar2) {
                local_c = (int)sVar2;
                piVar13 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID;
                piVar15 = DAT_UnitsState::instance.units[iVar8].manningEngineerUIDRef;
                psVar9 = DAT_UnitsState::instance.units[iVar8].manningEngineerRef;
                psVar10 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                do {
                    *psVar9 = *psVar10;
                    *piVar15 = *piVar13;
                    psVar10 = psVar10 + 1;
                    psVar9 = psVar9 + 1;
                    piVar13 = piVar13 + 1;
                    piVar15 = piVar15 + 1;
                    local_c = local_c + -1;
                } while (local_c);
            }
            iVar12 = DAT_CurrentBuildingID::instance;
            bVar16 = DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
            DAT_UnitsState::instance.units[iVar8].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                = sVar2;
            if ((bVar16) && (iVar12 == DAT_BuildingsState::instance.menuSelectedBuildingID)) {
                DAT_BuildingsState::instance.siegeEngineCreationRelated01 = 2;
                DAT_BuildingsState::instance.unitID = iVar8;
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                iVar12);
        }
    }

}
}
