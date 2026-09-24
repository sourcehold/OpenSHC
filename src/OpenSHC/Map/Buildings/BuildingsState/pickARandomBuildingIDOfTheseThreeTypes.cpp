#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040AFB0
        int BuildingsState::pickARandomBuildingIDOfTheseThreeTypes(
            int playerID, BuildingType buildingType1, BuildingType buildingType2, BuildingType buildingType3)
        {
            int count = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && (this->buildings[i].buildingType == buildingType1
                        || this->buildings[i].buildingType == buildingType2
                        || this->buildings[i].buildingType == buildingType3)
                    && this->buildings[i].owner == playerID) {
                    ++count;
                }
            }
            if (count <= 0) {
                return 0;
            }

            int pick = SEC_RNG::instance.currentNumber2 % count;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && (this->buildings[i].buildingType == buildingType1
                        || this->buildings[i].buildingType == buildingType2
                        || this->buildings[i].buildingType == buildingType3)
                    && this->buildings[i].owner == playerID && --pick < 0) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
