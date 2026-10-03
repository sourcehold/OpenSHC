#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00455D90
    void GameStateStructures::clearCurrentResourcesAndStrongWalls()
    {
        /*
          the resource stores are written out one by one, exactly as the original binary does
         */
        for (int playerID = 1; playerID < 9; playerID++) {
            this->playerDataArray[playerID].currentResources[0] = 0;
            this->playerDataArray[playerID].currentResources[1] = 0;
            this->playerDataArray[playerID].currentResources[2] = 0;
            this->playerDataArray[playerID].currentResources[3] = 0;
            this->playerDataArray[playerID].currentResources[4] = 0;
            this->playerDataArray[playerID].currentResources[5] = 0;
            this->playerDataArray[playerID].currentResources[6] = 0;
            this->playerDataArray[playerID].currentResources[7] = 0;
            this->playerDataArray[playerID].currentResources[8] = 0;
            this->playerDataArray[playerID].currentResources[9] = 0;
            this->playerDataArray[playerID].currentResources[10] = 0;
            this->playerDataArray[playerID].currentResources[11] = 0;
            this->playerDataArray[playerID].currentResources[12] = 0;
            this->playerDataArray[playerID].currentResources[13] = 0;
            this->playerDataArray[playerID].currentResources[14] = 0;
            this->playerDataArray[playerID].currentResources[15] = 0;
            this->playerDataArray[playerID].currentResources[16] = 0;
            this->playerDataArray[playerID].currentResources[17] = 0;
            this->playerDataArray[playerID].currentResources[18] = 0;
            this->playerDataArray[playerID].currentResources[19] = 0;
            this->playerDataArray[playerID].currentResources[20] = 0;
            this->playerDataArray[playerID].currentResources[21] = 0;
            this->playerDataArray[playerID].currentResources[22] = 0;
            this->playerDataArray[playerID].currentResources[23] = 0;
            this->playerDataArray[playerID].currentResources[24] = 0;
        }
        DAT_GameState::instance.mapAndTime.skirmishStrongWalls = 0;
        DAT_GameState::instance.mapAndTime.skirmishAlliances = 0;
    }
}
}
