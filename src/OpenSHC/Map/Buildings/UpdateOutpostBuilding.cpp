#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/GameModeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using AI::AIType;
    using Game::GameMode;
    using Game::GameMode2;
    using Game::GameModeInt;
    using Map::Buildings::BuildingType;
    using Map::Units::UnitInstructionType;
    using Map::Units::UnitType;
    using Map::Units::Behavior::UnitStanceEnum;
    using Map::Units::Instructions::UnitMatchSpeedEnum;
    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00411540
    void Buildings::UpdateOutpostBuilding()
    {
        char* pcVar1;
        short sVar2;
        short sVar3;
        ushort uVar4;
        GameModeInt GVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int _randomUnitID;
        int _requiredEngineers;
        int _engineerID;
        int iVar10;
        UnitType unitType;
        short* psVar11;
        uint uVar12;
        int* piVar13;
        int _tribeID;
        char* local_18;
        uint local_14;
        int local_10;
        int local_c;
        int local_4;
        UnitTypeInt _randomUnitType;
        int _tribeUID;
        iVar9 = DAT_CurrentBuildingID::instance;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        piVar13 = &DAT_GameState::instance.playerDataArray[sVar2].someCount04;
        *piVar13 = *piVar13 + 10;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar9);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        GVar5 = DAT_GameSynchronyState::instance.currentGameMode;
        iVar9 = DAT_CurrentBuildingID::instance;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            piVar13 = &DAT_BuildingsState::instance.buildings[iVar9].flagSlot.ownerFlagFrame;
            *piVar13 = *piVar13 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar9].flagSlot.ownerFlagFrame
                        / 2]
                <= '\0') {
                DAT_BuildingsState::instance.buildings[iVar9].flagSlot.ownerFlagFrame = 0;
            }
            DAT_BuildingsState::instance.buildings[iVar9].overlayImageID
                = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar9].flagSlot.ownerFlagFrame / 2];
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {}
        if (GVar5 != Game::GM_SOLITARY && GVar5 != Game::GM_SKIRMISH_SINGLE_PLAYER
            && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks) {}
        if (DAT_BuildingsState::instance.buildings[iVar9].surroundingsRevealed == 0) {
            DAT_BuildingsState::instance.buildings[iVar9].surroundingsRevealed = 1;
            iVar6 = (int)DAT_BuildingsState::instance.buildings[iVar9].widthOrHeight / 2;
            iVar10 = (short)DAT_BuildingsState::instance.buildings[iVar9].x + iVar6;
            iVar6 = iVar6 + (short)DAT_BuildingsState::instance.buildings[iVar9].y;
            iVar8 = iVar10 + 8;
            uVar12 = iVar10 - 8;
            if ((int)uVar12 < iVar8) {
                local_18 = (char*)((int)DAT_ViewportRenderState::ptr + uVar12 * 0x191 + 0xc0);
                do {
                    if (iVar6 + -8 < iVar6 + 8) {
                        piVar13 = &DAT_ViewportRenderState::instance.translationMatrix[iVar6 + -8].addXgetTile;
                        iVar10 = (iVar6 + 8) - (iVar6 + -8);
                        do {
                            if (uVar12 < 400 && *local_18 != '\0'
                                && (iVar7 = (int)(short)DAT_TileMapState::instance.UnitLayer[*piVar13 + uVar12],
                                    iVar7 != 0)) {
                                sVar3 = DAT_BuildingsState::instance.buildings[iVar9].owner;
                                do {
                                    if (DAT_UnitsState::instance.units[iVar7].owner == sVar3) {
                                        DAT_UnitsState::instance.units[iVar7].aiUnitBehaviourType = 0x32;
                                    }
                                    iVar7 = (int)(short)DAT_UnitsState::instance.units[iVar7].nextUnitOnTheSameTile;
                                } while (iVar7);
                            }
                            piVar13 = piVar13 + 3;
                            iVar10 = iVar10 + -1;
                        } while (iVar10);
                    }
                    local_18 = local_18 + 0x191;
                    uVar12 = uVar12 + 1;
                } while ((int)uVar12 < iVar8);
            }
        }
        sVar3 = DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk3;
        if (0 < sVar3) {
            DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk3 = sVar3 + -1;
        }
        _tribeID = (int)DAT_BuildingsState::instance.buildings[iVar9].tribeID;
        local_10 = (int)DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex;
        if ((_tribeID)
            && (DAT_TribesState::instance.tribes[_tribeID].uid
                != DAT_BuildingsState::instance.buildings[iVar9].tribeUID)) {
            _tribeID = 0;
        }
        if (DAT_BuildingsState::instance.buildings[iVar9].randomOutpostField <= '\0') {
            uVar12 = (int)SEC_RNG::instance.currentNumber2 & 0x80000001;
            if ((int)uVar12 < 0) {
                uVar12 = (uVar12 - 1 | 0xfffffffe) + 1;
            }
            DAT_BuildingsState::instance.buildings[iVar9].randomOutpostField = (char)uVar12 + '\x06';
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 1200;
        } else {
            psVar11 = &DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk4;
            *psVar11 = *psVar11 + -1;
            iVar8 = DAT_CurrentBuildingID::instance;
            if (DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk4 < 0) {
                DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk4 = 1200;
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].insideUnitID1;
                iVar6 = 0;
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].insideUnitUID1)) {
                    iVar6 = 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].workerID[0];
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].workerUID[0])) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].insideUnitID2;
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].insideUnitUID2)) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].workerID[1];
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].workerUID[1])) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].insideUnitID3;
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].insideUnitUID3)) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].workerID[2];
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].workerUID[2])) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].insideUnitID4;
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].insideUnitUID4)) {
                    iVar6 = iVar6 + 1;
                }
                sVar3 = DAT_BuildingsState::instance.buildings[iVar8].workerID[3];
                if ((0 < sVar3)
                    && (DAT_UnitsState::instance.units[sVar3].uid
                        == DAT_BuildingsState::instance.buildings[iVar8].workerUID[3])) {
                    iVar6 = iVar6 + 1;
                }
                if (iVar6 < DAT_BuildingsState::instance.buildings[iVar9].randomOutpostField) {
                    /*
                      european archer
                     */
                    unitType = Map::Units::UT_E_ARCHER;
                    if (DAT_BuildingsState::instance.buildings[iVar9].buildingType
                        == Map::Buildings::BT_OUTPOST_ARABIAN) {
                        /*
                          arabian archer
                         */
                        unitType = Map::Units::UT_A_ARCHER;
                    }
                    iVar8 = (int)DAT_BuildingsState::instance.buildings[iVar9].owner;
                    /*
                      spawn archer
                     */
                    iVar9 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(iVar8, iVar8,
                        (int)(DAT_BuildingsState::instance.buildings[iVar9].buildingEntryX * 8),
                        (int)(DAT_BuildingsState::instance.buildings[iVar9].buildingEntryY * 8), 8, unitType);
                    if (iVar9) {
                        DAT_UnitsState::instance.units[iVar9].aiUnitBehaviourType = 0x32;
                        DAT_UnitsState::instance.units[iVar9].goToRallyPoint = 0;
                        DAT_UnitsState::instance.units[iVar9].state.generic
                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                        local_18 = (char*)0xffffffff;
                        local_14 = 0xffffffff;
                        local_c = 0;
                        do {
                            iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                         .widthOrHeight
                                    / 2
                                + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x;
                            iVar6 = (int)SEC_RNG::instance.currentNumber2 % 0xe;
                            pcVar1 = (char*)(iVar10 + -7 + iVar6);
                            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            iVar8 = (int)SEC_RNG::instance.currentNumber2;
                            iVar7 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .widthOrHeight
                                    / 2
                                + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y;
                            uVar12 = iVar7 + -7 + iVar8 % 0xe;
                            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            if ((int)pcVar1 < 400 && uVar12 < 400
                                && *(char*)(uVar12 * 400 + 0x21aec98 + (int)pcVar1) != '\0') {
                                iVar8 = DAT_ViewportRenderState::instance.translationMatrix[iVar8 % 0xe + iVar7 + -7]
                                            .addXgetTile;
                                int _unitPathConnection
                                    = (short)DAT_TileMapState::instance.PathConnectionLayer
                                          [DAT_ViewportRenderState::instance
                                                  .translationMatrix[DAT_UnitsState::instance.units[iVar9].y]
                                                  .addXgetTile
                                              + (int)DAT_UnitsState::instance.units[iVar9].x];
                                int _targetMacroTile
                                    = (short)DAT_TileMapState::instance.MacroLayer[iVar6 + iVar10 + iVar8 + 0x13a09];
                                if (_unitPathConnection == _targetMacroTile
                                    || (iVar7 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                                            DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[iVar9].owner,
                                            (dword)_unitPathConnection, (dword)_targetMacroTile,
                                            (int)(DAT_UnitsState::instance.units[iVar9].unitCanClimb)),
                                        iVar7 != 0)) {
                                    if ((int)local_18 < 0) {
                                        local_18 = pcVar1;
                                        local_14 = uVar12;
                                    }
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar6 + iVar10 + iVar8 + -7]
                                            & 0x10000000U))
                                        break;
                                }
                            }
                            local_c = local_c + 1;
                            pcVar1 = local_18;
                            uVar12 = local_14;
                        } while (local_c < 0xf);
                        local_14 = uVar12;
                        local_18 = pcVar1;
                        if (-1 < (int)local_18) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                                iVar9, (uint)(local_18), local_14, 0);
                        }
                        iVar8 = DAT_CurrentBuildingID::instance;
                        iVar6 = 0;
                        psVar11 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID;
                        do {
                            if (psVar11[0xa1] < 1
                                || DAT_UnitsState::instance.units[psVar11[0xa1]].uid
                                    != *(int*)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                                   .quarryLinkedOxTethers
                                        + iVar6 * 2 + 0xf)) {
                                iVar10 = DAT_UnitsState::instance.units[iVar9].uid;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                    .quarryLinkedOxTethers[iVar6 + 0xb] = (short)iVar9;
                                *(int*)(DAT_BuildingsState::instance.buildings[iVar8].quarryLinkedOxTethers + iVar6 * 2
                                    + 0xf) = iVar10;
                                break;
                            }
                            if ((*psVar11 <= 0)
                                || (DAT_UnitsState::instance.units[*psVar11].uid
                                    != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .workerUID[iVar6])) {
                                iVar10 = DAT_UnitsState::instance.units[iVar9].uid;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[iVar6]
                                    = (short)iVar9;
                                DAT_BuildingsState::instance.buildings[iVar8].workerUID[iVar6] = iVar10;
                                break;
                            }
                            iVar6 = iVar6 + 1;
                            psVar11 = psVar11 + 1;
                        } while (iVar6 < 4);
                    }
                }
            }
        }
        iVar9 = DAT_CurrentBuildingID::instance;
        if (!_tribeID) {
            iVar8 = 2000 - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk06;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                || DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER || 399 < iVar8) {
                if (iVar8 < 100) {
                    iVar8 = 100;
                }
            } else {
                iVar8 = 400;
            }
            psVar11 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field268_0x308;
            *psVar11 = *psVar11 + 1;
            if (DAT_BuildingsState::instance.buildings[iVar9].field268_0x308 < iVar8) {}
            uVar4 = DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk1;
            uVar12 = (uint)((uVar4 & 1));
            if ((uVar4 & 2)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 4)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 8)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 0x10)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 0x20)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 0x40)) {
                uVar12 = uVar12 + 1;
            }
            if ((uVar4 & 0x80)) {
                uVar12 = uVar12 + 1;
            }
            if (!uVar12) {}
            iVar6 = (int)SEC_RNG::instance.currentNumber2 % (int)uVar12;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            iVar9 = DAT_CurrentBuildingID::instance;
            iVar8 = 0;
            if ((uVar4 & 1)) {
                if (!iVar6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 0;
                }
                iVar8 = 1;
            }
            if ((uVar4 & 2)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 1;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 4)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 2;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 8)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 3;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 0x10)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 4;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 0x20)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 5;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 0x40)) {
                if (iVar6 == iVar8) {
                    DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 6;
                }
                iVar8 = iVar8 + 1;
            }
            if ((uVar4 & 0x80) && iVar6 == iVar8) {
                DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex = 7;
            }
            if (DAT_BuildingsState::instance.buildings[iVar9].buildingType == Map::Buildings::BT_OUTPOST_ARABIAN) {
                psVar11 = &DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex;
                *psVar11 = *psVar11 + 8;
            }
            local_10 = (int)DAT_BuildingsState::instance.buildings[iVar9].spawnUnitTypeIndex;
            _tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(
                (int)DAT_BuildingsState::instance.buildings[iVar9].owner);
            iVar9 = DAT_CurrentBuildingID::instance;
            if (_tribeID <= 0) {}
            _tribeUID = DAT_TribesState::instance.tribes[_tribeID].uid;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID = (short)_tribeID;
            DAT_BuildingsState::instance.buildings[iVar9].tribeUID = _tribeUID;
            iVar6 = (int)SEC_RNG::instance.currentNumber2;
            iVar8 = DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][3];
            sVar3 = DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk2;
            DAT_TribesState::instance.tribes[_tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk05
                = ((short)(iVar6 % iVar8) + (short)DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][2])
                * (sVar3 + 1);
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            iVar8 = DAT_CurrentBuildingID::instance;
            iVar9 = DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][0xc];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field273_0x312 = 1;
            DAT_TribesState::instance.tribes[_tribeID].tribeSubtype1 = (short)iVar9;
            DAT_BuildingsState::instance.buildings[iVar8].field268_0x308 = 2000;
        }
        iVar8 = DAT_CurrentBuildingID::instance;
        iVar6 = DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][0]
            - (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].incByFourUnk;
        iVar9 = DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][1];
        if (iVar6 < iVar9) {
            iVar6 = iVar9;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER && iVar6 < 0x32) {
            iVar6 = 0x32;
        }
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk2;
        psVar11 = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field268_0x308;
        *psVar11 = *psVar11 + 1;
        if (((sVar3 * -0xf + 100) * iVar6) / 100 <= (int)DAT_BuildingsState::instance.buildings[iVar8].field268_0x308) {
            DAT_BuildingsState::instance.buildings[iVar8].field268_0x308 = SEC_RNG::instance.currentNumber2 % 0x28;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3;
            if (sVar3 < 1
                || (int)DAT_TribesState::instance.tribes[_tribeID].size
                    < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05
                        + -1) {
                uVar12 = (uint)(DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][4] != 0);
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][5] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][6] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][7] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][8] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][9] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][10] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][0xb] != 0) {
                    uVar12 = uVar12 + 1;
                }
                if (((local_10 == 7) || (local_10 == 6))
                    && ((!sVar3 && (DAT_TribesState::instance.tribes[_tribeID].size == 0))
                        || ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field273_0x312 != 0
                            && (0 < DAT_TribesState::instance.tribes[_tribeID].size))))) {
                    uVar12 = 1;
                }
                _randomUnitType
                    = DAT_BuildingDefinedData::instance
                          .SpawnUnitProperties[local_10][(int)SEC_RNG::instance.currentNumber2 % (int)uVar12 + 4];
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                local_18 = (char*)0x1;
                if (0 < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3
                    && DAT_TribesState::instance.tribes[_tribeID].size == 0
                    && DAT_GameState::instance.playerDataArray[sVar2].aiType != AI::AIT_NULL) {
                    local_18 = (char*)((int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .outpostRelatedUnk05
                        / 2);
                    if (local_18 == (char*)0x0) {
                        local_18 = (char*)0x1;
                    }
                    if (((local_10 == 7) || (local_10 == 6)) && 1 < (int)local_18
                        && _randomUnitType == Map::Units::UT_S_CATAPULT) {
                        _randomUnitType = DAT_BuildingDefinedData::instance.SpawnUnitProperties[local_10][5];
                    }
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                    || DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
                    || DAT_GameState::instance.playerDataArray[sVar2].count_2
                            + DAT_GameState::instance.playerDataArray[sVar2].armySize
                        < DAT_GameState::instance.mapAndTime.armySizeLimit) {
                    for (local_4 = 0; local_4 < (int)local_18; local_4++) {
                        iVar9 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                        _randomUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            iVar9, iVar9,
                            (int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX
                                * 8),
                            (int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY
                                * 8),
                            8, (UnitType)((int)(_randomUnitType)));
                        if (!_randomUnitID) {}
                        if (_randomUnitType == Map::Units::UT_S_CATAPULT) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field273_0x312 = 0;
                        }
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            _randomUnitID, _tribeID);
                        switch (_randomUnitType) {
                        case Map::Units::UT_S_CATAPULT:
                        case Map::Units::UT_S_FBALLISTA:
                            _requiredEngineers = 2;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                            _requiredEngineers = 3;
                            break;
                        default:
                            goto switchD_004121d2_caseD_29;
                        case Map::Units::UT_S_TOWER:
                        case Map::Units::UT_S_BATTERINGRAM:
                            _requiredEngineers = 4;
                            break;
                        case Map::Units::UT_S_SHIELD:
                            _requiredEngineers = 1;
                        }
                        do {
                            iVar9 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                            /*
                              spawn siege engineer
                             */
                            _engineerID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(iVar9, iVar9,
                                (int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                          .buildingEntryX
                                    * 8),
                                (int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                          .buildingEntryY
                                    * 8),
                                8, Map::Units::UT_E_ENGINEER);
                            if (_engineerID) {
                                DAT_UnitsState::instance.units[_engineerID].targetingType
                                    = Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                                DAT_UnitsState::instance.units[_engineerID]
                                    .targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)_randomUnitID;
                            }
                            _requiredEngineers = _requiredEngineers + -1;
                        } while (_requiredEngineers);
                    switchD_004121d2_caseD_29:
                        DAT_UnitsState::instance.units[_randomUnitID].aiUnitBehaviourType = 0x32;
                        DAT_UnitsState::instance.units[_randomUnitID].goToRallyPoint = 0;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        _tribeID,
                        (uint)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX),
                        (uint)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY),
                        0, 0, Map::Units::Instructions::UMSE_0);
                    if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05
                            <= DAT_TribesState::instance.tribes[_tribeID].size)
                        && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3
                            <= 0)) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::aiRegisterTribeAndAssignTarget, DAT_AICState::ptr)(
                            _tribeID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID);
                        iVar9 = DAT_CurrentBuildingID::instance;
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID = 0;
                        psVar11 = &DAT_BuildingsState::instance.buildings[iVar9].outpostRelatedUnk06;
                        *psVar11 = *psVar11 + 100;
                        psVar11 = &DAT_BuildingsState::instance.buildings[iVar9].incByFourUnk;
                        *psVar11 = *psVar11 + 4;
                    }
                }
            }
        }
    }

}
}
