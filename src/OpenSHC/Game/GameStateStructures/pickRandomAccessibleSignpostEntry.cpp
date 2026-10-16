#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456AD0
    int GameStateStructures::pickRandomAccessibleSignpostEntry()
    {
        int signpostCount = 0;
        int accessibleCount = 0;
        for (int slot = 0; slot < 8; slot++) {
            if ((this->mapAndTime.signpostIDs[slot] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                signpostCount = signpostCount + 1;
                if (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot].tile]]
                    > 10000) {
                    accessibleCount = accessibleCount + 1;
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
        int randomIndex = SEC_RNG::instance.currentNumber1 % accessibleCount;
        int accessibleIndex = 0;
        for (int slot = 0; slot < 8; slot++) {
            if ((this->mapAndTime.signpostIDs[slot] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)
                && (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot].tile]]
                    > 10000)) {
                if (accessibleIndex++ == randomIndex) {
                    return slot;
                }
            }
        }
        return 0;
    }
}
}
