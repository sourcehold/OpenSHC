#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;
    using Game::GameMode2;
    using Game::Resources::ResourceType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00412360
    void Buildings::UpdateStockpile()
    {
        int* piVar1;
        int iVar2;
        bool bVar3;
        BOOLEnum BVar4;
        int _owner;
        int _buildingID;
        bool bVar5;
        _buildingID = DAT_CurrentBuildingID::instance;
        _owner = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        bVar3 = false;
        bVar5 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        if (((((bVar5) || (_owner != DAT_GameState::instance.mapAndTime.somePlayerID))
                 && (!((byte)DAT_GameCore::instance.mapTimeInTicks & 3)))
                && ((DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted == 0
                    && (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR))))
            && ((DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                && (DAT_GameState::instance.playerDataArray[_owner].someCountdown01 == 0)))) {
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[2])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_WOOD),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[2];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 2;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[2] = iVar2 + -1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 2;
                *piVar1 = *piVar1 + 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[3])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_HOPS),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[3];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 3;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[3] = iVar2 + -1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 3;
                *piVar1 = *piVar1 + 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[4])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_STONE),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[4];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 4;
                *piVar1 = *piVar1 + 1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 4;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[4] = iVar2 + -1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[6])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_IRON),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[6];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 6;
                *piVar1 = *piVar1 + 1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 6;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[6] = iVar2 + -1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[7])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_PITCH),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[7];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 7;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[7] = iVar2 + -1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 7;
                *piVar1 = *piVar1 + 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[9])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_WHEAT),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[9];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 9;
                *piVar1 = *piVar1 + 1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 9;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[9] = iVar2 + -1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((0 < DAT_GameState::instance.playerDataArray[_owner].startResources[0xe])
                && (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_ALE),
                    BVar4)) {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[0xe];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 0xe;
                *piVar1 = *piVar1 + 1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 0xe;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[0xe] = iVar2 + -1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
                bVar3 = true;
                _buildingID = DAT_CurrentBuildingID::instance;
            }
            if ((DAT_GameState::instance.playerDataArray[_owner].startResources[0x10] <= 0)
                || (BVar4 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::buildingHasSpaceForResource,
                        DAT_BuildingsState::ptr)(_buildingID, Game::Resources::RT_FLOUR),
                    !BVar4)) {
                if (!bVar3) {}
            } else {
                iVar2 = DAT_GameState::instance.playerDataArray[_owner].startResources[0x10];
                piVar1 = DAT_GameState::instance.playerDataArray[_owner].currentResources + 0x10;
                *piVar1 = *piVar1 + 1;
                DAT_GameState::instance.playerDataArray[_owner].startResources[0x10] = iVar2 + -1;
                piVar1 = DAT_BuildingsState::instance.buildings[_buildingID].resources + 0x10;
                *piVar1 = *piVar1 + 1;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                    DAT_BuildingsState::ptr)(_buildingID);
                DAT_GameState::instance.playerDataArray[_owner].hasInitialResourceRecievingStarted = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    _buildingID);
            }
            MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(_owner);
        }
    }

}
}
