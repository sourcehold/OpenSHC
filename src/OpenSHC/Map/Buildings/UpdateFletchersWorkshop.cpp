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

    // FUNCTION: STRONGHOLDCRUSADER 0x00412D50
    void Buildings::UpdateFletchersWorkshop()
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
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
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

        // Matching note: the bow and crossbow arms of state 0 share the frame store and the index check; the
        // original keeps the crossbow copy and the bow arm jumps into it.
        int shownFrame;
        // The animation tables are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].producedItemTypeNext
            == OpenSHC::Game::Resources::RT_BOW) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                    && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 8
                        || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 58)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_FLETCH_LONG);
                }
                char frame;
                if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                    frame
                        = (char)DAT_BuildingDefinedData::instance.FletcherWorkshopAnimationCycle
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                } else {
                    frame = (char)DAT_BuildingDefinedData::instance
                                .field43_0x430c[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .animationIndex];
                }
                if (frame <= 0) {
                    animationDone = 1;
                    goto checkIndex;
                }
                shownFrame = frame;
                goto storeFrame;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                    animationDone = 1;
                } else {
                    char const frame
                        = DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames1
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                    if (frame <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                    }
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
            }
        } else {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                char frame;
                if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                    frame = (char)DAT_BuildingDefinedData::instance
                                .field46_0x4674[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .animationIndex];
                } else {
                    frame = (char)DAT_BuildingDefinedData::instance
                                .field45_0x44e4[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .animationIndex];
                }
                if (frame <= 0) {
                    animationDone = 1;
                    goto checkIndex;
                }
                shownFrame = frame + 36;
            storeFrame:
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = shownFrame;
            checkIndex:
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
                if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                    animationDone = 1;
                } else {
                    char const frame
                        = DAT_BuildingDefinedData::instance.FletchersWorkshopAnimationFrames2
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                    if (frame <= 0) {
                        animationDone = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                            = frame + 36;
                    }
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex;
            }
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
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength > 31) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 31;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        }

        int const workerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (workerID != 0) {
            if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
            } else if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
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
