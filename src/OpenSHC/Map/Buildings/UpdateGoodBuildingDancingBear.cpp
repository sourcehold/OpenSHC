#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // renderAnimation = (owner fearFactorLevel >= 3) (signed setge at 0x41973E). Frame table entry read with
    // movsx; <= 0 (jg at 0x41975E) restarts the animation at index 0, frame 1.
    // FUNCTION: STRONGHOLDCRUSADER 0x004196D0
    void Buildings::UpdateGoodBuildingDancingBear()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
            DAT_BuildingsState::ptr)(buildingID, 1);
        OpenSHC::Map::Buildings::Building* bear = &DAT_BuildingsState::instance.buildings[buildingID];
        bear->renderAnimation
            = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel >= 3;
        int frame = (char)DAT_BuildingDefinedData::instance
                        .GoodBuildingDancingBearAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
        if (frame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
    }

}
}
