#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::GameMode;
    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004167E0
    void Buildings::UpdateDairyFarm()
    {
        byte* pbVar1;
        byte bVar2;
        uint uVar3;
        int iVar4;
        int _cow;
        int _ownerPlayerIndex;
        int* piVar5;
        int iVar6;
        int iVar7;
        short sVar8;
        short* psVar9;
        int iVar10;
        iVar7 = DAT_CurrentBuildingID::instance;
        _ownerPlayerIndex = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].countFarms
            = DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].countFarms + 1;
        if (DAT_BuildingsState::instance.buildings[iVar7].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].farmsWithoutWorkers
                = DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].farmsWithoutWorkers + 1;
        }
        if ('\0' < (char)DAT_BuildingsState::instance.buildings[iVar7].numberOfAnimals) {
            DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].someResourceCounter = 0;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar7);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar7 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar7].displayOwnerFlag
            = (uint)(DAT_BuildingsState::instance.buildings[iVar7].workers[0] != 0);
        DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter
            = DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter + 1;
        if (1 < DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter) {
            DAT_BuildingsState::instance.buildings[iVar7].animationTickCounter = 0;
            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock
                = DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock + 1;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1
                = DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 + 1;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2
                = DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2 + 1;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame3
                = DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame3 + 1;
        }
        sVar8 = DAT_BuildingsState::instance.buildings[iVar7].flagonsOfAleOrCheeseOrReleaseDogs;
        if (sVar8) {
            DAT_BuildingsState::instance.buildings[iVar7].flagonsOfAleOrCheeseOrReleaseDogs = sVar8 + -1;
        }
        if (DAT_BuildingsState::instance.buildings[iVar7].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 0;
            DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite2 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3 = 0;
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite4 = 0;
            goto LAB_00416a00;
        }
        bVar2 = DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage;
        if (!bVar2) {
            if ((char)DAT_BuildingsState::instance.buildings[iVar7].numberOfAnimals < '\x03'
                && DAT_BuildingsState::instance.buildings[iVar7].flagonsOfAleOrCheeseOrReleaseDogs == 0) {
                DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4
                    = DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4 + 1;
                if (400 < DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4) {
                    DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 1;
                    DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4 = 0;
                    DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0x20;
                }
            } else if ((DAT_BuildingsState::instance.buildings[iVar7].resources[0xb] == 0)
                && (psVar9 = &DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4, *psVar9 = *psVar9 + 1,
                    400 < DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4)) {
                DAT_BuildingsState::instance.buildings[iVar7].workerRotationIndex
                    = DAT_BuildingsState::instance.buildings[iVar7].workerRotationIndex + 1;
                if ('\x03' < (char)DAT_BuildingsState::instance.buildings[iVar7].workerRotationIndex) {
                    DAT_BuildingsState::instance.buildings[iVar7].workerRotationIndex = 1;
                }
                bVar2 = DAT_BuildingsState::instance.buildings[iVar7].workerRotationIndex;
                _ownerPlayerIndex = (int)DAT_BuildingsState::instance.buildings[iVar7].workerID[(char)bVar2];
                if (!_ownerPlayerIndex) {}
                if (DAT_UnitsState::instance.units[_ownerPlayerIndex].uid
                    != DAT_BuildingsState::instance.buildings[iVar7].workerUID[(char)bVar2]) {}
                DAT_BuildingsState::instance.buildings[iVar7].outpostRelatedUnk4 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 3;
                DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0x20;
                DAT_UnitsState::instance.units[_ownerPlayerIndex].state.generic = Map::Units::States::US_JESTER_ROAM_TO;
                DAT_UnitsState::instance.units[_ownerPlayerIndex].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[_ownerPlayerIndex].engineerManningSiegeStateRef_checkType = 1;
            }
            goto LAB_00416a00;
        }
        if (bVar2 == 1) {
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0x46;
            DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength
                = DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength + -1;
            if (DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength < 1) {
                DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0;
                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 2;
            }
            goto LAB_00416a00;
        }
        if (bVar2 != 2) {
            if (bVar2 == 3) {
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0x10;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite2 = 0x1c;
                DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength + -1;
                if (DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength < 1) {
                    DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0;
                    DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 = 0;
                    DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 4;
                }
            } else if (bVar2 == 4) {
                if (DAT_BuildingDefinedData::instance
                        .DairyFarmAnimationFrames3[DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1]
                    == 0) {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3 = 0x30;
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0x10;
                    DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength
                        = DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength + 1;
                    if (0x1f < DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength) {
                        DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0x20;
                        DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 5;
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0;
                        DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite2 = 0;
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 = 0;
                        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2 = 0;
                    }
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1
                        = (int)(char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames2
                              [DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite2
                        = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames3
                              [DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1]
                        + 0x10;
                    DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0;
                    _ownerPlayerIndex = DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1;
                    if ((_ownerPlayerIndex / 0xc < 0x1e) && (_ownerPlayerIndex % 0xc == 10)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                            (int)((short)DAT_BuildingsState::instance.buildings[iVar7].y), DE::SHCDE::FX_COW_MILK);
                        iVar7 = DAT_CurrentBuildingID::instance;
                    }
                }
                if (DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 == 0x170) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar7].y), DE::SHCDE::FX_MILK_POUR);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
            } else if (bVar2 == 5) {
                if (DAT_BuildingDefinedData::instance
                        .DairyFarmAnimationFrames4[DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2]
                    == 0) {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3 = 0x36;
                    DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 6;
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3
                        = (char)DAT_BuildingDefinedData::instance.DairyFarmAnimationFrames4
                              [DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2]
                        + 0x2f;
                    DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0;
                }
            } else if (bVar2 == 6) {
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite4 = 0x37;
                DAT_BuildingsState::instance.buildings[iVar7].resources[0xb] = 1;
                DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 0;
            } else {
                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite2 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationFrame2 = 0;
                DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite3 = 0;
            }
            goto LAB_00416a00;
        }
        if (DAT_BuildingDefinedData::instance
                .DairyFarmAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock]
            != 0x18) {
            DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1
                = (char)DAT_BuildingDefinedData::instance
                      .DairyFarmAnimationFrames1[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock]
                + 0x37;
            DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0;
            goto LAB_00416a00;
        }
        DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength
            = DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength + 1;
        if (DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength < 0x20)
            goto LAB_00416a00;
        DAT_BuildingsState::instance.buildings[iVar7].renderBlendStrength = 0x20;
        psVar9 = DAT_BuildingsState::instance.buildings[iVar7].workerID + 1;
        DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
        iVar6 = DAT_CurrentBuildingID::instance;
        if (*psVar9 == 0) {
            iVar10 = 0;
            iVar6 = iVar7;
        } else if (DAT_BuildingsState::instance.buildings[iVar7].workerID[2] == 0) {
            iVar10 = 1;
            iVar6 = iVar7;
        } else if (DAT_BuildingsState::instance.buildings[iVar7].workerID[3] == 0) {
            iVar10 = 2;
            iVar6 = iVar7;
        } else {
            iVar4 = 1;
            iVar10 = 0;
            piVar5 = DAT_BuildingsState::instance.buildings[iVar7].workerUID;
            do {
                piVar5 = piVar5 + 1;
                if ((*piVar5 != DAT_UnitsState::instance.units[*psVar9].uid)
                    || (DAT_UnitsState::instance.units[*psVar9].logicalState == Map::Units::ULS_REMOVE)) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[iVar4] = 0;
                    iVar10 = iVar4 + -1;
                    break;
                }
                iVar4 = iVar4 + 1;
                psVar9 = psVar9 + 1;
            } while (iVar4 < 4);
        }
        iVar6 = *(int*)(DAT_BuildingsState::instance.buildings[iVar6].workers + iVar10 * 2 + 8);
        _cow = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(_ownerPlayerIndex, 0,
            (iVar6
                - DAT_ViewportRenderState::instance
                    .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar6]]
                    .addXgetTile)
                * 8,
            (int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar6] * 8),
            (int)(DAT_BuildingsState::instance.buildings[iVar7].terrainHeightUnk), Map::Units::UT_COW);
        iVar7 = DAT_CurrentBuildingID::instance;
        if (!_cow)
            goto LAB_00416a00;
        DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].counter
            = DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].counter + 1;
        DAT_UnitsState::instance.units[_cow].workplaceBuildingUID = DAT_BuildingsState::instance.buildings[iVar7].uid;
        DAT_UnitsState::instance.units[_cow].engineerManningSiegeStateRef_checkType = 0xff;
        DAT_UnitsState::instance.units[_cow].substate = -1;
        uVar3 = DAT_UnitsState::instance.units[_cow].fixedRng;
        DAT_UnitsState::instance.units[_cow].workplaceBuildingID_1 = (short)iVar7;
        DAT_UnitsState::instance.units[_cow].idInTribe = (short)iVar10;
        DAT_UnitsState::instance.units[_cow].state.generic = Map::Units::States::US_JESTER_ROAM_TO;
        DAT_UnitsState::instance.units[_cow].disappearFadeAlphaCountdown = 0x20;
        DAT_UnitsState::instance.units[_cow].facingDirection = (byte)uVar3 & 7;
        DAT_UnitsState::instance.units[_cow].animationCycleNumber = 0;
        sVar8 = (short)_cow;
        if (!iVar10) {
            _ownerPlayerIndex = DAT_UnitsState::instance.units[_cow].uid;
            DAT_BuildingsState::instance.buildings[iVar7].workerID[1] = sVar8;
            DAT_BuildingsState::instance.buildings[iVar7].workerUID[1] = _ownerPlayerIndex;
            DAT_UnitsState::instance.units[_cow].workerIndex = 1;
        LAB_00416d22:
            DAT_UnitsState::instance.units[_cow].buildingID = (short)iVar7;
        } else {
            if (iVar10 == 1) {
                _ownerPlayerIndex = DAT_UnitsState::instance.units[_cow].uid;
                DAT_BuildingsState::instance.buildings[iVar7].workerID[2] = sVar8;
                DAT_BuildingsState::instance.buildings[iVar7].workerUID[2] = _ownerPlayerIndex;
                DAT_UnitsState::instance.units[_cow].workerIndex = 2;
                goto LAB_00416d22;
            }
            if (iVar10 == 2) {
                _ownerPlayerIndex = DAT_UnitsState::instance.units[_cow].uid;
                DAT_BuildingsState::instance.buildings[iVar7].workerID[3] = sVar8;
                DAT_BuildingsState::instance.buildings[iVar7].workerUID[3] = _ownerPlayerIndex;
                DAT_UnitsState::instance.units[_cow].workerIndex = 3;
                goto LAB_00416d22;
            }
        }
        DAT_BuildingsState::instance.buildings[iVar7].dairyProductionStage = 0;
        DAT_BuildingsState::instance.buildings[iVar7].extraAnimationSprite1 = 0;
    LAB_00416a00:
        if (DAT_BuildingsState::instance.field4_0x10) {
            MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::updateBuildingAreaTileGraphics, DAT_BuildingsState::ptr)(iVar7);
            iVar7 = DAT_CurrentBuildingID::instance;
        }
        DAT_BuildingsState::instance.buildings[iVar7].numberOfAnimals = 0;
        _ownerPlayerIndex = (int)DAT_BuildingsState::instance.buildings[iVar7].workerID[1];
        if ((!_ownerPlayerIndex)
            || (DAT_UnitsState::instance.units[_ownerPlayerIndex].uid
                != DAT_BuildingsState::instance.buildings[iVar7].workerUID[1])) {
            DAT_BuildingsState::instance.buildings[iVar7].workerID[1] = 0;
        }
        _ownerPlayerIndex = (int)DAT_BuildingsState::instance.buildings[iVar7].workerID[2];
        if ((!_ownerPlayerIndex)
            || (DAT_UnitsState::instance.units[_ownerPlayerIndex].uid
                != DAT_BuildingsState::instance.buildings[iVar7].workerUID[2])) {
            DAT_BuildingsState::instance.buildings[iVar7].workerID[2] = 0;
        }
        _ownerPlayerIndex = (int)DAT_BuildingsState::instance.buildings[iVar7].workerID[3];
        if ((!_ownerPlayerIndex)
            || (DAT_UnitsState::instance.units[_ownerPlayerIndex].uid
                != DAT_BuildingsState::instance.buildings[iVar7].workerUID[3])) {
            DAT_BuildingsState::instance.buildings[iVar7].workerID[3] = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[iVar7].overlayImageID = 0;
        }
        DAT_BuildingsState::instance.buildings[iVar7].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar7].flagSlot.ownerFlagFrame
            = DAT_BuildingsState::instance.buildings[iVar7].flagSlot.ownerFlagFrame + 1;
        if ((char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar7].flagSlot.ownerFlagFrame / 2]
            < '\x01') {
            DAT_BuildingsState::instance.buildings[iVar7].flagSlot.ownerFlagFrame = 0;
        }
        DAT_BuildingsState::instance.buildings[iVar7].overlayImageID
            = (int)(char)DAT_BuildingDefinedData::instance
                  .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[iVar7].flagSlot.ownerFlagFrame
                      / 2];
    }

}
}
