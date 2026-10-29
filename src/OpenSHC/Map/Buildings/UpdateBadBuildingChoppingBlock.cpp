#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // Every second tick (animationTickCounter > 1, signed jle at 0x4193D4): displayOwnerFlag = fearFactorLevel <= -4 (setle),
    // campgroundVclock steps through BadBuildingChoppingBlockAnimationFrames (signed bytes, jg at 0x41940F) into extraAnimationSprite1.
    // FUNCTION: STRONGHOLDCRUSADER 0x00419370
    void Buildings::UpdateBadBuildingChoppingBlock()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
        int* counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter;
        *counterPtr += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter > 1) {
            int fear = DAT_GameState::instance.playerDataArray[owner].fearFactorLevel;
            DAT_BuildingsState::instance.buildings[buildingID].animationTickCounter = 0;
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = fear <= -4;
            counterPtr = &DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock;
            *counterPtr += 1;
            int frame = (char)DAT_BuildingDefinedData::instance
                            .BadBuildingChoppingBlockAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock];
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = frame;
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 1;
            }
        }
    }

}
}
