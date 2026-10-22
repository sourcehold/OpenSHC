#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00456AD0
    int GameStateStructures::pickRandomAccessibleSignpostEntry()
    {
        int signpostCount = 0;
        int accessibleCount = 0;
        for (int slot = 0; slot < 8; ++slot) {
            if (this->mapAndTime.signpostIDs[slot] > 0
                && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == Map::Buildings::BT_SIGNPOST) {
                ++signpostCount;
                if (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot].tile]]
                    > 10000) {
                    ++accessibleCount;
                }
            }
        }
        if (signpostCount <= 1) {
            return 0;
        }
        if (signpostCount == accessibleCount) {
            return SEC_RNG::instance.currentNumber1 % signpostCount;
        }
        if (accessibleCount <= 0) {
            return 0;
        }
        int const randomIndex = SEC_RNG::instance.currentNumber1 % accessibleCount;
        int accessibleIndex = 0;
        for (int slot = 0; slot < 8; ++slot) {
            if (this->mapAndTime.signpostIDs[slot] > 0
                && DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == Map::Buildings::BT_SIGNPOST
                && DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                           .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot].tile]]
                    > 10000) {
                if (accessibleIndex++ == randomIndex) {
                    return slot;
                }
            }
        }
        return 0;
    }

}
}
