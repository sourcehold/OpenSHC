#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004140B0
    void Buildings::UpdateTannersWorkshop()
    {
        int animationDone = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        if (((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid
                 + DAT_GameCore::instance.mapTimeInTicks)
                & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingPlacementRotationPreview,
                DAT_TileMapState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = DAT_TileMapState::instance.uiBuildingRotation;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state <= 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX
                = DAT_BuildingDefinedData::instance.SpriteOffsets1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType][0][0]
                + 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY
                = DAT_BuildingDefinedData::instance.SpriteOffsets1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType][1][0]
                + 1;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX
                = DAT_BuildingDefinedData::instance.SpriteOffsets1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType][0][0];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY
                = DAT_BuildingDefinedData::instance.SpriteOffsets1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType][1][0];
        }

        // Most of the animation tables are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
            int const index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
            char const frame = DAT_GameSynchronyState::instance.currentGameMode == 0
                ? (char)DAT_BuildingDefinedData::instance.AnimTannerSolitary[index]
                : (char)DAT_BuildingDefinedData::instance.AnimTanner[index];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                > 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 14
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 26
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 41) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_TANNER_BRUSH1);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 7
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 21
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 33
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 47) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_TANNER_BRUSH2);
                }
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.AnimTannerSolitary2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 12;
                }
            } else {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.AnimTanner2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 12;
                }
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
            char const frame = DAT_BuildingDefinedData::instance
                                   .AnimTanner3[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .animationIndex];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
            char const frame = DAT_BuildingDefinedData::instance
                                   .AnimTanner3[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .animationIndex];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
            char const frame = DAT_BuildingDefinedData::instance
                                   .AnimTanner4[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .animationIndex];
            if (frame <= 0) {
                goto doneWithBlend;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 15
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 30
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 40
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 46)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_TANNER_CUT);
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 25;
                }
            } else {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.TannersWorkshopAnimationFrames2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 25;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                > 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 8) {
            char const frame = (char)DAT_BuildingDefinedData::instance
                                   .AnimTanner5[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                           .animationIndex];
            if (frame <= 0) {
                goto doneWithBlend;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 25;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 9) {
            int const index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
            char const frame = DAT_GameSynchronyState::instance.currentGameMode == 0
                ? (char)DAT_BuildingDefinedData::instance.AnimTannerSolitary4[index]
                : (char)DAT_BuildingDefinedData::instance.AnimTanner6[index];
            if (frame <= 0) {
                animationDone = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 51;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                > 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 10) {
            if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.AnimTanner7
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 51;
                    goto blend;
                }
            }
        doneWithBlend:
            animationDone = 1;
        blend:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
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
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 6;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 8;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 8) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 9;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 9) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 10;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 10) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength > 31) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        }

        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        int const workerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (workerID != 0) {
            if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            } else if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
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
