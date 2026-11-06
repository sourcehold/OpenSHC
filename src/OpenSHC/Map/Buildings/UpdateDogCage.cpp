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
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00420A30
    void Buildings::UpdateDogCage()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        DAT_GameState::instance
            .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .dogCageCount += 1;
        int unitCount = 0;
        int dogCount = 0;
        for (int i = 0; i < 4; ++i) {
            int const unitID = DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[i];
            if (unitID != 0
                && DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[i]
                    == DAT_UnitsState::instance.units[unitID].uid) {
                ++unitCount;
                // Unit state 210 has no UnitState constant.
                if (DAT_UnitsState::instance.units[unitID].state.generic == 210) {
                    ++dogCount;
                }
            }
        }
        if (unitCount != 0) {
            if (dogCount != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
                DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                    DAT_BuildingsState::ptr)(buildingID, 1);
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .DogCageAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
                }
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
                DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                buildingID);
        }
    }

}
}
