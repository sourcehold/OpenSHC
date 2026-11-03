#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00422400
        int BuildingsState::findQuarryPileThatIsCloseAndHasMostStone(int playerID, int x, int y, int unitID)
        {
            int bestScore = 0;
            int bestBuildingID = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != BLS_NORMAL
                    || this->buildings[buildingID].buildingType != BT_QUARRYSTOCKPILE
                    || this->buildings[buildingID].owner != playerID) {
                    continue;
                }
                int const stone = this->buildings[buildingID].resources[Game::Resources::RT_STONE];
                if (stone <= 0
                    || MACRO_CALL_MEMBER(BuildingsState_Func::buildingIsAccessible, this)(buildingID, 1) == 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    x, y, this->buildings[buildingID].x, this->buildings[buildingID].y);
                int score = 400 - DAT_DirectionAlgorithmState::instance.distanceHigh;
                if (DAT_UnitsState::instance.units[unitID].field300_0x410 != 0 && stone >= 8) {
                    if (stone > 40) {
                        score += stone;
                    } else {
                        score += stone / 2;
                    }
                }
                if (score >= bestScore) {
                    bestScore = score;
                    bestBuildingID = buildingID;
                }
            }
            return bestBuildingID;
        }

    }
}
}
