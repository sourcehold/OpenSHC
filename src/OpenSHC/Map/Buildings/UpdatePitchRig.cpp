#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00410EE0
    void Buildings::UpdatePitchRig()
    {
        int* piVar1;
        short* psVar2;
        byte bVar3;
        short sVar4;
        int iVar5;
        int iVar6;
        bool bVar7;
        iVar6 = DAT_CurrentBuildingID::instance;
        piVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .countPitchRigs;
        *piVar1 = *piVar1 + 1;
        bVar7 = false;
        DAT_BuildingsState::instance.buildings[iVar6].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[iVar6].workers[0] != 0);
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar6);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
        sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state;
        if (!sVar4) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y),
                        DE::SHCDE::FX_PITCH_SCOOP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x14) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y),
                        DE::SHCDE::FX_PITCH_POUR);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y),
                        DE::SHCDE::FX_PITCH_WATERLAP);
                }
                sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
                if ((sVar4 == 10) || (sVar4 == 0x19)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y),
                        DE::SHCDE::FX_MUDBUB);
                }
            }
            iVar5 = DAT_CurrentBuildingID::instance;
            iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
            bVar3 = DAT_BuildingDefinedData::instance.PitchRigAnimationFrames2
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if ('\0' < (char)bVar3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    = (int)(char)bVar3;
            }
            bVar7 = (char)bVar3 < '\x01';
            sVar4 = DAT_BuildingsState::instance.buildings[iVar5].animationIndex;
            if (!sVar4) {
                DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength = 0x1f;
            } else {
                if (0x1d < sVar4)
                    goto LAB_004112c0;
                psVar2 = &DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength;
                *psVar2 = *psVar2 + -1;
            }
        LAB_004112c7:
            if (bVar7) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar6) = 0;
                sVar4 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8);
                if (!sVar4) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8) = 1;
                } else if (sVar4 == 1) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8) = 2;
                } else if (sVar4 == 2) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8) = 3;
                } else if (sVar4 == 3) {
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8) = 4;
                } else if (sVar4 == 4) {
                    piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCount + iVar6);
                    *piVar1 = *piVar1 + 1;
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationCycleCompleted + iVar6) = 1;
                    *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -8) = 0;
                }
            }
        } else {
            if (sVar4 == 1 || sVar4 == 2 || sVar4 == 3) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_SCOOP);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                        == 0x14) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_POUR);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_WATERLAP);
                    }
                    sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
                    if ((sVar4 == 10) || (sVar4 == 0x19)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_MUDBUB);
                    }
                }
                iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
                if ((char)DAT_BuildingDefinedData::instance.PitchRigAnimationFrames1
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                    <= '\0') {
                    bVar7 = true;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                        = (int)(char)DAT_BuildingDefinedData::instance.PitchRigAnimationFrames1
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                }
            LAB_004112c0:
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x62) = 0;
                goto LAB_004112c7;
            }
            if (sVar4 == 4) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_SCOOP);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                        == 0x14) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_POUR);
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_PITCH_WATERLAP);
                    }
                    sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
                    if ((sVar4 == 10) || (sVar4 == 0x19)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            (int)((
                                int)((short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y)),
                            DE::SHCDE::FX_MUDBUB);
                    }
                }
                iVar5 = DAT_CurrentBuildingID::instance;
                iVar6 = DAT_CurrentBuildingID::instance * 0x32c;
                bVar3 = DAT_BuildingDefinedData::instance.PitchRigAnimationFrames3
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if ('\0' < (char)bVar3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                        = (int)(char)bVar3;
                }
                bVar7 = (char)bVar3 < '\x01';
                sVar4 = DAT_BuildingsState::instance.buildings[iVar5].animationIndex;
                if (0x27 < sVar4) {
                    DAT_BuildingsState::instance.buildings[iVar5].renderBlendStrength = sVar4 + -0x28;
                }
                goto LAB_004112c7;
            }
        }
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationIncrement + iVar6) != 0) {
            sVar4 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x62);
            if (0x1f < sVar4) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x62) = 0x1f;
                goto LAB_00411360;
            }
            if (-1 < sVar4)
                goto LAB_00411360;
        }
        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar6 + -0x62) = 0;
    LAB_00411360:
        bVar7 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraAnimationSprite1 + iVar6) = 0;
        if (bVar7) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar6) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar6) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) / 2]
            <= '\0') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].overlayImageID + iVar6)
            = (int)(char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                  [*(int*)((int)&DAT_BuildingsState::instance.buildings[0].flagSlot.ownerFlagFrame + iVar6) / 2];
    }

}
}
