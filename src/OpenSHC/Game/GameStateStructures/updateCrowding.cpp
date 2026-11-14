#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458E60
    void GameStateStructures::updateCrowding()
    {
        for (int playerID = 1; playerID != 9; ++playerID) {
            int populationCap = this->playerDataArray[playerID].populationCap;
            int currentPopulation = this->playerDataArray[playerID].currentPopulation;
            int crowding;
            if (currentPopulation <= populationCap) {
                crowding = 0;
            } else if (currentPopulation <= 0) {
                crowding = 0;
            } else if (populationCap <= 0) {
                crowding = 150;
            } else {
                crowding = (currentPopulation * 100) / populationCap;
            }
            this->playerDataArray[playerID].crowding = crowding;
        }
    }

}
}
