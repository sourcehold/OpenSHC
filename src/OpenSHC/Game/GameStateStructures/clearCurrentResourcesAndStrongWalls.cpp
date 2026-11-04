#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00455D90
    void GameStateStructures::clearCurrentResourcesAndStrongWalls()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            for (int resourceType = 0; resourceType < 25; ++resourceType) {
                this->playerDataArray[playerID].currentResources[resourceType] = 0;
            }
        }
        DAT_GameState::instance.mapAndTime.skirmishStrongWalls = 0;
        DAT_GameState::instance.mapAndTime.skirmishAlliances = 0;
    }

}
}
