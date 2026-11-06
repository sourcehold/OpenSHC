#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00412360
    void Buildings::UpdateStockpile()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode != 0
            && owner == DAT_GameState::instance.mapAndTime.somePlayerID) {
            return;
        }
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) != 0) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted != 0) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
            || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[owner].someCountdown01 != 0) {
            return;
        }

        // Hand out one unit of each starting resource the stockpile has room for
        int resourceGiven = 0;
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_WOOD] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_WOOD)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_WOOD] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_WOOD] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_WOOD] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_HOPS] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_HOPS)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_HOPS] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_HOPS] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_HOPS] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_STONE] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_STONE)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_STONE] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_STONE] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_STONE] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_IRON] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_IRON)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_IRON] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_IRON] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_IRON] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_PITCH] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_PITCH)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_PITCH] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_PITCH] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_PITCH] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_WHEAT] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_WHEAT)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_WHEAT] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_WHEAT] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_WHEAT] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_ALE] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_ALE)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_ALE] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_ALE] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_ALE] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_FLOUR] > 0
            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_FLOUR)) {
            DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_FLOUR] += 1;
            DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_FLOUR] -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_FLOUR] += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
            DAT_GameState::instance.playerDataArray[owner].hasInitialResourceRecievingStarted = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            resourceGiven = 1;
        }
        if (resourceGiven != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(owner);
        }
    }

}
}
