#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00419190
    void Buildings::UpdateBadBuildingDungeon()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk = 0;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
            DAT_BuildingsState::ptr)(buildingID, 1);
        int const fear = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel;
        if (fear <= -4) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            if (fear <= -2) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
            = (char)DAT_BuildingDefinedData::instance
                  .BadBuildingDungeonAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
    }

}
}
