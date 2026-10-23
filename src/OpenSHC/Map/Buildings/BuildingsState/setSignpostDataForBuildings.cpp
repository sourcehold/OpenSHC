#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F1E0
        void BuildingsState::setSignpostDataForBuildings()
        {
            // Registers every signpost that is not known yet in the first free signpost slot
            for (int i = 0; i < 2000; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].buildingType != BT_SIGNPOST) {
                    continue;
                }
                bool alreadyKnown = false;
                for (int s = 0; s < 8; ++s) {
                    if (DAT_GameState::instance.mapAndTime.signpostIDs[s] == i) {
                        alreadyKnown = true;
                        break;
                    }
                }
                if (alreadyKnown) {
                    continue;
                }
                for (int s = 0; s < 8; ++s) {
                    if (DAT_GameState::instance.mapAndTime.signpostIDs[s] <= 0) {
                        DAT_GameState::instance.mapAndTime.signpostIDs[s] = i;
                        break;
                    }
                }
            }
        }

    }
}
}
