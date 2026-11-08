#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F1E0
        void BuildingsState::setSignpostDataForBuildings()
        {
            for (int buildingID = 0; buildingID < 2000; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].buildingType == BT_SIGNPOST) {
                    bool alreadyListed = false;
                    for (int slot = 0; slot < 8; ++slot) {
                        if (DAT_GameState::instance.mapAndTime.signpostIDs[slot] == buildingID) {
                            alreadyListed = true;
                            break;
                        }
                    }
                    if (!alreadyListed) {
                        for (int slot = 0; slot < 8; ++slot) {
                            if (DAT_GameState::instance.mapAndTime.signpostIDs[slot] <= 0) {
                                DAT_GameState::instance.mapAndTime.signpostIDs[slot] = buildingID;
                                break;
                            }
                        }
                    }
                }
            }
        }

    }
}
}
