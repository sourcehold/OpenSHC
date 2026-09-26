#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422400
        int BuildingsState::findQuarryPileThatIsCloseAndHasMostStone(int playerID, int x, int y, int unitID)
        {
            // Scores the accessible quarry piles of the player by distance and stored stone
            int bestValue = 0;
            int best = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL
                    || this->buildings[i].buildingType != BT_QUARRYSTOCKPILE || this->buildings[i].owner != playerID) {
                    continue;
                }
                int stone = this->buildings[i].resources[OpenSHC::Game::Resources::RT_STONE];
                if (stone <= 0
                    || MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(i, 1)
                        == 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(x, y, (short)this->buildings[i].x, (short)this->buildings[i].y);
                int value = 400 - DAT_DirectionAlgorithmState::instance.distanceHigh;
                if (DAT_UnitsState::instance.units[unitID].field300_0x410 != 0 && stone >= 8) {
                    if (stone > 40) {
                        value += stone;
                    } else {
                        value += stone / 2;
                    }
                }
                if (value >= bestValue) {
                    bestValue = value;
                    best = i;
                }
            }
            return best;
        }

    }
}
}
