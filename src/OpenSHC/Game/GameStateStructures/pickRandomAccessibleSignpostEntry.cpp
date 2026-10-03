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
        /*
          four signpost slots are handled per pass, exactly as the original binary does
         */
        for (int slot = 0; slot < 8; slot += 4) {
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
            if ((this->mapAndTime.signpostIDs[slot + 1] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot + 1]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                signpostCount = signpostCount + 1;
                if (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot + 1].tile]]
                    > 10000) {
                    accessibleCount = accessibleCount + 1;
                }
            }
            if ((this->mapAndTime.signpostIDs[slot + 2] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot + 2]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                signpostCount = signpostCount + 1;
                if (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot + 2].tile]]
                    > 10000) {
                    accessibleCount = accessibleCount + 1;
                }
            }
            if ((this->mapAndTime.signpostIDs[slot + 3] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot + 3]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                signpostCount = signpostCount + 1;
                if (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot + 3].tile]]
                    > 10000) {
                    accessibleCount = accessibleCount + 1;
                }
            }
        }
        if (signpostCount <= 1) {
            return 0;
        }
        if (signpostCount == accessibleCount) {
            return (int)SEC_RNG::instance.currentNumber1 % signpostCount;
        }
        if (accessibleCount <= 0) {
            return 0;
        }
        int accessibleIndex = 0;
        for (int slot = 0; slot < 8; slot++) {
            if ((this->mapAndTime.signpostIDs[slot] > 0)
                && (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    == OpenSHC::Map::Buildings::BT_SIGNPOST)
                && (DAT_PathFindingState::instance.zoneSizesArray[(short)DAT_TileMapState::instance
                            .PathConnectionLayer[this->mapAndTime.signpostEntryData[slot].tile]]
                    > 10000)) {
                if (accessibleIndex == (int)SEC_RNG::instance.currentNumber1 % accessibleCount) {
                    return slot;
                }
                accessibleIndex = accessibleIndex + 1;
            }
        }
        return 0;
    }
}
}
