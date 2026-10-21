#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BB30
        undefined4 BuildingsState::addResourceToStockpile(int buildingID, int buildingUID, ResourceType resourceType,
            int amount, int maxCapacity, int recomputeResources)
        {
            int const owner = this->buildings[buildingID].owner;
            int const newAmount = this->buildings[buildingID].resources[resourceType] + amount;
            if (this->buildings[buildingID].uid != buildingUID) {
                return 0;
            }
            if (maxCapacity == 0) {
                this->buildings[buildingID].resources[resourceType] = 0;
                return 0;
            }
            if (newAmount < 0) {
                return 0;
            }
            if (newAmount > maxCapacity) {
                return 0;
            }
            if (recomputeResources == 0) {
                return 1;
            }
            this->buildings[buildingID].resources[resourceType] = newAmount;
            int const buildingType = this->buildings[buildingID].buildingType;
            if (buildingType >= BT_STOCKPILE && (buildingType <= BT_ARMORY || buildingType == BT_GRANARY)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[resourceType] += amount;
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType, this)(
                (BuildingType)this->buildings[buildingID].buildingType, 600,
                DAT_GameSynchronyState::instance.currentPlayerSlotID);
            MACRO_CALL_MEMBER(BuildingsState_Func::computeResourceSumForBuilding, this)(buildingID);
            MACRO_CALL_MEMBER(BuildingsState_Func::countPlayerResources, this)(owner);
            MACRO_CALL_MEMBER(TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
            return 1;
        }

    }
}
}
