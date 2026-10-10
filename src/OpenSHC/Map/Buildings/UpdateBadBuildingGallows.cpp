#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00418530
    void Buildings::UpdateBadBuildingGallows()
    {
        byte bVar1;
        int sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
            buildingID, 1);
        uint uVar3 = DAT_GameState::instance.playerDataArray[sVar2].fearFactorLevel;
        if ((int)uVar3 < -2) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            if (0x7fffffff < uVar3) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                goto LAB_004185ad;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
    LAB_004185ad:
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = -0x23;
        DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = -0x6d;
        bVar1
            = DAT_BuildingDefinedData::instance
                  .BadBuildingGallowsAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = (int)(char)bVar1;
        if ((char)bVar1 < 1) {
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
    }

}
}
