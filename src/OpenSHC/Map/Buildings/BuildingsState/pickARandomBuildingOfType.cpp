#include "../BuildingsState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AEF0
        int BuildingsState::pickARandomBuildingOfType(int playerID, BuildingType buildingType)
        {
            int count = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].buildingType == buildingType
                    && this->buildings[buildingID].owner == playerID) {
                    ++count;
                }
            }
            if (count > 0) {
                int selection = SEC_RNG::instance.currentNumber2 % count;
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                    if (this->buildings[buildingID].logicalState != 0
                        && this->buildings[buildingID].logicalState != BLS_REMOVE
                        && this->buildings[buildingID].buildingType == buildingType
                        && this->buildings[buildingID].owner == playerID) {
                        --selection;
                        if (selection < 0) {
                            return buildingID;
                        }
                    }
                }
            }
            return 0;
        }

    }
}
}
