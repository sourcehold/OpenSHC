#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004156F0
    void Buildings::UpdateInn()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const workerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (workerID == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .flagonsOfAleOrCheeseOrReleaseDogs
                != 0
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field164_0x28a != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        }
        int const visuallyActive
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);

        // InnAnimationFrames* are declared byte, but the original reads them signed
        if (visuallyActive != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                = (char)DAT_BuildingDefinedData::instance.InnAnimationFrames4
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.InnAnimationFrames4[0];
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
            }
            // The original clears the sprite it just animated
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field164_0x28a != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance
                          .InnAnimationFrames3[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                  .extraAnimationFrame1];
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance
                          .InnAnimationFrames2[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                  .extraAnimationFrame1];
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance.InnAnimationFrames2[0];
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
            }
            if (DAT_UnitsState::instance.units[workerID].state.generic
                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = (char)DAT_BuildingDefinedData::instance
                          .InnAnimationFrames1[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                  .extraAnimationFrame2];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = (char)DAT_BuildingDefinedData::instance.InnAnimationFrames1[0];
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive
                    != 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field164_0x28a != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field164_0x28a -= 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field164_0x28a == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnDrunkard, DAT_GameState::ptr)(
                        DAT_CurrentBuildingID::instance);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                    = (char)DAT_BuildingDefinedData::instance
                          .InnAnimationFrames5[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                  .extraAnimationFrame3];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                        = (char)DAT_BuildingDefinedData::instance.InnAnimationFrames5[0];
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive
                    != 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                }
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        }

        // aleTracker counts the ticks towards the next flagon drunk
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagonsOfAleOrCheeseOrReleaseDogs
            > 0) {
            if (workerID != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].aleTracker += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].aleTracker
                    >= DAT_GameState::instance.playerDataArray[owner].aleRate) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].aleTracker = 0;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .flagonsOfAleOrCheeseOrReleaseDogs -= 1;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .flagonsOfAleOrCheeseOrReleaseDogs
                    > 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0] != 0) {
                DAT_GameState::instance.playerDataArray[owner].workingInnsCount += 1;
            }
        }
        DAT_GameState::instance.playerDataArray[owner].countInns += 1;
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
