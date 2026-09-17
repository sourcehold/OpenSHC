#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A3F0
    void Version::UpgradeSolitaryMapBuildingField3()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            for (int _buildingID = 1; _buildingID < 2000; _buildingID++) {
                if (DAT_BuildingsState::instance.buildings[_buildingID].logicalState != ((BuildingLogicalState)0)) {
                    DAT_BuildingsState::instance.buildings[_buildingID].playerColorUnk = 0;
                }
            }
        }
    }

}
}
