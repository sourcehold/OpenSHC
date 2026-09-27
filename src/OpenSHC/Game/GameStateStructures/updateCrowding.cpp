#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458E60
    void GameStateStructures::updateCrowding()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            if (this->playerDataArray[playerID].currentPopulation <= this->playerDataArray[playerID].populationCap) {
                this->playerDataArray[playerID].crowding = 0;
            } else if (this->playerDataArray[playerID].currentPopulation <= 0) {
                this->playerDataArray[playerID].crowding = 0;
            } else if (this->playerDataArray[playerID].populationCap <= 0) {
                this->playerDataArray[playerID].crowding = 150;
            } else {
                this->playerDataArray[playerID].crowding = (this->playerDataArray[playerID].currentPopulation * 100)
                    / this->playerDataArray[playerID].populationCap;
            }
        }
    }
}
}
