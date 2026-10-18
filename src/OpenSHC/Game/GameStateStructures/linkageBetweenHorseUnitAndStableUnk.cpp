#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingType;

    // NOTE: returns stable where the horse was taken from?

    // FUNCTION: STRONGHOLDCRUSADER 0x00459930
    int GameStateStructures::linkageBetweenHorseUnitAndStableUnk(int playerID, int unitID)
    {
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0
                && DAT_BuildingsState::instance.buildings[buildingID].logicalState != Map::Buildings::BLS_REMOVE
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_STABLES
                && DAT_BuildingsState::instance.buildings[buildingID].owner == playerID
                && (char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals
                    > DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField) {
                --this->playerDataArray[playerID].availableHorses;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits,
                    DAT_BuildingsState::ptr)(buildingID);
                for (int tetherSlot = 0; tetherSlot < 4; ++tetherSlot) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[tetherSlot] == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[tetherSlot] = (short)unitID;
                        DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[tetherSlot]
                            = DAT_UnitsState::instance.units[unitID].uid;
                        DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField
                            = DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField + 1;
                        return buildingID;
                    }
                }
                return buildingID;
            }
        }
        return 0;
    }

}
}
