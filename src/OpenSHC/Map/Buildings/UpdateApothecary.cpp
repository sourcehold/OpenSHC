#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00415A80
    void Buildings::UpdateApothecary()
    {
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        int const workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
        if (workerID != 0 && DAT_UnitsState::instance.units[workerID].state.generic == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(buildingID);
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .ApothecaryAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
            < 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
            = (char)DAT_BuildingDefinedData::instance
                  .ApothecaryAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        }
    }

}
}
