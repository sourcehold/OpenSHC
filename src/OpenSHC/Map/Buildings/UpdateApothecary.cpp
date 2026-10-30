#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
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

    // Active only while the worker is in unit state 2 (cmp word, 2 at 0x415AD8). The frame table is signed and only a
    // negative entry wraps (cmp byte, 0; jge at 0x415B26); updateBuildingGraphicsLayer gets the cached id (push edi).
    // FUNCTION: STRONGHOLDCRUSADER 0x00415A80
    void Buildings::UpdateApothecary()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
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
        short* incrementPtr = &DAT_BuildingsState::instance.buildings[buildingID].animationIncrement;
        *incrementPtr = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .ApothecaryAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
            < 0) {
            short* indexPtr = &DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            *indexPtr = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].animationCycleCompleted = 0;
        }
        int* framePtr = &DAT_BuildingsState::instance.buildings[buildingID].animationFrame;
        *framePtr = (char)DAT_BuildingDefinedData::instance
                        .ApothecaryAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if ((char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID
                = (char)DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
    }

}
}
