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

    // Animated while fearFactorLevel <= -3 (setle at 0x419301); BadBuildingStretchingRackAnimationFrames entries are signed bytes
    // (movsx, jg at 0x419321).
    // FUNCTION: STRONGHOLDCRUSADER 0x00419290
    void Buildings::UpdateBadBuildingStretchingRack()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
            DAT_BuildingsState::ptr)(buildingID, 1);
        short* renderPtr = &DAT_BuildingsState::instance.buildings[buildingID].renderAnimation;
        *renderPtr = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel <= -3;
        int frame = (char)DAT_BuildingDefinedData::instance
                        .BadBuildingStretchingRackAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
        if (frame <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
    }

}
}
