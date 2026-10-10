#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathHelper12.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;
        using Game::GameMode2;
        using Map::Buildings::BuildingType;
        using Map::Navigation::PathHelper12;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          gynt: unitID and x and y and id are the target of the instruction   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00527C80
        undefined4 TribesState::giveTribeAnInstruction(
            int tribeID, UnitInstructionType unitInstructionType, int id, int unitUID, int param_5)
        {
            short* psVar1;
            byte bVar2;
            UnitStateShort UVar3;
            UnitTypeShort UVar4;
            bool bVar5;
            Unit* pUVar6;
            char cVar7;
            short sVar8;
            int _unitID_0x03;
            int _unitID_0x04;
            int _targetUnitID;
            uint _x_528565;
            BOOL _isAllAssassins_528565;
            UnitInstructionType UVar10;
            int iVar11;
            int _unitID_0x05_0x16;
            int iVar12;
            int _unitID;
            short sVar9;
            uint uVar13;
            int iVar14;
            int iVar15;
            int _laddermanID;
            undefined3 extraout_var;
            int _unitID_0x1e;
            BOOLEnum BVar16;
            uint _freeTileX;
            uint uVar17;
            uint x;
            int _unitID_0x11;
            short _param_3_id_x_tile_buildingID_copy;
            int _unitSelectionIndex;
            int* piVar18;
            uint y;
            uint uVar19;
            bool _gamemodeSiegeThat;
            int _unitTribeIndex;
            int _ramOrHorse;
            uint local_8;
            dword _param_4_unitUID_Y_copy;
            int _tile1_528565;
            short _y_528565;
            int _param_1_tribeID;
            int _paramUnitID;
            int _paramUnitUID;
            short _tribeSize;
            int _freeTile;
            uint _defensiveTile1;
            int _defensiveTile2;
            short _freeTileY;
            short _y;
            short _x;
            uint _id;
            int _param_3_id_x_tile_buildingID;
            int _param_4_unitUID_Y;
            ushort _targetArea;
            _param_4_unitUID_Y = unitUID;
            iVar11 = id;
            _param_1_tribeID = tribeID;
            _tribeSize = this->tribes[tribeID].size;
            _param_4_unitUID_Y_copy = unitUID;
            _ramOrHorse = 0;
            local_8 = 0;
            bVar5 = false;
            this->tribes[tribeID].someUnitID = 0;
            this->tribes[tribeID].containsRabbit = 0;
            _param_3_id_x_tile_buildingID_copy = (short)id;
            uVar13 = id;
            switch (unitInstructionType) {
            case Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk:
                _unitSelectionIndex = 0;
                if (0 < _tribeSize) {
                    do {
                        _unitID_0x03 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            _param_1_tribeID, _unitSelectionIndex);
                        _unitSelectionIndex = _unitSelectionIndex + 1;
                        if ((DAT_UnitsState::instance.units[_unitID_0x03].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID_0x03].dying == 0)) {
                            DAT_UnitsState::instance.units[_unitID_0x03].field253_0x3c5 = 3;
                            DAT_UnitsState::instance.units[_unitID_0x03].targetingType
                                = Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                            DAT_UnitsState::instance.units[_unitID_0x03].field243_0x3b0 = 0;
                        }
                    } while (_unitSelectionIndex < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case Map::Units::UIT_UNIT_ATTACK_UNIT:
                /*
                  unit attack target
                 */
                this->tribes[tribeID].isRallyingUnk = 0;
                pUVar6 = DAT_UnitsState::instance.units + id;
                _unitTribeIndex = 0;
                /*
                  repurposed parameter: counts amount of melee units
                 */
                id = 0;
                if (pUVar6->uid != unitUID) {
                    return (undefined4)(0);
                }
                if (0 < _tribeSize) {
                    do {
                        _unitID_0x04 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[_unitID_0x04].logicalState != Map::Units::ULS_NORMAL
                            || DAT_UnitsState::instance.units[_unitID_0x04].dying != 0
                            || DAT_UnitsState::instance.units[_unitID_0x04].field303_0x413 != 0)
                            continue;
                        DAT_UnitsState::instance.units[_unitID_0x04]._someX_2 = 0;
                        DAT_UnitsState::instance.units[_unitID_0x04]._someY_2 = 0;
                        switch (DAT_UnitsState::instance.units[_unitID_0x04].unitType) {
                        case Map::Units::UT_TUNNELER:
                        case Map::Units::UT_E_SPEAR:
                        case Map::Units::UT_E_PIKE:
                        case Map::Units::UT_E_MACE:
                        case Map::Units::UT_E_SWORD:
                        case Map::Units::UT_E_KNIGHT:
                        case Map::Units::UT_E_MONK:
                        case Map::Units::UT_LORD:
                        case Map::Units::UT_A_SLAVE:
                        case Map::Units::UT_A_ASSASSIN:
                        case Map::Units::UT_A_SWORDSMAN:
                            /*
                              melee units
                             */
                            if (DAT_UnitsState::instance.units[iVar11].unitType != Map::Units::UT_ANTELOPESHDEER
                                && (param_5 != 1
                                    || (DAT_UnitsState::instance.units[iVar11].state.generic
                                        != Map::Units::States::US_MELEE_ATTACK))) {
                                id = id + 1;
                            }
                            break;
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_SLINGER:
                        case Map::Units::UT_A_HARCHER:
                        case Map::Units::UT_A_FIRETHROWER:
                            /*
                              ranged units
                             */
                            if (DAT_UnitsState::instance.units[_unitID_0x04].state.generic == (UnitState)0x69) {
                                DAT_UnitsState::instance.units[_unitID_0x04].state.generic
                                    = Map::Units::States::US_MOVE_TO_DESTINATION;
                            }
                            DAT_UnitsState::instance.units[_unitID_0x04]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID;
                            DAT_UnitsState::instance.units[_unitID_0x04].targetUID = unitUID;
                            DAT_UnitsState::instance.units[_unitID_0x04].targetingType
                                = Map::Units::UIT_UNIT_ATTACK_UNIT;
                            DAT_UnitsState::instance.units[_unitID_0x04]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[_unitID_0x04].shootTargetedUnit
                                = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[_unitID_0x04].field283_0x3f8 = 0;
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                DAT_UnitsState::ptr)(_unitID_0x04);
                            goto LAB_00527ee1;
                        case Map::Units::UT_S_CATAPULT:
                        case Map::Units::UT_S_TREBUCHET:
                            DAT_UnitsState::instance.units[_unitID_0x04].field253_0x3c5 = 5;
                            DAT_UnitsState::instance.units[_unitID_0x04].targetingType = Map::Units::UIT_ATTACK_LAND;
                            DAT_UnitsState::instance.units[_unitID_0x04].attackAtTileX
                                = DAT_UnitsState::instance.units[iVar11].x;
                            DAT_UnitsState::instance.units[_unitID_0x04].attackAtTileY
                                = DAT_UnitsState::instance.units[iVar11].y;
                            DAT_UnitsState::instance.units[_unitID_0x04].unkAttackRelated = 0xb;
                            DAT_UnitsState::instance.units[_unitID_0x04].shootBeforeStop = 10;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                        case Map::Units::UT_S_BALLISTA:
                        case Map::Units::UT_S_FBALLISTA:
                            DAT_UnitsState::instance.units[_unitID_0x04].targetingType
                                = Map::Units::UIT_UNIT_ATTACK_UNIT;
                            DAT_UnitsState::instance.units[_unitID_0x04]
                                .targetedUnitID__OR__engineerMannedSiegeEngineRef = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[_unitID_0x04]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID;
                            DAT_UnitsState::instance.units[_unitID_0x04].field283_0x3f8 = 0;
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                DAT_UnitsState::ptr)(_unitID_0x04);
                            DAT_UnitsState::instance.units[_unitID_0x04].shootBeforeStop = 10;
                        LAB_00527ee1:
                            if (DAT_UnitsState::instance.units[iVar11].unitType == Map::Units::UT_RABBIT) {
                                this->tribes[_param_1_tribeID].containsRabbit = 1;
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                    if (id | x | id != 0) {
                        /*
                          if there are melee units in the selection
                         */
                        _targetUnitID = (int)this->tribes[_param_1_tribeID].selectionTargetUnitID;
                        local_8 = (uint)DAT_UnitsState::instance.units[_targetUnitID].x;
                        unitInstructionType = (UnitInstructionType)DAT_UnitsState::instance.units[_targetUnitID].y;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::predictUnitInterceptPosition, this)(
                            _targetUnitID, iVar11, (int*)&local_8, (int*)&unitInstructionType);
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathPlanningForTribe,
                            DAT_PathFindingState::ptr)(tribeID, (undefined4)((int)(iVar11)), local_8,
                            (uint)(unitInstructionType), id,
                            (dword)((int)((short)DAT_TileMapState::instance
                                    .PathConnectionLayer[DAT_UnitsState::instance.units[_targetUnitID].tile])),
                            (int)(DAT_UnitsState::instance.units[_targetUnitID].owner));
                        this->tribes[_param_1_tribeID].someUnitID = _param_3_id_x_tile_buildingID_copy;
                        this->tribes[_param_1_tribeID].someUnitUID = unitUID;
                        this->tribes[_param_1_tribeID].someTile = DAT_UnitsState::instance.units[iVar11].tile;
                        iVar12 = 0;
                        sVar9 = this->tribes[_param_1_tribeID].size;
                        this->tribes[_param_1_tribeID].someTile2
                            = (int)DAT_UnitsState::instance.units[iVar11].destinationX_2Unk
                            + DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_UnitsState::instance.units[iVar11].destinationY_2Unk]
                                  .addXgetTile;
                        unitInstructionType = ((UnitInstructionType)0);
                        if (0 < sVar9) {
                            id = 0x12d5c6c;
                            do {
                                iVar11 = MACRO_CALL_MEMBER(
                                    Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, iVar12);
                                iVar12 = iVar12 + 1;
                                if (DAT_UnitsState::instance.units[iVar11].logicalState == Map::Units::ULS_NORMAL
                                    && DAT_UnitsState::instance.units[iVar11].dying == 0
                                    && DAT_UnitsState::instance.units[iVar11].field303_0x413 == 0) {
                                    UVar4 = DAT_UnitsState::instance.units[iVar11].unitType;
                                    switch (UVar4) {
                                    case Map::Units::UT_TUNNELER:
                                    case Map::Units::UT_E_SPEAR:
                                    case Map::Units::UT_E_PIKE:
                                    case Map::Units::UT_E_MACE:
                                    case Map::Units::UT_E_SWORD:
                                    case Map::Units::UT_E_KNIGHT:
                                    case Map::Units::UT_E_MONK:
                                    case Map::Units::UT_LORD:
                                    case Map::Units::UT_A_SLAVE:
                                    case Map::Units::UT_A_ASSASSIN:
                                    case Map::Units::UT_A_SWORDSMAN:
                                        if (((param_5 != 1)
                                                || (DAT_UnitsState::instance.units[iVar11].state.generic
                                                    != Map::Units::States::US_MELEE_ATTACK))
                                            && (iVar14 = *(int*)id, iVar14 != 0)) {
                                            sVar9 = DAT_ViewportRenderState::instance
                                                        .tileTranslationMatrix_YComponent[iVar14];
                                            uVar13 = iVar14
                                                - DAT_ViewportRenderState::instance.translationMatrix[sVar9]
                                                      .addXgetTile;
                                            if (*(int*)(id + 4) == 0) {
                                                DAT_UnitsState::instance.units[iVar11].targetingType
                                                    = ((UnitInstructionType)0);
                                                if (UVar4 == Map::Units::UT_LORD)
                                                    break;
                                            } else {
                                                DAT_UnitsState::instance.units[iVar11].targetingType
                                                    = Map::Units::UIT_UNIT_ATTACK_UNIT;
                                                DAT_UnitsState::instance.units[iVar11]
                                                    .targetedUnitID__OR__engineerMannedSiegeEngineRef
                                                    = _param_3_id_x_tile_buildingID_copy;
                                                DAT_UnitsState::instance.units[iVar11]
                                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                                    = unitUID;
                                            }
                                            UVar3 = DAT_UnitsState::instance.units[iVar11].state.generic;
                                            DAT_UnitsState::instance.units[iVar11].plannedDestinationX = (short)uVar13;
                                            DAT_UnitsState::instance.units[iVar11].plannedDestinationY = sVar9;
                                            DAT_UnitsState::instance.units[iVar11].targetedBuildingTile = 0;
                                            DAT_UnitsState::instance.units[iVar11].movementType_OR_targetUnitID = 0;
                                            if (UVar3 == Map::Units::States::US_MELEE_ATTACK) {
                                                DAT_UnitsState::instance.units[iVar11].movementCooldown
                                                    = DAT_UnitsState::instance.units[iVar11].movementSpeed * -4;
                                            }
                                            DAT_UnitsState::instance.units[iVar11].state.generic
                                                = Map::Units::States::US_MOVE_TO_DESTINATION;
                                            BVar16 = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
                                            if (!BVar16) {
                                                DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
                                            } else {
                                                DAT_PathFindingState::instance.allAssassinsUnk = 1;
                                            }
                                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                                DAT_UnitsState::ptr)(iVar11, uVar13, (uint)(sVar9), 0);
                                            UVar10 = (UnitInstructionType)((int)DAT_UnitsState::instance.units[iVar11]
                                                                               .totalSizeOfPathPlan
                                                / 2);
                                            DAT_UnitsState::instance.units[iVar11].lookForEnemy = -0x32;
                                            if ((int)unitInstructionType < (int)UVar10) {
                                                unitInstructionType = UVar10;
                                            }
                                            id = id + 0xc;
                                            DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                        }
                                    }
                                }
                            } while (iVar12 < this->tribes[_param_1_tribeID].size);
                        }
                        iVar11 = unitInstructionType * 8;
                        if (iVar11 < 9) {
                            iVar11 = 8;
                        }
                        this->tribes[_param_1_tribeID].field168_0x2be = (short)iVar11;
                        return (undefined4)(1);
                    }
                }
                break;
            case Map::Units::UIT_ATTACK_LAND:
            case Map::Units::UIT_THROW_COW:
                unitUID = this->tribes[tribeID].owner;
                this->tribes[tribeID].isRallyingUnk = 0;
                _unitTribeIndex = 0;
                if (0 < _tribeSize) {
                    do {
                        _unitID_0x05_0x16 = MACRO_CALL_MEMBER(
                            Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if ((DAT_UnitsState::instance.units[_unitID_0x05_0x16].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID_0x05_0x16].dying == 0)) {
                            switch (DAT_UnitsState::instance.units[_unitID_0x05_0x16].unitType) {
                            case Map::Units::UT_E_ARCHER:
                            case Map::Units::UT_E_XBOW:
                            case Map::Units::UT_E_ARCHER_DEBUG:
                            case Map::Units::UT_S_MANGONEL:
                            case Map::Units::UT_S_BALLISTA:
                            case Map::Units::UT_A_ARCHER:
                            case Map::Units::UT_A_SLINGER:
                            case Map::Units::UT_A_HARCHER:
                            case Map::Units::UT_A_FIRETHROWER:
                            case Map::Units::UT_S_FBALLISTA:
                                if (DAT_UnitsState::instance.units[_unitID_0x05_0x16].state.generic
                                    == (UnitState)0x69) {
                                    DAT_UnitsState::instance.units[_unitID_0x05_0x16].state.generic
                                        = Map::Units::States::US_MOVE_TO_DESTINATION;
                                }
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].field283_0x3f8 = 0;
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].targetingType
                                    = (UnitInstructionTypeShort)unitInstructionType;
                            LAB_00528808:
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].field253_0x3c5
                                    = (byte)unitInstructionType;
                                sVar9 = (short)_param_4_unitUID_Y;
                                if (unitInstructionType == Map::Units::UIT_THROW_COW
                                    && (UVar4 = DAT_UnitsState::instance.units[_unitID_0x05_0x16].unitType,
                                        UVar4 == Map::Units::UT_S_CATAPULT || (UVar4 == Map::Units::UT_S_TREBUCHET))) {
                                    if (DAT_GameState::instance.playerDataArray[unitUID].counter < 1) {
                                        DAT_UnitsState::instance.units[_unitID_0x05_0x16].field253_0x3c5 = 5;
                                    } else {
                                        DAT_UnitsState::instance.units[_unitID_0x05_0x16].targetingType
                                            = Map::Units::UIT_THROW_COW;
                                        DAT_UnitsState::instance.units[_unitID_0x05_0x16].shootTargetMicroX
                                            = _param_3_id_x_tile_buildingID_copy * 8;
                                        DAT_UnitsState::instance.units[_unitID_0x05_0x16].shootTargetMicroY = sVar9 * 8;
                                        DAT_UnitsState::instance.units[_unitID_0x05_0x16].shootTargetZ = (ushort)
                                            * (byte*)(DAT_ViewportRenderState::instance
                                                          .translationMatrix[_param_4_unitUID_Y]
                                                          .addXgetTile
                                                + 0x1d32c38 + iVar11);
                                    }
                                }
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].attackAtTileX
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].attackAtTileY = sVar9;
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].unkAttackRelated = (short)param_5;
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16]._someX_2 = 0;
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16]._someY_2 = 0;
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                    DAT_UnitsState::ptr)(_unitID_0x05_0x16);
                                DAT_UnitsState::instance.units[_unitID_0x05_0x16].shootBeforeStop = 10;
                                break;
                            case Map::Units::UT_S_CATAPULT:
                            case Map::Units::UT_S_TREBUCHET:
                                if (DAT_UnitsState::instance.units[_unitID_0x05_0x16]
                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                    != 0)
                                    goto LAB_00528808;
                            }
                        }
                        if (this->tribes[_param_1_tribeID].size <= _unitTribeIndex) {
                            return (undefined4)(1);
                        }
                    } while (true);
                }
                break;
            case Map::Units::UIT_FILL_MOAT:
                _targetArea = DAT_TileMapState::instance.PathConnectionLayer
                                  [DAT_UnitsState::instance.units[this->tribes[tribeID].selectionTargetUnitID].tile];
                this->tribes[tribeID].isRallyingUnk = 0;
                if ((int)(short)_targetArea != 0) {
                    iVar11 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                        DAT_PathFindingState::ptr)(
                        this->tribes[tribeID].owner, (dword)((int)((short)_targetArea)), (uint)(id), (uint)(unitUID));
                    if (iVar11 == 0) {
                        return (undefined4)(1);
                    }
                    unitUID = DAT_PathFindingState::instance.climbY;
                    uVar13 = DAT_PathFindingState::instance.climbX;
                }
            case Map::Units::UIT_DIG_MOAT:
                iVar11 = unitUID;
                iVar12 = 0;
                this->tribes[_param_1_tribeID].isRallyingUnk = 0;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                    tribeID, uVar13, (uint)(unitUID), 0, 1);
                if (0 < this->tribes[_param_1_tribeID].size) {
                    do {
                        iVar14 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, iVar12);
                        iVar12 = iVar12 + 1;
                        if ((DAT_UnitsState::instance.units[iVar14].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[iVar14].dying == 0)) {
                            switch (DAT_UnitsState::instance.units[iVar14].unitType) {
                            case Map::Units::UT_E_ARCHER:
                            case Map::Units::UT_E_SPEAR:
                            case Map::Units::UT_E_PIKE:
                            case Map::Units::UT_E_MACE:
                            case Map::Units::UT_E_ENGINEER:
                            case Map::Units::UT_A_SLAVE:
                                if (DAT_UnitsState::instance.units[iVar14].state.generic == (UnitState)0x69) {
                                    DAT_UnitsState::instance.units[iVar14].state.generic
                                        = Map::Units::States::US_MOVE_TO_DESTINATION;
                                }
                                DAT_UnitsState::instance.units[iVar14].targetingType = (undefined2)unitInstructionType;
                                DAT_UnitsState::instance.units[iVar14].attackAtTileX = (short)uVar13;
                                DAT_UnitsState::instance.units[iVar14].attackAtTileY = (short)iVar11;
                                DAT_UnitsState::instance.units[iVar14].targetX = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[iVar14].targetY
                                    = (UnitStateShort)_param_4_unitUID_Y_copy;
                                DAT_UnitsState::instance.units[iVar14].targetedBuildingTile = 0;
                                DAT_UnitsState::instance.units[iVar14].movementType_OR_targetUnitID = 0;
                                DAT_UnitsState::instance.units[iVar14]._someX_2 = 0;
                                DAT_UnitsState::instance.units[iVar14]._someY_2 = 0;
                            }
                        }
                    } while (iVar12 < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case Map::Units::UIT_ATTACK_BUILDING:
            case ((UnitInstructionType)0x24):
            case ((UnitInstructionType)0x26):
                _unitTribeIndex = 0;
                id = 0;
                this->tribes[tribeID].targetBuildingID = _param_3_id_x_tile_buildingID_copy;
                this->tribes[tribeID].targetBuildingUID = unitUID;
                this->tribes[tribeID].isRallyingUnk = 0;
                if (0 < _tribeSize) {
                    do {
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[iVar12].logicalState != Map::Units::ULS_NORMAL
                            || DAT_UnitsState::instance.units[iVar12].dying != 0
                            || DAT_UnitsState::instance.units[iVar12].field303_0x413 != 0)
                            continue;
                        DAT_UnitsState::instance.units[iVar12]._someX_2 = 0;
                        DAT_UnitsState::instance.units[iVar12]._someY_2 = 0;
                        switch (DAT_UnitsState::instance.units[iVar12].unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_SLINGER:
                        case Map::Units::UT_A_FIRETHROWER:
                            goto switchD_00528b77_caseD_16;
                        case Map::Units::UT_E_KNIGHT:
                            if (DAT_BuildingsState::instance.buildings[iVar11].buildingType
                                != Map::Buildings::BT_PITCHDITCH) {
                                _ramOrHorse = _ramOrHorse + 1;
                            }
                        case Map::Units::UT_TUNNELER:
                        case Map::Units::UT_E_SPEAR:
                        case Map::Units::UT_E_PIKE:
                        case Map::Units::UT_E_MACE:
                        case Map::Units::UT_E_SWORD:
                        case Map::Units::UT_E_MONK:
                        case Map::Units::UT_LORD:
                        case Map::Units::UT_A_SLAVE:
                        case Map::Units::UT_A_ASSASSIN:
                        case Map::Units::UT_A_SWORDSMAN:
                        switchD_00528b77_caseD_5:
                            if (DAT_BuildingsState::instance.buildings[iVar11].buildingType
                                != Map::Buildings::BT_PITCHDITCH) {
                                id = id + 1;
                            }
                            break;
                        case Map::Units::UT_S_CATAPULT:
                        case Map::Units::UT_S_TREBUCHET:
                        case Map::Units::UT_S_MANGONEL:
                        case Map::Units::UT_S_BALLISTA:
                        case Map::Units::UT_S_FBALLISTA:
                            if (unitInstructionType == (UnitInstructionType)0x26
                                || DAT_BuildingsState::instance.buildings[iVar11].buildingType
                                    == Map::Buildings::BT_PITCHDITCH)
                                break;
                            DAT_UnitsState::instance.units[iVar12].targetID_OR_targetBuildingID
                                = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[iVar12]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                = unitUID;
                            goto LAB_00528c46;
                        case Map::Units::UT_S_BATTERINGRAM:
                            if ((DAT_BuildingsState::instance.buildings[iVar11].buildingType
                                    != Map::Buildings::BT_PITCHDITCH)
                                && (DAT_UnitsState::instance.units[iVar12]
                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                    == 4)) {
                                id = id + 1;
                                _ramOrHorse = _ramOrHorse + 1;
                            }
                            break;
                        case Map::Units::UT_A_HARCHER:
                            _ramOrHorse = _ramOrHorse + 1;
                        switchD_00528b77_caseD_16:
                            if (unitInstructionType == (UnitInstructionType)0x24) {
                                switch (DAT_BuildingsState::instance.buildings[iVar11].buildingType) {
                                case Map::Buildings::BT_GATEHOUSELARGE:
                                case Map::Buildings::BT_GATEHOUSESMALL:
                                case Map::Buildings::BT_WOODGATE1:
                                case Map::Buildings::BT_WOODGATE2:
                                case Map::Buildings::BT_TOWER1:
                                case Map::Buildings::BT_TOWER2:
                                case Map::Buildings::BT_TOWER3:
                                case Map::Buildings::BT_TOWER4:
                                case Map::Buildings::BT_TOWER5:
                                    goto switchD_00528bae_caseD_2d;
                                }
                                goto switchD_00528b77_caseD_5;
                            }
                            if (unitInstructionType != (UnitInstructionType)0x26) {
                            switchD_00528bae_caseD_2d:
                                /*
                                  attack buildings
                                 */
                                if (DAT_UnitsState::instance.units[iVar12].state.generic == (UnitState)0x69) {
                                    DAT_UnitsState::instance.units[iVar12].state.generic
                                        = Map::Units::States::US_MOVE_TO_DESTINATION;
                                }
                                sVar8 = (short)((int)(DAT_BuildingsState::instance.buildings[iVar11].widthOrHeight * 8)
                                    / 2);
                                DAT_UnitsState::instance.units[iVar12].shootTargetMicroX
                                    = DAT_BuildingsState::instance.buildings[iVar11].x * 8 + sVar8;
                                sVar9 = DAT_BuildingsState::instance.buildings[iVar11].terrainHeightUnk;
                                DAT_UnitsState::instance.units[iVar12].shootTargetMicroY
                                    = DAT_BuildingsState::instance.buildings[iVar11].y * 8 + sVar8;
                                DAT_UnitsState::instance.units[iVar12].shootTargetZ = sVar9;
                                DAT_UnitsState::instance.units[iVar12].shootTargetedUnit = -1;
                                DAT_UnitsState::instance.units[iVar12].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[iVar12]
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID;
                            LAB_00528c46:
                                DAT_UnitsState::instance.units[iVar12].field253_0x3c5 = 9;
                                DAT_UnitsState::instance.units[iVar12].targetingType = Map::Units::UIT_ATTACK_BUILDING;
                                DAT_UnitsState::instance.units[iVar12].field283_0x3f8 = 0;
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                    DAT_UnitsState::ptr)(iVar12);
                                DAT_UnitsState::instance.units[iVar12].shootBeforeStop = 10;
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                }
                if ((((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                         || (DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0))
                        || (4 < (int)(short)DAT_BuildingsState::instance.buildings[iVar11].buildingType - 0x4aU))
                    && (id | x | id != 0)) {
                    sVar9 = this->tribes[_param_1_tribeID].selectionTargetUnitID;
                    if (unitInstructionType == Map::Units::UIT_ATTACK_BUILDING
                        || unitInstructionType == (UnitInstructionType)0x26) {
                        iVar12 = (int)DAT_UnitsState::instance.units[sVar9].owner;
                    } else {
                        iVar12 = 0;
                    }
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingForAttacksUnk,
                        DAT_PathFindingState::ptr)(tribeID, iVar11, id,
                        (dword)((int)((short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[sVar9].tile])),
                        iVar12);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::sortTribePathDestinationsByCost, this)(
                        tribeID, _ramOrHorse);
                    if ((DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper != 0)
                        && (_unitTribeIndex = 0, 0 < this->tribes[_param_1_tribeID].size)) {
                        id = 0x12d5c70;
                        do {
                            _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, _unitTribeIndex);
                            _unitTribeIndex = _unitTribeIndex + 1;
                            if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[_unitID].dying == 0
                                && DAT_UnitsState::instance.units[_unitID].field303_0x413 == 0) {
                                UVar4 = DAT_UnitsState::instance.units[_unitID].unitType;
                                switch (UVar4) {
                                case Map::Units::UT_TUNNELER:
                                case Map::Units::UT_E_SPEAR:
                                case Map::Units::UT_E_PIKE:
                                case Map::Units::UT_E_MACE:
                                case Map::Units::UT_E_SWORD:
                                case Map::Units::UT_E_KNIGHT:
                                case Map::Units::UT_E_MONK:
                                case Map::Units::UT_LORD:
                                case Map::Units::UT_S_BATTERINGRAM:
                                case Map::Units::UT_A_SLAVE:
                                case Map::Units::UT_A_ASSASSIN:
                                case Map::Units::UT_A_SWORDSMAN:
                                switchD_00528e3a_caseD_5:
                                    if (UVar4 != Map::Units::UT_S_BATTERINGRAM)
                                        goto LAB_00528f32;
                                    if (DAT_UnitsState::instance.units[_unitID]
                                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                        != 4)
                                        break;
                                    if (bVar5) {
                                    LAB_00528f32:
                                        iVar12 = *(int*)(id + -4);
                                        if (iVar12 == 0)
                                            break;
                                        sVar9 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[iVar12];
                                        unitUID = iVar12
                                            - DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                                        DAT_UnitsState::instance.units[_unitID].targetingType
                                            = ((UnitInstructionType)0);
                                        DAT_UnitsState::instance.units[_unitID].plannedDestinationX = (short)unitUID;
                                        DAT_UnitsState::instance.units[_unitID].plannedDestinationY = sVar9;
                                        if (DAT_UnitsState::instance.units[_unitID].state.generic
                                            == Map::Units::States::US_MELEE_ATTACK) {
                                            DAT_UnitsState::instance.units[_unitID].movementCooldown
                                                = DAT_UnitsState::instance.units[_unitID].movementSpeed * -4;
                                        }
                                        DAT_UnitsState::instance.units[_unitID].state.generic
                                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                                        BVar16 = MACRO_CALL_MEMBER(
                                            Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
                                        if (!BVar16) {
                                            DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
                                        } else {
                                            DAT_PathFindingState::instance.allAssassinsUnk = 1;
                                        }
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                            DAT_UnitsState::ptr)(_unitID, (uint)(unitUID), (uint)(sVar9), 0);
                                        DAT_UnitsState::instance.units[_unitID].movementType_OR_targetUnitID = 0;
                                        DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                        uVar13 = *(uint*)id;
                                        DAT_UnitsState::instance.units[_unitID].targetedBuildingTile = uVar13;
                                        sVar9 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[uVar13];
                                        DAT_UnitsState::instance.units[_unitID].attackAtTileY = sVar9;
                                        sVar9 = *(short*)id
                                            - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar9]
                                                  .addXgetTile;
                                        id = id + 0xc;
                                    } else {
                                        iVar12 = MACRO_CALL_MEMBER(
                                            Map::Navigation::PathFindingState_Func::findBuildingAccessPoint,
                                            DAT_PathFindingState::ptr)(_unitID, iVar11, &param_5);
                                        bVar5 = true;
                                        if (iVar12 == 0)
                                            goto LAB_00528f32;
                                        sVar9 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[iVar12];
                                        unitUID = iVar12
                                            - DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                                        BVar16 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                            DAT_UnitsState::ptr)(_unitID, (uint)(unitUID), (uint)(sVar9), 0);
                                        if (!BVar16)
                                            goto LAB_00528f32;
                                        DAT_UnitsState::instance.units[_unitID].targetingType
                                            = ((UnitInstructionType)0);
                                        DAT_UnitsState::instance.units[_unitID].plannedDestinationX = (short)unitUID;
                                        DAT_UnitsState::instance.units[_unitID].plannedDestinationY = sVar9;
                                        if (DAT_UnitsState::instance.units[_unitID].state.generic
                                            == Map::Units::States::US_MELEE_ATTACK) {
                                            DAT_UnitsState::instance.units[_unitID].movementCooldown
                                                = DAT_UnitsState::instance.units[_unitID].movementSpeed * -4;
                                        }
                                        DAT_UnitsState::instance.units[_unitID].state.generic
                                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                                        DAT_UnitsState::instance.units[_unitID].movementType_OR_targetUnitID = 0;
                                        DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                        sVar9 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[param_5];
                                        DAT_UnitsState::instance.units[_unitID].targetedBuildingTile = param_5;
                                        DAT_UnitsState::instance.units[_unitID].attackAtTileY = sVar9;
                                        sVar9 = (short)param_5
                                            - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar9]
                                                  .addXgetTile;
                                    }
                                    DAT_UnitsState::instance.units[_unitID].attackAtTileX = sVar9;
                                    break;
                                case Map::Units::UT_E_ARCHER:
                                case Map::Units::UT_E_XBOW:
                                case Map::Units::UT_A_ARCHER:
                                case Map::Units::UT_A_SLINGER:
                                case Map::Units::UT_A_HARCHER:
                                case Map::Units::UT_A_FIRETHROWER:
                                    if (unitInstructionType == (UnitInstructionType)0x24)
                                        goto switchD_00528e3a_caseD_5;
                                }
                            }
                            if (this->tribes[_param_1_tribeID].size <= _unitTribeIndex) {
                                return (undefined4)(1);
                            }
                        } while (true);
                    }
                }
                break;
            case Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED:
                this->tribes[tribeID].isRallyingUnk = 0;
                _y = DAT_BuildingsState::instance.buildings[id].buildingEntryY;
                _x = DAT_BuildingsState::instance.buildings[id].buildingEntryX;
                _unitTribeIndex = 0;
                BVar16 = MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)((int)_x, (uint)(_y));
                if (!BVar16) {
                    return (undefined4)(0);
                }
                param_5 = (int)(short)DAT_TileMapState::instance
                              .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile
                                  + (int)_x];
                unitUID = MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::getRequiredEngineersCount, DAT_BuildingsState::ptr)(iVar11);
                if (((unitUID | unitUID != 0)
                        || (DAT_BuildingsState::instance.buildings[iVar11].buildingType
                            == Map::Buildings::BT_OILSMELTER))
                    && 0 < this->tribes[_param_1_tribeID].size) {
                    do {
                        uVar13 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        iVar12 = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[uVar13].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[uVar13].dying == 0
                            && DAT_UnitsState::instance.units[uVar13].unitType == Map::Units::UT_E_ENGINEER
                            && (UVar3 = DAT_UnitsState::instance.units[uVar13].state.generic,
                                UVar3 != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_IDLEUnk)
                                    && (UVar3 != ((UnitState)10)))
                            && UVar3 != Map::Units::States::US_SIT_DOWNUnk
                            && UVar3 != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_RELOAD_WEAPONUnk)
                            && UVar3 != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_AIM_WEAPONUnk)
                            && UVar3 != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_FIRE_WEAPONUnk)
                            && UVar3 != (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_LOOK_AROUNDUnk)) {
                            DAT_UnitsState::instance.units[uVar13]._someX_2 = 0;
                            DAT_UnitsState::instance.units[uVar13]._someY_2 = 0;
                            cVar7 = MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::resolveBuildingEntryAccessibility,
                                DAT_BuildingsState::ptr)(iVar11, 1, (int)(DAT_UnitsState::instance.units[uVar13].x),
                                (int)(DAT_UnitsState::instance.units[uVar13].y));
                            if (((((uint)(extraout_var) & 0xffffff) << 8) | (uint)(byte)(cVar7)) != 0
                                && (iVar14 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[uVar13].owner,
                                        (dword)((int)(param_5)),
                                        (dword)((int)((short)DAT_TileMapState::instance
                                                .PathConnectionLayer[DAT_UnitsState::instance.units[uVar13].tile])),
                                        0),
                                    iVar14 != 0)) {
                                sVar9 = DAT_BuildingsState::instance.buildings[iVar11].buildingEntryY;
                                sVar8 = DAT_BuildingsState::instance.buildings[iVar11].buildingEntryX;
                                iVar14 = DAT_BuildingsState::instance.buildings[iVar11].uid;
                                DAT_UnitsState::instance.units[uVar13].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[uVar13].targetUID = iVar14;
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                    DAT_UnitsState::ptr)(uVar13, (uint)(sVar8), (uint)(sVar9), 0);
                                if (DAT_BuildingsState::instance.buildings[iVar11].buildingType
                                    == Map::Buildings::BT_OILSMELTER) {
                                    DAT_UnitsState::instance.units[uVar13].state.generic
                                        = Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_IDLEUnk;
                                    DAT_UnitsState::instance.units[uVar13].workplaceBuildingID_1
                                        = _param_3_id_x_tile_buildingID_copy;
                                } else {
                                    DAT_UnitsState::instance.units[uVar13].state.generic
                                        = Map::Units::States::US_STAND_UPUnk;
                                    DAT_UnitsState::instance.units[uVar13].resourceToDeposit = 0;
                                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                                        uVar13);
                                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                                        DAT_UnitsState::ptr)(this->tribes[_param_1_tribeID].owner, uVar13, 0);
                                    unitUID = unitUID + -1;
                                    iVar12 = _unitTribeIndex;
                                    if (unitUID == 0) {
                                        return (undefined4)(1);
                                    }
                                }
                            }
                        }
                        _unitTribeIndex = iVar12;
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case Map::Units::UIT_MAN_SIEGE_EQUIPMENT:
                /*
                  manning siege equipment?
                 */
                this->tribes[tribeID].isRallyingUnk = 0;
                if (DAT_UnitsState::instance.units[id].uid == unitUID
                    && (unitUID = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getRemainingRequiredEngineers, DAT_UnitsState::ptr)(id),
                        unitUID | unitUID != 0)
                    && (iVar12 = 0, 0 < this->tribes[_param_1_tribeID].size)) {
                    do {
                        uVar13 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, iVar12);
                        iVar14 = iVar12 + 1;
                        if (DAT_UnitsState::instance.units[uVar13].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[uVar13].dying == 0
                            && DAT_UnitsState::instance.units[uVar13].unitType == Map::Units::UT_E_ENGINEER) {
                            DAT_UnitsState::instance.units[iVar11]._someX_2 = 0;
                            DAT_UnitsState::instance.units[iVar11]._someY_2 = 0;
                            param_5 = (int)(short)DAT_TileMapState::instance
                                          .PathConnectionLayer[DAT_UnitsState::instance.units[uVar13].tile];
                            unitInstructionType = ((UnitInstructionType)0);
                            do {
                                iVar14 = (int)DAT_UnitsState::instance.units[iVar11]
                                             .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine;
                                x = (int)DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[iVar14][0]
                                    + (int)DAT_UnitsState::instance.units[iVar11].x;
                                y = (int)DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[iVar14][1]
                                    + (int)DAT_UnitsState::instance.units[iVar11].y;
                                uVar19 = (iVar14 + 1) % 16;
                                DAT_UnitsState::instance.units[iVar11]
                                    .digTileY__OR__countLifeCycleEngineersSentToManSiegeEngine = (short)uVar19;
                                BVar16 = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(x, y);
                                if (BVar16) {
                                    iVar14 = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                                    _param_4_unitUID_Y_copy
                                        = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar14];
                                    uVar19 = MACRO_CALL_MEMBER(
                                        Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(iVar14);
                                    uVar19 = ((int)DAT_UnitsState::instance.units[iVar11].buildingHeight
                                                 + (int)DAT_UnitsState::instance.units[iVar11].terrainOrClimbHeight)
                                        - uVar19;
                                    uVar17 = (int)uVar19 >> 0x1f;
                                    if ((int)((uVar19 ^ uVar17) - uVar17) < 0x11
                                        && (iVar14
                                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                    calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                DAT_PathFindingState::ptr)(
                                                (int)DAT_UnitsState::instance.units[iVar11].owner,
                                                (dword)((int)(param_5)), (dword)((int)(_param_4_unitUID_Y_copy)), 0),
                                            iVar14 != 0))
                                        break;
                                }
                                unitInstructionType = (UnitInstructionType)(unitInstructionType + 1);
                            } while ((int)unitInstructionType < 0x10);
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                                uVar13, x, y, 0);
                            DAT_UnitsState::instance.units[uVar13].state.generic
                                = Map::Units::States::US_MOVE_TO_DESTINATION;
                            DAT_UnitsState::instance.units[uVar13].targetingType = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                            DAT_UnitsState::instance.units[uVar13].targetedUnitID__OR__engineerMannedSiegeEngineRef
                                = (short)id;
                            DAT_UnitsState::instance.units[uVar13].resourceToDeposit = 0;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(uVar13);
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                                DAT_UnitsState::ptr)(this->tribes[_param_1_tribeID].owner, uVar13, 0);
                            unitUID = unitUID + -1;
                            iVar14 = iVar12;
                            if (unitUID == 0) {
                                return (undefined4)(1);
                            }
                        }
                        iVar12 = iVar14;
                        if (this->tribes[_param_1_tribeID].size <= iVar14) {
                            return (undefined4)(1);
                        }
                    } while (true);
                }
                break;
            case Map::Units::UIT_EXIT_SIEGE_EQUIPMENT:
                /*
                  disband siege engines?
                 */
                _param_4_unitUID_Y_copy = -(uint)(param_5 != 0) & 0x10;
                param_5 = (int)SEC_RNG::instance.currentNumber2 & 0x8000000f;
                if (param_5 < 0) {
                    param_5 = (param_5 - 1U | 0xfffffff0) + 1;
                }
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                if (DAT_UnitsState::instance.units[iVar11].uid == unitUID) {
                    DAT_UnitsState::instance.units[iVar11].state.generic = Map::Units::States::US_FIRE_WEAPONUnk;
                    unitInstructionType = ((UnitInstructionType)0);
                    if (0 < DAT_UnitsState::instance.units[iVar11]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300) {
                        tribeID = iVar11 * 0x490 + 0x1388860;
                        do {
                            _unitID_0x11 = (int)*(short*)tribeID;
                            *(undefined2*)tribeID = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].field249_0x3c0 = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].field248_0x3bc = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].animationCycleNumber = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].state.generic
                                = Map::Units::States::US_JESTER_ROAM_TO;
                            DAT_UnitsState::instance.units[_unitID_0x11].disappearFadeAlphaCountdown = 0x20;
                            DAT_UnitsState::instance.units[_unitID_0x11].engineerManningSiegeStateRef_checkType = 0xfe;
                            DAT_UnitsState::instance.units[_unitID_0x11].cachedState
                                = (UnitStateShort)_param_4_unitUID_Y_copy;
                            UVar4 = DAT_UnitsState::instance.units[iVar11].unitType;
                            if ((UVar4 == Map::Units::UT_S_MANGONEL) || (UVar4 == Map::Units::UT_S_BALLISTA)) {
                                DAT_UnitsState::instance.units[_unitID_0x11].goToRallyPoint = 1;
                            }
                            DAT_UnitsState::instance.units[_unitID_0x11].updateTickTracker = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].field39_0x58 = 1;
                            unitUID = 0;
                        LAB_00529da0:
                            do {
                                uVar19 = (int)DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[param_5][0]
                                    + (int)DAT_UnitsState::instance.units[iVar11].x;
                                uVar13 = (int)DAT_AttackInfoDefinedData::instance.SiegeCrewPositionOffsets[param_5][1]
                                    + (int)DAT_UnitsState::instance.units[iVar11].y;
                                param_5 = param_5 + 1U & 0x8000000f;
                                if (param_5 < 0) {
                                    param_5 = (param_5 - 1U | 0xfffffff0) + 1;
                                }
                                MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::findWalkableTileThatDoesNotContainUnit,
                                    DAT_PathFindingState::ptr)(id, uVar19, uVar13, 1);
                                if (DAT_PathFindingState::instance.ALG_ResultTile == 0) {
                                    MACRO_CALL_MEMBER(
                                        Map::Navigation::PathFindingState_Func::findWalkableTileThatDoesNotContainUnit,
                                        DAT_PathFindingState::ptr)(id, uVar19, uVar13, 0);
                                    sVar9 = (short)DAT_PathFindingState::instance.ALG_ResultX;
                                    sVar8 = (short)DAT_PathFindingState::instance.ALG_ResultY;
                                    iVar12 = DAT_PathFindingState::instance.ALG_ResultTile;
                                    if (DAT_PathFindingState::instance.ALG_ResultTile != 0)
                                        break;
                                    unitUID = unitUID + 1;
                                    if (unitUID | unitUID != 0x10)
                                        goto LAB_00529da0;
                                    sVar9 = DAT_UnitsState::instance.units[iVar11].x;
                                    sVar8 = DAT_UnitsState::instance.units[iVar11].y;
                                    iVar12 = DAT_UnitsState::instance.units[iVar11].tile;
                                } else {
                                    sVar9 = (short)DAT_PathFindingState::instance.ALG_ResultX;
                                    sVar8 = (short)DAT_PathFindingState::instance.ALG_ResultY;
                                    iVar12 = DAT_PathFindingState::instance.ALG_ResultTile;
                                }
                            } while (iVar12 == 0);
                            bVar2 = DAT_TileMapState::instance.HeightLayer[iVar12];
                            DAT_UnitsState::instance.units[_unitID_0x11].totalSizeOfPathPlan = 0;
                            DAT_UnitsState::instance.units[_unitID_0x11].x = sVar9;
                            DAT_UnitsState::instance.units[_unitID_0x11].mimicCurrentXPosition = sVar9;
                            DAT_UnitsState::instance.units[_unitID_0x11].y = sVar8;
                            DAT_UnitsState::instance.units[_unitID_0x11].mimicCurrentYPosition = sVar8;
                            DAT_UnitsState::instance.units[_unitID_0x11].terrainOrClimbHeight = (ushort)bVar2;
                            DAT_UnitsState::instance.units[_unitID_0x11].tile = iVar12;
                            DAT_UnitsState::instance.units[_unitID_0x11].nextTileUnk = iVar12;
                            DAT_UnitsState::instance.units[_unitID_0x11].microXPosition = sVar9 * 8 + 4;
                            DAT_UnitsState::instance.units[_unitID_0x11].microYPosition = sVar8 * 8 + 4;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::updateMicroPosition, DAT_UnitsState::ptr)(
                                _unitID_0x11);
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                                _unitID_0x11);
                            tribeID = tribeID + 2;
                            DAT_UnitsState::instance.units[_unitID_0x11].animationSheetFrameOffset = 1;
                            DAT_UnitsState::instance.units[_unitID_0x11].field_0x30_animRelated = 0x10;
                            unitInstructionType = (UnitInstructionType)(unitInstructionType + 1);
                        } while ((int)unitInstructionType < (int)DAT_UnitsState::instance.units[iVar11]
                                     .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300);
                    }
                    DAT_UnitsState::instance.units[iVar11]
                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 = 0;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                        DAT_UnitsState::ptr)(id);
                    return (undefined4)(1);
                }
                break;
            case Map::Units::UIT_THROW_OIL:
                iVar11 = 0;
                this->tribes[tribeID].isRallyingUnk = 0;
                if (0 < _tribeSize) {
                    do {
                        uVar13 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, iVar11);
                        iVar11 = iVar11 + 1;
                        if (DAT_UnitsState::instance.units[uVar13].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[uVar13].dying == 0
                            && DAT_UnitsState::instance.units[uVar13].unitType == Map::Units::UT_E_ENGINEER) {
                            DAT_UnitsState::instance.units[uVar13].targetingType = Map::Units::UIT_THROW_OIL;
                            DAT_UnitsState::instance.units[uVar13].attackAtTileX = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[uVar13].attackAtTileY = (short)unitUID;
                            DAT_UnitsState::instance.units[uVar13].plannedDestinationX
                                = _param_3_id_x_tile_buildingID_copy;
                            DAT_UnitsState::instance.units[uVar13].plannedDestinationY = (short)unitUID;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(uVar13);
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                                DAT_UnitsState::ptr)(this->tribes[_param_1_tribeID].owner, uVar13, 0);
                            DAT_UnitsState::instance.units[uVar13]._someX_2 = 0;
                            DAT_UnitsState::instance.units[uVar13]._someY_2 = 0;
                        }
                    } while (iVar11 < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case ((UnitInstructionType)0x15):
                this->tribes[tribeID].isRallyingUnk = 0;
                uVar13 = (uint)DAT_BuildingsState::instance.buildings[id].buildingEntryY;
                _unitTribeIndex = 0;
                BVar16
                    = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                        (int)DAT_BuildingsState::instance.buildings[id].buildingEntryX, uVar13);
                if (!BVar16) {
                    return (undefined4)(0);
                }
                param_5
                    = (int)(short)DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[uVar13].addXgetTile
                              + (int)DAT_BuildingsState::instance.buildings[iVar11].buildingEntryX];
                if (0 < _tribeSize) {
                    do {
                        uVar13 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[uVar13].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[uVar13].dying == 0
                            && DAT_UnitsState::instance.units[uVar13].unitType == Map::Units::UT_TUNNELER) {
                            DAT_UnitsState::instance.units[uVar13]._someX_2 = 0;
                            DAT_UnitsState::instance.units[uVar13]._someY_2 = 0;
                            iVar12 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                                DAT_BuildingsState::ptr)(iVar11, 1);
                            if (iVar12 != 0
                                && (iVar12 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                   calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[uVar13].owner,
                                        (dword)((int)(param_5)),
                                        (dword)((int)((short)DAT_TileMapState::instance
                                                .PathConnectionLayer[DAT_UnitsState::instance.units[uVar13].tile])),
                                        0),
                                    iVar12 != 0)) {
                                sVar9 = DAT_BuildingsState::instance.buildings[iVar11].buildingEntryY;
                                sVar8 = DAT_BuildingsState::instance.buildings[iVar11].buildingEntryX;
                                iVar11 = DAT_BuildingsState::instance.buildings[iVar11].uid;
                                DAT_UnitsState::instance.units[uVar13].workplaceBuildingID_1
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[uVar13].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[uVar13].targetUID = iVar11;
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                    DAT_UnitsState::ptr)(uVar13, (uint)(sVar8), (uint)(sVar9), 0);
                                DAT_UnitsState::instance.units[uVar13].state.generic
                                    = Map::Units::States::US_LOOK_AROUNDUnk;
                                DAT_UnitsState::instance.units[uVar13].targetingType = ((UnitInstructionType)0x15);
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                                    uVar13);
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection,
                                    DAT_UnitsState::ptr)(this->tribes[_param_1_tribeID].owner, uVar13, 0);
                                return (undefined4)(1);
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                }
                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                    iVar11);
                break;
            case Map::Units::UIT_ATTACK_WALL:
            case ((UnitInstructionType)0x23):
            case ((UnitInstructionType)0x25):
                _unitTribeIndex = 0;
                id = 0;
                this->tribes[tribeID].isRallyingUnk = 0;
                if (0 < _tribeSize) {
                    do {
                        uVar13 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[uVar13].logicalState != Map::Units::ULS_NORMAL
                            || DAT_UnitsState::instance.units[uVar13].dying != 0
                            || DAT_UnitsState::instance.units[uVar13].field303_0x413 != 0)
                            continue;
                        DAT_UnitsState::instance.units[uVar13]._someX_2 = 0;
                        DAT_UnitsState::instance.units[uVar13]._someY_2 = 0;
                        switch (DAT_UnitsState::instance.units[uVar13].unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_SLINGER:
                        case Map::Units::UT_A_ASSASSIN:
                        case Map::Units::UT_A_FIRETHROWER:
                            goto switchD_005290c7_caseD_16;
                        case Map::Units::UT_E_KNIGHT:
                        switchD_005290c7_caseD_1c:
                            _ramOrHorse = _ramOrHorse + 1;
                        case Map::Units::UT_TUNNELER:
                        case Map::Units::UT_E_SPEAR:
                        case Map::Units::UT_E_PIKE:
                        case Map::Units::UT_E_MACE:
                        case Map::Units::UT_E_SWORD:
                        case Map::Units::UT_E_MONK:
                        case Map::Units::UT_LORD:
                        case Map::Units::UT_A_SLAVE:
                        case Map::Units::UT_A_SWORDSMAN:
                        switchD_005290c7_caseD_5:
                            id = id + 1;
                            break;
                        case Map::Units::UT_S_CATAPULT:
                        case Map::Units::UT_S_TREBUCHET:
                        case Map::Units::UT_S_MANGONEL:
                        case Map::Units::UT_S_BALLISTA:
                        case Map::Units::UT_S_FBALLISTA:
                            if (unitInstructionType != (UnitInstructionType)0x25) {
                                sVar9 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar11];
                                DAT_UnitsState::instance.units[uVar13].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[uVar13]
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID;
                                DAT_UnitsState::instance.units[uVar13].attackAtTileY = sVar9;
                                DAT_UnitsState::instance.units[uVar13].attackAtTileX
                                    = _param_3_id_x_tile_buildingID_copy
                                    - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                                DAT_UnitsState::instance.units[uVar13].field253_0x3c5 = 0x17;
                                DAT_UnitsState::instance.units[uVar13].targetingType = Map::Units::UIT_ATTACK_WALL;
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                    DAT_UnitsState::ptr)(uVar13);
                                DAT_UnitsState::instance.units[uVar13].shootBeforeStop = 10;
                            }
                            break;
                        case Map::Units::UT_S_TOWER:
                            uVar19 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::findFreeTileNearby,
                                DAT_UnitsState::ptr)(uVar13, (uint)(iVar11));
                            if (uVar19 != 0) {
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(uVar13,
                                    (uint)(uVar19
                                        - DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[uVar19]]
                                            .addXgetTile),
                                    (uint)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[uVar19]),
                                    0);
                                sVar9 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar11];
                                DAT_UnitsState::instance.units[uVar13].targetingType = Map::Units::UIT_ATTACK_WALL;
                                DAT_UnitsState::instance.units[uVar13].state.generic
                                    = Map::Units::States::US_MOVE_TO_DESTINATION;
                                DAT_UnitsState::instance.units[uVar13].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[uVar13].targetedBuildingTile = iVar11;
                                DAT_UnitsState::instance.units[uVar13].digTileTarget = uVar19;
                                DAT_UnitsState::instance.units[uVar13].attackAtTileY = sVar9;
                                DAT_UnitsState::instance.units[uVar13].attackAtTileX
                                    = _param_3_id_x_tile_buildingID_copy
                                    - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                            }
                            break;
                        case Map::Units::UT_S_BATTERINGRAM:
                            if (DAT_UnitsState::instance.units[uVar13]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                == 4) {
                                local_8 = local_8 + 1;
                                goto switchD_005290c7_caseD_1c;
                            }
                            break;
                        case Map::Units::UT_A_HARCHER:
                            _ramOrHorse = _ramOrHorse + 1;
                        switchD_005290c7_caseD_16:
                            if (unitInstructionType == (UnitInstructionType)0x23)
                                goto switchD_005290c7_caseD_5;
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                    && (DAT_GameState::instance.mapAndTime.skirmishStrongWalls != 0)) {
                    id = local_8;
                }
                if (id | x | id != 0) {
                    sVar9 = this->tribes[_param_1_tribeID].selectionTargetUnitID;
                    if (unitInstructionType == Map::Units::UIT_ATTACK_WALL
                        || unitInstructionType == (UnitInstructionType)0x25) {
                        sVar8 = DAT_UnitsState::instance.units[sVar9].facingDirection;
                        iVar12 = (int)DAT_UnitsState::instance.units[sVar9].owner;
                    } else {
                        sVar8 = DAT_UnitsState::instance.units[sVar9].facingDirection;
                        iVar12 = 0;
                    }
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                          findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance,
                        DAT_PathFindingState::ptr)(iVar11, id,
                        (int*)((int)((short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[sVar9].tile])),
                        iVar12, 0, (int)(sVar8));
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::sortTribePathDestinationsByCost, this)(
                        tribeID, _ramOrHorse);
                    if ((DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper != 0)
                        && (iVar12 = 0, 0 < this->tribes[_param_1_tribeID].size)) {
                        id = 0x12d5c70;
                        do {
                            iVar14 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, iVar12);
                            iVar12 = iVar12 + 1;
                            if (DAT_UnitsState::instance.units[iVar14].logicalState == Map::Units::ULS_NORMAL
                                && DAT_UnitsState::instance.units[iVar14].dying == 0
                                && DAT_UnitsState::instance.units[iVar14].field303_0x413 == 0) {
                                UVar4 = DAT_UnitsState::instance.units[iVar14].unitType;
                                switch (UVar4) {
                                case Map::Units::UT_TUNNELER:
                                case Map::Units::UT_E_SPEAR:
                                case Map::Units::UT_E_PIKE:
                                case Map::Units::UT_E_MACE:
                                case Map::Units::UT_E_SWORD:
                                case Map::Units::UT_E_KNIGHT:
                                case Map::Units::UT_E_MONK:
                                case Map::Units::UT_LORD:
                                case Map::Units::UT_A_SLAVE:
                                case Map::Units::UT_A_SWORDSMAN:
                                switchD_0052932a_caseD_5:
                                    if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                                        || (DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0))
                                        goto switchD_0052932a_caseD_3b;
                                    break;
                                case Map::Units::UT_E_ARCHER:
                                case Map::Units::UT_E_XBOW:
                                case Map::Units::UT_A_ARCHER:
                                case Map::Units::UT_A_SLINGER:
                                case Map::Units::UT_A_ASSASSIN:
                                case Map::Units::UT_A_HARCHER:
                                case Map::Units::UT_A_FIRETHROWER:
                                    if (unitInstructionType == (UnitInstructionType)0x23)
                                        goto switchD_0052932a_caseD_5;
                                    break;
                                case Map::Units::UT_S_BATTERINGRAM:
                                switchD_0052932a_caseD_3b:
                                    if (UVar4 == Map::Units::UT_S_BATTERINGRAM) {
                                        if (DAT_UnitsState::instance.units[iVar14]
                                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                            != 4)
                                            break;
                                        if (!bVar5) {
                                            bVar5 = true;
                                            iVar15
                                                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                        findUnitPreferredOrientationBasedConnectedTile,
                                                    DAT_PathFindingState::ptr)(iVar14, iVar11);
                                            if (iVar15 != 0) {
                                                sVar9 = DAT_ViewportRenderState::instance
                                                            .tileTranslationMatrix_YComponent[iVar15];
                                                unitUID = iVar15
                                                    - DAT_ViewportRenderState::instance.translationMatrix[sVar9]
                                                          .addXgetTile;
                                                BVar16 = MACRO_CALL_MEMBER(
                                                    Map::Units::UnitsState_Func::setDestinationForUnit,
                                                    DAT_UnitsState::ptr)(iVar14, (uint)(unitUID), (uint)(sVar9), 0);
                                                if (BVar16) {
                                                    DAT_UnitsState::instance.units[iVar14].targetingType
                                                        = ((UnitInstructionType)0);
                                                    DAT_UnitsState::instance.units[iVar14].plannedDestinationX
                                                        = (short)unitUID;
                                                    DAT_UnitsState::instance.units[iVar14].plannedDestinationY = sVar9;
                                                    if (DAT_UnitsState::instance.units[iVar14].state.generic
                                                        == Map::Units::States::US_MELEE_ATTACK) {
                                                        DAT_UnitsState::instance.units[iVar14].movementCooldown
                                                            = DAT_UnitsState::instance.units[iVar14].movementSpeed * -4;
                                                    }
                                                    DAT_UnitsState::instance.units[iVar14].state.generic
                                                        = Map::Units::States::US_MOVE_TO_DESTINATION;
                                                    DAT_UnitsState::instance.units[iVar14].movementType_OR_targetUnitID
                                                        = 0;
                                                    DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                                    sVar9 = DAT_ViewportRenderState::instance
                                                                .tileTranslationMatrix_YComponent[iVar11];
                                                    DAT_UnitsState::instance.units[iVar14].targetedBuildingTile
                                                        = iVar11;
                                                    DAT_UnitsState::instance.units[iVar14].attackAtTileY = sVar9;
                                                    DAT_UnitsState::instance.units[iVar14].attackAtTileX
                                                        = _param_3_id_x_tile_buildingID_copy
                                                        - (short)DAT_ViewportRenderState::instance
                                                              .translationMatrix[sVar9]
                                                              .addXgetTile;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    iVar15 = *(int*)(id + -4);
                                    if (iVar15 != 0) {
                                        sVar9 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[iVar15];
                                        uVar13 = iVar15
                                            - DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                                        DAT_UnitsState::instance.units[iVar14].targetingType = ((UnitInstructionType)0);
                                        DAT_UnitsState::instance.units[iVar14].plannedDestinationX = (short)uVar13;
                                        DAT_UnitsState::instance.units[iVar14].plannedDestinationY = sVar9;
                                        DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
                                        if (DAT_UnitsState::instance.units[iVar14].state.generic
                                            == Map::Units::States::US_MELEE_ATTACK) {
                                            DAT_UnitsState::instance.units[iVar14].movementCooldown
                                                = DAT_UnitsState::instance.units[iVar14].movementSpeed * -4;
                                        }
                                        DAT_UnitsState::instance.units[iVar14].state.generic
                                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                            DAT_UnitsState::ptr)(iVar14, uVar13, (uint)(sVar9), 0);
                                        DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                        uVar13 = *(uint*)id;
                                        sVar9 = *(short*)id;
                                        DAT_UnitsState::instance.units[iVar14].movementType_OR_targetUnitID = 0;
                                        DAT_UnitsState::instance.units[iVar14].targetedBuildingTile = uVar13;
                                        sVar8 = DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[uVar13];
                                        DAT_UnitsState::instance.units[iVar14].attackAtTileY = sVar8;
                                        id = id + 0xc;
                                        DAT_UnitsState::instance.units[iVar14].attackAtTileX = sVar9
                                            - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar8]
                                                  .addXgetTile;
                                    }
                                }
                            }
                            if (this->tribes[_param_1_tribeID].size <= iVar12) {
                                return (undefined4)(1);
                            }
                        } while (true);
                    }
                }
                break;
            case Map::Units::UIT_SET_LADDER:
                iVar12 = 0;
                id = 0;
                this->tribes[tribeID].isRallyingUnk = 0;
                if (0 < _tribeSize) {
                    do {
                        iVar14 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, iVar12);
                        iVar12 = iVar12 + 1;
                        if (DAT_UnitsState::instance.units[iVar14].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[iVar14].dying == 0
                            && DAT_UnitsState::instance.units[iVar14].unitType == Map::Units::UT_E_LADDER) {
                            id = id + 1;
                            DAT_UnitsState::instance.units[iVar14]._someX_2 = 0;
                            DAT_UnitsState::instance.units[iVar14]._someY_2 = 0;
                        }
                    } while (iVar12 < this->tribes[_param_1_tribeID].size);
                    if (id | x | id != 0) {
                        sVar9 = this->tribes[_param_1_tribeID].selectionTargetUnitID;
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                              populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea,
                            DAT_PathFindingState::ptr)(iVar11, id,
                            (dword)((int)((short)DAT_TileMapState::instance
                                    .PathConnectionLayer[DAT_UnitsState::instance.units[sVar9].tile])),
                            (int)(DAT_UnitsState::instance.units[sVar9].owner));
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::sortTribePathDestinationsByCost, this)(
                            tribeID, 0);
                        if ((DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper != 0)
                            && (iVar11 = 0, 0 < this->tribes[_param_1_tribeID].size)) {
                            piVar18 = &DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper;
                            do {
                                _laddermanID = MACRO_CALL_MEMBER(
                                    Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, iVar11);
                                iVar11 = iVar11 + 1;
                                if (DAT_UnitsState::instance.units[_laddermanID].logicalState == Map::Units::ULS_NORMAL
                                    && DAT_UnitsState::instance.units[_laddermanID].dying == 0
                                    && DAT_UnitsState::instance.units[_laddermanID].unitType == Map::Units::UT_E_LADDER
                                    && (_freeTile = ((PathHelper12*)(piVar18 + -1))->tile1, _freeTile != 0)) {
                                    /*
                                      set ladder men destination to free id next to defensive structure
                                     */
                                    _freeTileY
                                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_freeTile];
                                    _freeTileX = _freeTile
                                        - DAT_ViewportRenderState::instance.translationMatrix[_freeTileY].addXgetTile;
                                    DAT_UnitsState::instance.units[_laddermanID].targetingType
                                        = ((UnitInstructionType)0);
                                    DAT_UnitsState::instance.units[_laddermanID].plannedDestinationX
                                        = (short)_freeTileX;
                                    DAT_UnitsState::instance.units[_laddermanID].plannedDestinationY = _freeTileY;
                                    DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
                                    if (DAT_UnitsState::instance.units[_laddermanID].state.generic
                                        == Map::Units::States::US_MELEE_ATTACK) {
                                        DAT_UnitsState::instance.units[_laddermanID].movementCooldown
                                            = DAT_UnitsState::instance.units[_laddermanID].movementSpeed * -4;
                                    }
                                    DAT_UnitsState::instance.units[_laddermanID].state.generic
                                        = (ushort)(*piVar18 != 0) * 2 + Map::Units::States::US_MOVE_TO_DESTINATION;
                                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                        DAT_UnitsState::ptr)(_laddermanID, _freeTileX, (uint)(_freeTileY), 0);
                                    DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                    _defensiveTile1 = *piVar18;
                                    _defensiveTile2 = *piVar18;
                                    /*
                                      set ladder man ladder target id
                                     */
                                    DAT_UnitsState::instance.units[_laddermanID].targetedBuildingTile = _defensiveTile1;
                                    sVar9 = DAT_ViewportRenderState::instance
                                                .tileTranslationMatrix_YComponent[_defensiveTile1];
                                    DAT_UnitsState::instance.units[_laddermanID].attackAtTileY = sVar9;
                                    piVar18 = piVar18 + 3;
                                    DAT_UnitsState::instance.units[_laddermanID].attackAtTileX = (short)_defensiveTile2
                                        - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar9].addXgetTile;
                                }
                            } while (iVar11 < this->tribes[_param_1_tribeID].size);
                            return (undefined4)(1);
                        }
                    }
                }
                break;
            case Map::Units::UT_E_MACE:
                iVar11 = 0;
                if (0 < _tribeSize) {
                    do {
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            _param_1_tribeID, iVar11);
                        iVar11 = iVar11 + 1;
                        if (DAT_UnitsState::instance.units[iVar12].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[iVar12].dying == 0
                            && (int)(short)DAT_UnitsState::instance.units[iVar12].unitType - 0x27U < 2) {
                            DAT_UnitsState::instance.units[iVar12].field243_0x3b0 = 1;
                        }
                    } while (iVar11 < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case Map::Units::UIT_DISBAND:
                /*
                  disband?
                 */
                this->tribes[tribeID].isRallyingUnk = 0;
                _unitTribeIndex = 0;
                if (0 < _tribeSize) {
                    do {
                        _unitID_0x1e = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            _param_1_tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if ((DAT_UnitsState::instance.units[_unitID_0x1e].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_unitID_0x1e].dying == 0)) {
                            switch (DAT_UnitsState::instance.units[_unitID_0x1e].unitType) {
                            case Map::Units::UT_TUNNELER:
                            case Map::Units::UT_E_ARCHER:
                            case Map::Units::UT_E_XBOW:
                            case Map::Units::UT_E_SPEAR:
                            case Map::Units::UT_E_PIKE:
                            case Map::Units::UT_E_MACE:
                            case Map::Units::UT_E_SWORD:
                            case Map::Units::UT_E_KNIGHT:
                            case Map::Units::UT_E_LADDER:
                            case Map::Units::UT_E_ENGINEER:
                            case Map::Units::UT_E_MONK:
                            case Map::Units::UT_A_ARCHER:
                            case Map::Units::UT_A_SLAVE:
                            case Map::Units::UT_A_SLINGER:
                            case Map::Units::UT_A_ASSASSIN:
                            case Map::Units::UT_A_HARCHER:
                            case Map::Units::UT_A_SWORDSMAN:
                            case Map::Units::UT_A_FIRETHROWER:
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::disbandUnit, DAT_UnitsState::ptr)(
                                    _unitID_0x1e);
                                break;
                            case Map::Units::UT_S_CATAPULT:
                            case Map::Units::UT_S_TREBUCHET:
                            case Map::Units::UT_S_MANGONEL:
                            case Map::Units::UT_S_TOWER:
                            case Map::Units::UT_S_BATTERINGRAM:
                            case Map::Units::UT_S_SHIELD:
                            case Map::Units::UT_S_BALLISTA:
                            case Map::Units::UT_S_FBALLISTA:
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, this)(
                                    _param_1_tribeID, Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, _unitID_0x1e,
                                    DAT_UnitsState::instance.units[_unitID_0x1e].uid, 1);
                                _gamemodeSiegeThat = DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT;
                                DAT_UnitsState::instance.units[_unitID_0x1e].state.generic
                                    = Map::Units::States::US_DISAPPEAR;
                                if (_gamemodeSiegeThat) {
                                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getPriceForDisbandedUnitType,
                                        DAT_BuildingsState::ptr)(
                                        (Map::Units::UnitType)(DAT_UnitsState::instance.units[_unitID_0x1e].unitType),
                                        &tribeID);
                                    piVar18 = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .startResources
                                        + 0xf;
                                    *piVar18 = *piVar18 + tribeID;
                                }
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                }
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, DAT_UnitsState::ptr)(
                    this->tribes[_param_1_tribeID].owner, 0, 0);
                return (undefined4)(1);
            case Map::Units::UIT_STOP:
                iVar11 = 0;
                this->tribes[tribeID].isRallyingUnk = 0;
                this->tribes[tribeID].someUnitID = 0;
                if (0 < _tribeSize) {
                    do {
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, iVar11);
                        iVar11 = iVar11 + 1;
                        if (DAT_UnitsState::instance.units[iVar12].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[iVar12].dying == 0
                            && DAT_UnitsState::instance.units[iVar12].field303_0x413 == 0) {
                            DAT_UnitsState::instance.units[iVar12].field253_0x3c5 = 3;
                            DAT_UnitsState::instance.units[iVar12].targetingType
                                = Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                            DAT_UnitsState::instance.units[iVar12].field243_0x3b0 = 0;
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                DAT_UnitsState::ptr)(iVar12);
                            DAT_UnitsState::instance.units[iVar12].targetedBuildingTile = 0;
                            DAT_UnitsState::instance.units[iVar12].movementType_OR_targetUnitID = 0;
                        }
                    } while (iVar11 < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
                break;
            case ((UnitInstructionType)0x20):
            case Map::Units::UIT_SHOOT_TARGETUnk:
                local_8 = id * 0x490;
                pUVar6 = DAT_UnitsState::instance.units + id;
                _unitTribeIndex = 0;
                id = 0;
                if (pUVar6->uid != unitUID) {
                    return (undefined4)(0);
                }
                if (0 < _tribeSize) {
                    do {
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if (DAT_UnitsState::instance.units[iVar12].logicalState == Map::Units::ULS_NORMAL
                            && DAT_UnitsState::instance.units[iVar12].dying == 0
                            && DAT_UnitsState::instance.units[iVar12].field303_0x413 == 0
                            && (UVar3 = DAT_UnitsState::instance.units[iVar12].state.generic,
                                UVar3 != Map::Units::States::US_MELEE_ATTACK)) {
                            switch (DAT_UnitsState::instance.units[iVar12].unitType) {
                            case Map::Units::UT_TUNNELER:
                            case Map::Units::UT_E_SPEAR:
                            case Map::Units::UT_E_PIKE:
                            case Map::Units::UT_E_MACE:
                            case Map::Units::UT_E_SWORD:
                            case Map::Units::UT_E_KNIGHT:
                            case Map::Units::UT_E_MONK:
                            case Map::Units::UT_LORD:
                            case Map::Units::UT_A_SLAVE:
                            case Map::Units::UT_A_ASSASSIN:
                            case Map::Units::UT_A_SWORDSMAN:
                                if (unitInstructionType != Map::Units::UIT_SHOOT_TARGETUnk) {
                                    id = id + 1;
                                }
                                break;
                            case Map::Units::UT_E_ARCHER:
                            case Map::Units::UT_E_XBOW:
                            case Map::Units::UT_E_ARCHER_DEBUG:
                            case Map::Units::UT_A_ARCHER:
                            case Map::Units::UT_A_SLINGER:
                            case Map::Units::UT_A_HARCHER:
                            case Map::Units::UT_A_FIRETHROWER:
                            switchD_005282f6_caseD_16:
                                if (UVar3 == (UnitState)0x69) {
                                    DAT_UnitsState::instance.units[iVar12].state.generic
                                        = Map::Units::States::US_MOVE_TO_DESTINATION;
                                }
                                DAT_UnitsState::instance.units[iVar12].targetingType = Map::Units::UIT_UNIT_ATTACK_UNIT;
                                DAT_UnitsState::instance.units[iVar12].targetedUnitID__OR__engineerMannedSiegeEngineRef
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[iVar12]
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID;
                                DAT_UnitsState::instance.units[iVar12].field283_0x3f8 = 0;
                                if (DAT_UnitsState::instance.units[iVar11].unitType == Map::Units::UT_RABBIT) {
                                    this->tribes[_param_1_tribeID].containsRabbit = 1;
                                }
                                if (DAT_UnitsState::instance.units[iVar12]._someX_2 == 0) {
                                    sVar9 = DAT_UnitsState::instance.units[iVar12].destinationY_2Unk;
                                    DAT_UnitsState::instance.units[iVar12]._someX_2
                                        = DAT_UnitsState::instance.units[iVar12].destinationX_2Unk;
                                    DAT_UnitsState::instance.units[iVar12]._someY_2 = sVar9;
                                }
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                    DAT_UnitsState::ptr)(iVar12);
                                break;
                            case Map::Units::UT_S_CATAPULT:
                            case Map::Units::UT_S_TREBUCHET:
                                if (unitInstructionType != Map::Units::UIT_SHOOT_TARGETUnk) {
                                    sVar9 = DAT_UnitsState::instance.units[iVar12]._someX_2;
                                    DAT_UnitsState::instance.units[iVar12].field253_0x3c5 = 5;
                                    DAT_UnitsState::instance.units[iVar12].targetingType = Map::Units::UIT_ATTACK_LAND;
                                    DAT_UnitsState::instance.units[iVar12].attackAtTileX
                                        = DAT_UnitsState::instance.units[iVar11].x;
                                    DAT_UnitsState::instance.units[iVar12].attackAtTileY
                                        = DAT_UnitsState::instance.units[iVar11].y;
                                    DAT_UnitsState::instance.units[iVar12].unkAttackRelated = 0xb;
                                    if (sVar9 == 0) {
                                        sVar9 = DAT_UnitsState::instance.units[iVar12].destinationY_2Unk;
                                        DAT_UnitsState::instance.units[iVar12]._someX_2
                                            = DAT_UnitsState::instance.units[iVar12].destinationX_2Unk;
                                        DAT_UnitsState::instance.units[iVar12]._someY_2 = sVar9;
                                    }
                                    MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                        DAT_UnitsState::ptr)(iVar12);
                                    DAT_UnitsState::instance.units[iVar12].shootBeforeStop = 10;
                                }
                                break;
                            case Map::Units::UT_S_MANGONEL:
                            case Map::Units::UT_S_BALLISTA:
                            case Map::Units::UT_S_FBALLISTA:
                                if (unitInstructionType != Map::Units::UIT_SHOOT_TARGETUnk) {
                                    DAT_UnitsState::instance.units[iVar12].shootBeforeStop = 10;
                                    goto switchD_005282f6_caseD_16;
                                }
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                    if (id | x | id != 0) {
                        iVar12 = (int)this->tribes[_param_1_tribeID].selectionTargetUnitID;
                        param_5 = (int)DAT_UnitsState::instance.units[iVar12].x;
                        unitInstructionType = (UnitInstructionType)DAT_UnitsState::instance.units[iVar12].y;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::predictUnitInterceptPosition, this)(
                            iVar12, iVar11, &param_5, (int*)&unitInstructionType);
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathPlanningForTribe,
                            DAT_PathFindingState::ptr)(tribeID, (undefined4)((int)(iVar11)), (uint)(param_5),
                            (uint)(unitInstructionType), id,
                            (dword)((int)((short)DAT_TileMapState::instance
                                    .PathConnectionLayer[DAT_UnitsState::instance.units[iVar12].tile])),
                            (int)(DAT_UnitsState::instance.units[iVar12].owner));
                        this->tribes[_param_1_tribeID].someUnitID = _param_3_id_x_tile_buildingID_copy;
                        this->tribes[_param_1_tribeID].someUnitUID = unitUID;
                        this->tribes[_param_1_tribeID].someTile = DAT_UnitsState::instance.units[iVar11].tile;
                        iVar12 = 0;
                        sVar9 = this->tribes[_param_1_tribeID].size;
                        this->tribes[_param_1_tribeID].someTile2
                            = (int)DAT_UnitsState::instance.units[iVar11].destinationX_2Unk
                            + DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_UnitsState::instance.units[iVar11].destinationY_2Unk]
                                  .addXgetTile;
                        unitInstructionType = ((UnitInstructionType)0);
                        if (0 < sVar9) {
                            id = 0x12d5c6c;
                            do {
                                iVar14 = MACRO_CALL_MEMBER(
                                    Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, iVar12);
                                iVar12 = iVar12 + 1;
                                if (DAT_UnitsState::instance.units[iVar14].logicalState == Map::Units::ULS_NORMAL
                                    && DAT_UnitsState::instance.units[iVar14].dying == 0
                                    && DAT_UnitsState::instance.units[iVar14].field303_0x413 == 0
                                    && DAT_UnitsState::instance.units[iVar14].state.generic
                                        != Map::Units::States::US_MELEE_ATTACK) {
                                    switch (DAT_UnitsState::instance.units[iVar14].unitType) {
                                    case Map::Units::UT_TUNNELER:
                                    case Map::Units::UT_E_SPEAR:
                                    case Map::Units::UT_E_PIKE:
                                    case Map::Units::UT_E_MACE:
                                    case Map::Units::UT_E_SWORD:
                                    case Map::Units::UT_E_KNIGHT:
                                    case Map::Units::UT_E_MONK:
                                    case Map::Units::UT_LORD:
                                    case Map::Units::UT_A_SLAVE:
                                    case Map::Units::UT_A_ASSASSIN:
                                    case Map::Units::UT_A_SWORDSMAN:
                                        _tile1_528565 = *(int*)id;
                                        if (_tile1_528565 != 0) {
                                            _y_528565 = DAT_ViewportRenderState::instance
                                                            .tileTranslationMatrix_YComponent[_tile1_528565];
                                            _x_528565 = _tile1_528565
                                                - DAT_ViewportRenderState::instance.translationMatrix[_y_528565]
                                                      .addXgetTile;
                                            if (*(int*)(id + 4) == 0) {
                                                DAT_UnitsState::instance.units[iVar14].targetingType
                                                    = ((UnitInstructionType)0);
                                                if (DAT_UnitsState::instance.units[iVar14].unitType
                                                    == Map::Units::UT_LORD)
                                                    break;
                                            } else {
                                                DAT_UnitsState::instance.units[iVar14].targetingType
                                                    = Map::Units::UIT_UNIT_ATTACK_UNIT;
                                                DAT_UnitsState::instance.units[iVar14]
                                                    .targetedUnitID__OR__engineerMannedSiegeEngineRef
                                                    = _param_3_id_x_tile_buildingID_copy;
                                                DAT_UnitsState::instance.units[iVar14]
                                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                                    = unitUID;
                                            }
                                            DAT_UnitsState::instance.units[iVar14].plannedDestinationX
                                                = (short)_x_528565;
                                            DAT_UnitsState::instance.units[iVar14].plannedDestinationY = _y_528565;
                                            DAT_UnitsState::instance.units[iVar14].targetedBuildingTile = 0;
                                            if (DAT_UnitsState::instance.units[iVar14].state.generic
                                                == Map::Units::States::US_MELEE_ATTACK) {
                                                DAT_UnitsState::instance.units[iVar14].movementCooldown
                                                    = DAT_UnitsState::instance.units[iVar14].movementSpeed * -4;
                                            }
                                            if (DAT_UnitsState::instance.units[iVar14]._someX_2 == 0) {
                                                DAT_UnitsState::instance.units[iVar14]._someX_2
                                                    = DAT_UnitsState::instance.units[iVar14].destinationX_2Unk;
                                                DAT_UnitsState::instance.units[iVar14]._someY_2
                                                    = DAT_UnitsState::instance.units[iVar14].destinationY_2Unk;
                                            }
                                            DAT_UnitsState::instance.units[iVar14].state.generic
                                                = Map::Units::States::US_MOVE_TO_DESTINATION;
                                            _isAllAssassins_528565 = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
                                            if (_isAllAssassins_528565 == 0) {
                                                DAT_PathFindingState::instance.notAllAssassinsUnk = 1;
                                            } else {
                                                DAT_PathFindingState::instance.allAssassinsUnk = 1;
                                            }
                                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit,
                                                DAT_UnitsState::ptr)(iVar14, _x_528565, (uint)(_y_528565), 0);
                                            DAT_UnitsState::instance.units[iVar14].moveDelay = 0;
                                            DAT_UnitsState::instance.units[iVar14].lookForEnemy = -0x32;
                                            if (DAT_UnitsState::instance.units[iVar14].movementType_OR_targetUnitID
                                                != iVar11) {
                                                DAT_UnitsState::instance.units[iVar14].movementType_OR_targetUnitID
                                                    = _param_3_id_x_tile_buildingID_copy;
                                                psVar1 = (short*)((int)&DAT_UnitsState::instance.units[0].huntedBy
                                                    + local_8);
                                                *psVar1 = *psVar1 + 1;
                                            }
                                            UVar10 = (UnitInstructionType)((int)DAT_UnitsState::instance.units[iVar14]
                                                                               .totalSizeOfPathPlan
                                                / 2);
                                            if ((int)unitInstructionType < (int)UVar10) {
                                                unitInstructionType = UVar10;
                                            }
                                            id = id + 0xc;
                                            DAT_PathFindingState::instance.notAllAssassinsUnk = 0;
                                        }
                                    }
                                }
                            } while (iVar12 < this->tribes[_param_1_tribeID].size);
                        }
                        iVar11 = unitInstructionType * 8;
                        if (iVar11 < 9) {
                            iVar11 = 8;
                        }
                        this->tribes[_param_1_tribeID].field168_0x2be = (short)iVar11;
                        return (undefined4)(1);
                    }
                }
                break;
            case Map::Units::UIT_LIGHT_PITCH:
                this->tribes[tribeID].isRallyingUnk = 0;
                _unitTribeIndex = 0;
                if ((DAT_TileMapState::instance.pitchDitches[id].uid == unitUID) && (0 < _tribeSize)) {
                    do {
                        iVar12 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitTribeIndex);
                        _unitTribeIndex = _unitTribeIndex + 1;
                        if ((DAT_UnitsState::instance.units[iVar12].logicalState == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[iVar12].dying == 0)) {
                            DAT_UnitsState::instance.units[iVar12]._someX_2 = 0;
                            DAT_UnitsState::instance.units[iVar12]._someY_2 = 0;
                            UVar4 = DAT_UnitsState::instance.units[iVar12].unitType;
                            if ((UVar4 == Map::Units::UT_E_ARCHER) || (UVar4 == Map::Units::UT_A_ARCHER)) {
                                sVar9 = DAT_TileMapState::instance.pitchDitches[iVar11].y;
                                DAT_UnitsState::instance.units[iVar12].shootTargetMicroX
                                    = DAT_TileMapState::instance.pitchDitches[iVar11].x * 8 + 4;
                                iVar14 = DAT_TileMapState::instance.pitchDitches[iVar11].tile;
                                DAT_UnitsState::instance.units[iVar12].shootTargetMicroY = sVar9 * 8 + 4;
                                DAT_UnitsState::instance.units[iVar12].shootTargetZ
                                    = (ushort)DAT_TileMapState::instance.HeightLayer[iVar14];
                                DAT_UnitsState::instance.units[iVar12].shootTargetedUnit = -1;
                                DAT_UnitsState::instance.units[iVar12].targetID_OR_targetBuildingID
                                    = _param_3_id_x_tile_buildingID_copy;
                                DAT_UnitsState::instance.units[iVar12]
                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                                    = unitUID;
                                DAT_UnitsState::instance.units[iVar12].field253_0x3c5 = 0x22;
                                DAT_UnitsState::instance.units[iVar12].targetingType = Map::Units::UIT_LIGHT_PITCH;
                                DAT_UnitsState::instance.units[iVar12].field283_0x3f8 = 0;
                                MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                                    DAT_UnitsState::ptr)(iVar12);
                                DAT_UnitsState::instance.units[iVar12].shootBeforeStop = 10;
                            }
                        }
                    } while (_unitTribeIndex < this->tribes[_param_1_tribeID].size);
                    return (undefined4)(1);
                }
            }
            return (undefined4)(1);
        }

    }
}
}
