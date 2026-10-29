#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00419670
    void Buildings::UpdateGoodBuildingShrine()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        OpenSHC::Map::Buildings::Building* shrine = &DAT_BuildingsState::instance.buildings[buildingID];
        shrine->renderAnimation = 0;
        shrine->displayOwnerFlag = 0;
        shrine->someX
            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
        shrine->someY
            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
    }

}
}
