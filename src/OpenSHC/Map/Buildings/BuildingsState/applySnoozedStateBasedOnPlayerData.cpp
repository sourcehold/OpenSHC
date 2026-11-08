#include "../BuildingsState.func.hpp"

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
                // type is a reference so the test and the index share one load (a value moves the loop
                // anchor to sleeping), and owner is an int local read twice so its row offset is live across the
                // sleeping test, which is what puts it in esi and type in edi as in the original
                BuildingTypeShort const& type = this->buildings[i].buildingType;
                if (type >= 91) {
                    this->buildings[i].sleeping = false;
                    continue;
                }
                int const owner = this->buildings[i].owner;
                if (this->buildings[i].sleeping
                    == DAT_GameState::instance.playerDataArray[owner].snoozedBuildings[type]) {
                    continue;
                }
                this->buildings[i].sleeping = DAT_GameState::instance.playerDataArray[owner].snoozedBuildings[type];
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
