#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00416630
    void Buildings::UpdateHopsFarm()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].countFarms += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[owner].farmsWithoutWorkers += 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].growCounter += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].growCounter > 400) {
            DAT_BuildingsState::instance.buildings[buildingID].growCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::growHops, DAT_BuildingsState::ptr)(
                buildingID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateHopsFieldTileGraphics,
                DAT_BuildingsState::ptr)(buildingID);
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
