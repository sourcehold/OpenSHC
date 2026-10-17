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
            int currentPopulation = this->playerDataArray[playerID].currentPopulation;
            int populationCap = this->playerDataArray[playerID].populationCap;
            if (currentPopulation <= populationCap) {
                this->playerDataArray[playerID].crowding = 0;
            } else if (currentPopulation <= 0) {
                this->playerDataArray[playerID].crowding = 0;
            } else if (populationCap <= 0) {
                this->playerDataArray[playerID].crowding = 150;
            } else {
                this->playerDataArray[playerID].crowding = (currentPopulation * 100) / populationCap;
            }
        }
    }
}
}
