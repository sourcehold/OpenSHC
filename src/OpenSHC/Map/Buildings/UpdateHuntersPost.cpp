#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00423370
    void Buildings::UpdateHuntersPost()
    {
        int animationDone = 0;
        int hunterPresent = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const firstWorkerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (firstWorkerID != 0
            && DAT_UnitsState::instance.units[firstWorkerID].uid
                == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[0]) {
            hunterPresent = 1;
        }
        int const secondWorkerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1];
        if (secondWorkerID != 0
            && DAT_UnitsState::instance.units[secondWorkerID].uid
                == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[1]
            && (DAT_UnitsState::instance.units[secondWorkerID].unitType == OpenSHC::Map::Units::UT_BURNINGMAN
                || DAT_UnitsState::instance.units[secondWorkerID].unitType == OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG
                || DAT_UnitsState::instance.units[secondWorkerID].unitType
                    == OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL)) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].burningWorkerCountdown = 400;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].burningWorkerCountdown > 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].burningWorkerCountdown -= 1;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals == 0
            && hunterPresent != 0
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].burningWorkerCountdown == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 2, 0);
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX != 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY != 0) {
                int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                    0, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_HUNTERDOG);
                if (unitID != 0) {
                    DAT_UnitsState::instance.units[unitID].targetX_2
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX;
                    DAT_UnitsState::instance.units[unitID].targetY_2
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                        DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 1, 0);
                    DAT_UnitsState::instance.units[unitID].workplaceBuildingUID
                        = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] = unitID;
                    DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 = DAT_CurrentBuildingID::instance;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    DAT_UnitsState::instance.units[unitID].substate = -1;
                    DAT_UnitsState::instance.units[unitID].facingDirection = 4;
                    DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 32;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[1]
                        = DAT_UnitsState::instance.units[unitID].uid;
                    DAT_UnitsState::instance.units[unitID].workerIndex = 1;
                    DAT_UnitsState::instance.units[unitID].buildingID = DAT_CurrentBuildingID::instance;
                }
            }
        }

        // HuntersPostAnimationFrames1/3 are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.HuntersPostAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = (16 - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex) * 2;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
                    animationDone = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state >= 1
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state <= 6) {
                if (DAT_BuildingDefinedData::instance.HuntersPostAnimationFrames2
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                    <= 0) {
                    animationDone = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid,
                        OpenSHC::Game::Resources::RT_MEAT, 1, 6, 1);
                } else {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                        && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex
                            == 4) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                            OpenSHC::DE::SHCDE::FX_HUNTER_CUT);
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                        = DAT_BuildingDefinedData::instance.HuntersPostAnimationFrames2
                              [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
                char const frame
                    = (char)DAT_BuildingDefinedData::instance.HuntersPostAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame <= 0) {
                    animationDone = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex * 2;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength >= 32) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 32;
                    animationDone = 1;
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
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 6;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 7) {
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
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 20;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 21;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 22;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 23;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 5) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 24;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT]
            == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 25;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].numberOfAnimals = 0;
        // Faithful to the original, which stores the value it just compared against
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1] = 0;
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
