#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F8A0
        void BuildingsState::applySnoozedStateBasedOnPlayerData()
        {
            // Applies the snoozed settings of the owners and resets the production of buildings whose state changed
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL) {
                    continue;
                }
                if (this->buildings[i].buildingType >= 91) {
                    this->buildings[i].sleeping = false;
                    continue;
                }
                bool snoozed = DAT_GameState::instance.playerDataArray[this->buildings[i].owner]
                                   .snoozedBuildings[this->buildings[i].buildingType];
                if (this->buildings[i].sleeping == snoozed) {
                    continue;
                }
                this->buildings[i].sleeping = snoozed;
                this->buildings[i].currentEmployeeCount = 0;
                this->buildings[i].animationIndex = 0;
                this->buildings[i].renderAnimation = 0;
                // state/field117_0x11a and killingPitField/field119_0x11e are cleared as ints
                *(int*)&this->buildings[i].state = 0;
                *(int*)&this->buildings[i].killingPitField = 0;
                for (int r = 0; r < 25; ++r) {
                    this->buildings[i].resources[r] = 0;
                }
                for (int w = 0; w < 4; ++w) {
                    this->buildings[i].workerUID[w] = 0;
                    this->buildings[i].workerID[w] = 0;
                }
            }
        }

    }
}
}
