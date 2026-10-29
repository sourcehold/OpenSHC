#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // growCounter is a signed short (cmp ax, 0x96; jle at JLE0x00416540). The flag frames are signed (jg).
    // FUNCTION: STRONGHOLDCRUSADER 0x00416540
    void Buildings::UpdateWheatFarm()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].countFarms += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[owner].farmsWithoutWorkers += 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        short* renderPtr = &DAT_BuildingsState::instance.buildings[buildingID].renderAnimation;
        *renderPtr = 0;
        DAT_BuildingsState::instance.buildings[buildingID].growCounter += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].growCounter > 0x96) {
            DAT_BuildingsState::instance.buildings[buildingID].growCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::growWheat, DAT_BuildingsState::ptr)(buildingID);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWheatFieldTileGraphics, DAT_BuildingsState::ptr)(
            buildingID);
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = (char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
    }

}
}