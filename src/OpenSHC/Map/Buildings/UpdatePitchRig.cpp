#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00410EE0
    void Buildings::UpdatePitchRig()
    {
        DAT_GameState::instance
            .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .countPitchRigs += 1;
        int animationDone = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);

        // PitchRigAnimationFrames2/3 are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_SCOOP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_POUR);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_WATERLAP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 10
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 25) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MUDBUB);
                }
            }
            char const frame
                = (char)DAT_BuildingDefinedData::instance.PitchRigAnimationFrames2
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex < 30) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_SCOOP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_POUR);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_WATERLAP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 10
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 25) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MUDBUB);
                }
            }
            char const frame
                = DAT_BuildingDefinedData::instance.PitchRigAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_SCOOP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_POUR);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PITCH_WATERLAP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 10
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 25) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MUDBUB);
                }
            }
            char const frame
                = (char)DAT_BuildingDefinedData::instance.PitchRigAnimationFrames3
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex >= 40) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex - 40;
            }
        }
        if (animationDone != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength > 31) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
    }

}
}
