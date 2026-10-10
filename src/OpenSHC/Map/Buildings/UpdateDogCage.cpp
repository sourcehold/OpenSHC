#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x00420A30
    void Buildings::UpdateDogCage()
    {
        short* psVar1;
        byte bVar2;
        int _unitID;
        int iVar3;
        int iVar4;
        int _buildingID;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        _buildingID = DAT_CurrentBuildingID::instance;
        psVar1 = &DAT_GameState::instance
                      .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                      .dogCageCount;
        *psVar1 = *psVar1 + 1;
        _unitID = (int)DAT_BuildingsState::instance.buildings[_buildingID].insideUnitID1;
        iVar3 = 0;
        iVar4 = 0;
        if ((_unitID)
            && (DAT_BuildingsState::instance.buildings[_buildingID].insideUnitUID1
                == DAT_UnitsState::instance.units[_unitID].uid)) {
            iVar4 = 1;
            if (DAT_UnitsState::instance.units[_unitID].state.generic == Map::Units::States::USDU_WAITING_IN_CAGE) {
                iVar3 = 1;
                iVar4 = 1;
            }
        }
        _unitID = (int)DAT_BuildingsState::instance.buildings[_buildingID].insideUnitID2;
        if (_unitID
            && DAT_BuildingsState::instance.buildings[_buildingID].insideUnitUID2
                == DAT_UnitsState::instance.units[_unitID].uid
            && (iVar4 = iVar4 + 1,
                DAT_UnitsState::instance.units[_unitID].state.generic == Map::Units::States::USDU_WAITING_IN_CAGE)) {
            iVar3 = iVar3 + 1;
        }
        _unitID = (int)DAT_BuildingsState::instance.buildings[_buildingID].insideUnitID3;
        if (_unitID
            && DAT_BuildingsState::instance.buildings[_buildingID].insideUnitUID3
                == DAT_UnitsState::instance.units[_unitID].uid
            && (iVar4 = iVar4 + 1,
                DAT_UnitsState::instance.units[_unitID].state.generic == Map::Units::States::USDU_WAITING_IN_CAGE)) {
            iVar3 = iVar3 + 1;
        }
        _unitID = (int)DAT_BuildingsState::instance.buildings[_buildingID].insideUnitID4;
        if (_unitID
            && DAT_BuildingsState::instance.buildings[_buildingID].insideUnitUID4
                == DAT_UnitsState::instance.units[_unitID].uid
            && (iVar4 = iVar4 + 1,
                DAT_UnitsState::instance.units[_unitID].state.generic == Map::Units::States::USDU_WAITING_IN_CAGE)) {
            iVar3 = iVar3 + 1;
        }
        if (!iVar4) {
            DAT_BuildingsState::instance.buildings[_buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[_buildingID].displayOwnerFlag = 0;
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                _buildingID);
        } else {
            if (!iVar3) {
                DAT_BuildingsState::instance.buildings[_buildingID].renderAnimation = 0;
                DAT_BuildingsState::instance.buildings[_buildingID].displayOwnerFlag = 0;
            }
            DAT_BuildingsState::instance.buildings[_buildingID].displayOwnerFlag = 0;
            DAT_BuildingsState::instance.buildings[_buildingID].renderBlendStrength = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter,
                DAT_BuildingsState::ptr)(_buildingID, 1);
            DAT_BuildingsState::instance.buildings[_buildingID].renderAnimation = 1;
            bVar2 = DAT_BuildingDefinedData::instance
                        .DogCageAnimationFrames[DAT_BuildingsState::instance.buildings[_buildingID].animationIndex];
            DAT_BuildingsState::instance.buildings[_buildingID].animationFrame = (int)(char)bVar2;
            if ((char)bVar2 < 1) {
                DAT_BuildingsState::instance.buildings[_buildingID].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[_buildingID].animationFrame = 1;
            }
        }
    }

}
}
