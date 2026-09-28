#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;

    /*
      returns stable where the horse was taken from?   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459930
    int GameStateStructures::linkageBetweenHorseUnitAndStableUnk(int playerID, int unitID)
    {
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
            if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState != ((BuildingLogicalState)0))
                && (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                    != OpenSHC::Map::Buildings::BLS_REMOVE)
                && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_STABLES)
                && (DAT_BuildingsState::instance.buildings[buildingID].owner == playerID)
                && ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals
                    > DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField)) {
                this->playerDataArray[playerID].availableHorses
                    = this->playerDataArray[playerID].availableHorses - 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits,
                    DAT_BuildingsState::ptr)(buildingID);
                for (int tetherSlot = 0; tetherSlot < 4; tetherSlot++) {
                    if ((&DAT_BuildingsState::instance.buildings[buildingID].insideUnitID1)[tetherSlot] == 0) {
                        (&DAT_BuildingsState::instance.buildings[buildingID].insideUnitID1)[tetherSlot]
                            = (short)unitID;
                        (&DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID1)[tetherSlot]
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
