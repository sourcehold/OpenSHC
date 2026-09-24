#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F090
        void BuildingsState::harmAppleFarmTreesOfPlayer(int param_1)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].owner != param_1
                    || this->buildings[i].buildingType != BT_APPLEFARM) {
                    continue;
                }
                for (int t = 0; t < 8; ++t) {
                    short tree = DAT_TileMapState::instance.OrganismLayer[(&this->buildings[i].tileRef1)[t]];
                    DAT_LandscapeState::instance.trees[tree].stage = 4;
                    DAT_LandscapeState::instance.trees[tree].stageTracker = -1200;
                }
            }
        }

    }
}
}
