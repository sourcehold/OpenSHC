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

    // FUNCTION: STRONGHOLDCRUSADER 0x004138D0
    void Buildings::UpdatePoleturnersWorkshop()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int animationDone = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        DAT_GameState::instance.playerDataArray[owner].countFletchersPoleturners += 1;
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

        // The animation tables are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].producedItemTypeNext
            == OpenSHC::Game::Resources::RT_SPEAR) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 7
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 39
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 74
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 106
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 140
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 175)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_POLE_TURN);
                }
                char frame;
                if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                    frame = (char)DAT_BuildingDefinedData::instance
                                .field78_0x54cc[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .animationIndex];
                } else {
                    frame
                        = (char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames4
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                }
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 94;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                    < 30) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames5
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 94;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
            }
            if (animationDone != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                }
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].producedItemTypeNext
            == OpenSHC::Game::Resources::RT_PIKE) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                    < 30) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    == 61) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength += 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1
                || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 2
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 48)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_POLE_GRIND);
                }
                char frame;
                if (DAT_GameSynchronyState::instance.currentGameMode == 0) {
                    frame = (char)DAT_BuildingDefinedData::instance
                                .field75_0x53bc[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .animationIndex];
                } else {
                    frame
                        = (char)DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames2
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                }
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 61;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex < 32) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength -= 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                char const frame
                    = DAT_BuildingDefinedData::instance.PoleturnersWorkshopAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 61;
                }
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
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength > 31) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        }

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
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
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
