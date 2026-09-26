#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B090
        int BuildingsState::pickARandomPositiveFearFactorBuilding(int playerID)
        {
            int count = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && this->buildings[i].owner == playerID
                    && (this->buildings[i].buildingType == BT_MAYPOLE || this->buildings[i].buildingType == BT_GARDEN
                        || this->buildings[i].buildingType == BT_STATUE || this->buildings[i].buildingType == BT_SHRINE
                        || this->buildings[i].buildingType == BT_DANCINGBEAR
                        || this->buildings[i].buildingType == BT_POND || this->buildings[i].buildingType == BT_WELL
                        || this->buildings[i].buildingType == BT_BEEHIVE)) {
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
                    && this->buildings[i].owner == playerID
                    && (this->buildings[i].buildingType == BT_MAYPOLE || this->buildings[i].buildingType == BT_GARDEN
                        || this->buildings[i].buildingType == BT_STATUE || this->buildings[i].buildingType == BT_SHRINE
                        || this->buildings[i].buildingType == BT_DANCINGBEAR
                        || this->buildings[i].buildingType == BT_POND || this->buildings[i].buildingType == BT_WELL
                        || this->buildings[i].buildingType == BT_BEEHIVE)
                    && --pick < 0) {
                    return i;
                }
            }
            return 0;
        }

    }
}
}
