#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::Behavior::UnitStanceEnum;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052A7D0
        void TribesState::updateTribeCombatStanceBehavior(int tribeID)
        {
            short* psVar1;
            UnitTypeShort UVar2;
            int _unitID;
            BOOLEnum BVar3;
            int iVar4;
            int _targetUnitID;
            int iVar5;
            uint x1;
            uint y1;
            int local_c;
            int _buildingID;
            int _buildingIndex;
            short _buildingIndex_2;
            UnitInstructionType _unitInstructionType;
            _targetUnitID = (int)this->tribes[tribeID].selectionTargetUnitID;
            _buildingIndex_2 = this->tribes[tribeID].someUnitID;
            if (!_buildingIndex_2) {
                if (this->tribes[tribeID].unitStance == Map::Units::Behavior::USE_AGGRESSIVE) {
                    local_c = 0;
                    do {
                        iVar5 = ((this->tribes[tribeID].someUnitArrayIndex - local_c) + 10) % 10;
                        _unitID = (int)this->tribes[tribeID].someUnitArray[iVar5];
                        if (_unitID) {
                            if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[_unitID].dying == 0
                                && DAT_UnitsState::instance.units[_unitID].uid
                                    == this->tribes[tribeID].someUnitUIDArray[iVar5]
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_UnitsState::instance.units[_targetUnitID].owner]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                                && DAT_TileMapState::instance
                                        .PathConnectionLayer[DAT_UnitsState::instance.units[_targetUnitID].tile]
                                    == DAT_TileMapState::instance
                                        .PathConnectionLayer[DAT_UnitsState::instance.units[_unitID].tile]) {
                                iVar5 = (int)DAT_UnitsState::instance.units[_targetUnitID].microXPosition
                                    - (int)DAT_UnitsState::instance.units[_unitID].microXPosition;
                                iVar4 = (int)DAT_UnitsState::instance.units[_targetUnitID].microYPosition
                                    - (int)DAT_UnitsState::instance.units[_unitID].microYPosition;
                                if (iVar5 * iVar5 + iVar4 * iVar4 < 250000) {
                                    if ((this->tribes[tribeID].unknownAttackRelatedUpdateCounter == 0)
                                        && (this->tribes[tribeID].aggressiveStanceCounter == 0x3b)) {
                                        iVar5 = 0;
                                        if (this->tribes[tribeID].size < 1)
                                            goto LAB_0052aa55;
                                        goto LAB_0052a9f2;
                                    }
                                    break;
                                }
                            } else {
                                this->tribes[tribeID].someUnitArray[iVar5] = 0;
                            }
                        }
                        local_c = local_c + 1;
                    } while (local_c < 10);
                }
            } else {
                iVar5 = (int)_buildingIndex_2;
                if (DAT_UnitsState::instance.units[iVar5].uid == this->tribes[tribeID].someUnitUID) {
                    if ((int)DAT_UnitsState::instance.units[iVar5].destinationX_2Unk
                            + DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_UnitsState::instance.units[iVar5].destinationY_2Unk]
                                .addXgetTile
                        == this->tribes[tribeID].someTile2) {
                        _buildingIndex_2 = this->tribes[tribeID].field168_0x2be;
                        if (_buildingIndex_2) {
                            this->tribes[tribeID].field168_0x2be = _buildingIndex_2 + -1;
                            goto LAB_0052aa77;
                        }
                        if (DAT_UnitsState::instance.units[iVar5].tile == this->tribes[tribeID].someTile)
                            goto LAB_0052aa77;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                        tribeID, Map::Units::UIT_UNIT_ATTACK_UNIT, iVar5, this->tribes[tribeID].someUnitUID, 1);
                } else {
                    this->tribes[tribeID].someUnitID = 0;
                }
            }
            goto LAB_0052aa77;
        LAB_0052a9f2:
            do {
                iVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, iVar5);
                iVar5 = iVar5 + 1;
                if (DAT_UnitsState::instance.units[iVar4].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[iVar4].dying == 0
                    && DAT_UnitsState::instance.units[iVar4].state.generic != Map::Units::States::US_MELEE_ATTACK) {
                    switch (DAT_UnitsState::instance.units[iVar4].unitType) {
                    case Map::Units::UT_TUNNELER:
                    case Map::Units::UT_E_SPEAR:
                    case Map::Units::UT_E_PIKE:
                    case Map::Units::UT_E_MACE:
                    case Map::Units::UT_E_SWORD:
                    case Map::Units::UT_E_KNIGHT:
                    case Map::Units::UT_E_MONK:
                    case Map::Units::UT_S_BATTERINGRAM:
                        if (DAT_UnitsState::instance.units[iVar4].SA == 0)
                            goto LAB_0052aa77;
                    }
                }
            } while (iVar5 < this->tribes[tribeID].size);
        LAB_0052aa55:
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                tribeID, ((UnitInstructionType)0x20), _unitID, DAT_UnitsState::instance.units[_unitID].uid, 0);
        LAB_0052aa77:
            psVar1 = (short*)&this->tribes[tribeID].unknownAttackRelatedUpdateCounter;
            *psVar1 = *psVar1 + 1;
            if (0x32 < this->tribes[tribeID].unknownAttackRelatedUpdateCounter) {
                if (this->tribes[tribeID].isRallyingUnk == 0) {
                    if (this->tribes[tribeID].unitStance == Map::Units::Behavior::USE_AGGRESSIVE) {
                        psVar1 = &this->tribes[tribeID].aggressiveStanceCounter;
                        *psVar1 = *psVar1 + 1;
                        if (this->tribes[tribeID].aggressiveStanceCounter < 0x3c) {}
                        _buildingIndex_2 = this->tribes[tribeID].size;
                        this->tribes[tribeID].aggressiveStanceCounter = 0;
                        if (0 < _buildingIndex_2) {
                            iVar5 = 0;
                            do {
                                iVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                    tribeID, iVar5);
                                iVar5 = iVar5 + 1;
                                if (DAT_UnitsState::instance.units[iVar4].logicalState == Map::Units::ULS_NORMAL
                                    && DAT_UnitsState::instance.units[iVar4].dying == 0
                                    && DAT_UnitsState::instance.units[iVar4].state.generic
                                        != Map::Units::States::US_MELEE_ATTACK) {
                                    switch (DAT_UnitsState::instance.units[iVar4].unitType) {
                                    case Map::Units::UT_TUNNELER:
                                    case Map::Units::UT_E_SPEAR:
                                    case Map::Units::UT_E_PIKE:
                                    case Map::Units::UT_E_MACE:
                                    case Map::Units::UT_E_SWORD:
                                    case Map::Units::UT_E_KNIGHT:
                                    case Map::Units::UT_E_MONK:
                                    case Map::Units::UT_S_BATTERINGRAM:
                                    case Map::Units::UT_A_SLAVE:
                                    case Map::Units::UT_A_ASSASSIN:
                                    case Map::Units::UT_A_SWORDSMAN:
                                        if (DAT_UnitsState::instance.units[iVar4].SA == 0)
                                            goto LAB_0052ac8d;
                                    }
                                }
                            } while (iVar5 < this->tribes[tribeID].size);
                        }
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::aggressiveStanceTargetBuildingAtRange,
                            DAT_PathFindingState::ptr)(_targetUnitID, (int)((int)(15)));
                        if (DAT_PathFindingState::instance.ALG_ResultTile) {
                            _buildingIndex_2 = DAT_TileMapState::instance
                                                   .BuildingLayer[DAT_PathFindingState::instance.ALG_ResultTile];
                            if (!_buildingIndex_2) {
                                _buildingID = 0;
                                _unitInstructionType = ((UnitInstructionType)0x25);
                                _buildingIndex = DAT_PathFindingState::instance.ALG_ResultTile;
                            } else {
                                _buildingID = DAT_BuildingsState::instance.buildings[_buildingIndex_2].uid;
                                _unitInstructionType = ((UnitInstructionType)0x26);
                                _buildingIndex = (int)_buildingIndex_2;
                            }
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                                tribeID, _unitInstructionType, _buildingIndex, _buildingID, 0);
                        }
                    }
                } else {
                    BVar3 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::allUnitsReachedTheirDestination, this)(
                        tribeID);
                    if (!BVar3) {}
                    _buildingIndex_2 = this->tribes[tribeID].rallyPointCount;
                    iVar5 = this->tribes[tribeID].currentRallyPointIndex + 1;
                    this->tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    if (_buildingIndex_2 <= iVar5) {
                        if (this->tribes[tribeID].isRallyingUnk == -1) {
                            this->tribes[tribeID].currentRallyPointIndex = 0;
                            this->tribes[tribeID].isRallyingUnk = 0;
                        }
                        iVar5 = 0;
                    }
                    if (this->tribes[tribeID].isRallyingUnk != 0) {
                        x1 = (uint)this->tribes[tribeID].rallyPointArray[iVar5][0];
                        y1 = (uint)this->tribes[tribeID].rallyPointArray[iVar5][1];
                        this->tribes[tribeID].currentRallyPointIndex = (short)iVar5;
                        UVar2 = DAT_UnitsState::instance.units[_targetUnitID].unitType;
                        if (UVar2 == Map::Units::UT_E_ARCHER || UVar2 == Map::Units::UT_E_XBOW
                            || UVar2 == Map::Units::UT_A_ARCHER || UVar2 == Map::Units::UT_A_SLINGER
                            || UVar2 == Map::Units::UT_A_FIRETHROWER) {
                            if (0x1b0 < DAT_UnitsState::instance.units[_targetUnitID].closestEnemyMicroDistance) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                                    tribeID, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
                            }
                        } else if (UVar2 == Map::Units::UT_A_HARCHER) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                                tribeID, x1, y1, 0, 0);
                        } else if ((0x60 < DAT_UnitsState::instance.units[_targetUnitID].closestEnemyMicroDistance)
                            || (this->tribes[tribeID].unitStance != Map::Units::Behavior::USE_AGGRESSIVE)) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                                tribeID, x1, y1, 0, 0);
                        }
                    }
                }
            LAB_0052ac8d:
                if (this->tribes[tribeID].pendingScatterMove != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::moveTribeToIndexedNearbyTile, this)(tribeID);
                    this->tribes[tribeID].pendingScatterMove = 0;
                }
            }
        }

    }
}
}
