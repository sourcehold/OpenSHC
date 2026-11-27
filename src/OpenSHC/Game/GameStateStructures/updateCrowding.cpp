#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // The original walks a pointer to currentPopulation and reaches the other PlayerData fields by their distance
    // from it. Indexing playerDataArray[playerID] instead makes MSVC base the loop on populationCap.
#define PLAYER_FIELD(type, field)                                                                                      \
    (*(type*)((char*)currentPopulation + offsetof(PlayerData, field) - offsetof(PlayerData, currentPopulation)))

    // FUNCTION: STRONGHOLDCRUSADER 0x00458E60
    void GameStateStructures::updateCrowding()
    {
        int* currentPopulation = &this->playerDataArray[1].currentPopulation;
        for (int playerID = 1; playerID != 9; ++playerID) {
            int populationCap = PLAYER_FIELD(int, populationCap);
            int population = PLAYER_FIELD(int, currentPopulation);
            // The pointer advance is written in both exits: with it in the loop header MSVC swaps two registers.
            if (population <= populationCap) {
                PLAYER_FIELD(int, crowding) = 0;
                currentPopulation += sizeof(PlayerData) / sizeof(int);
                continue;
            }
            if (population <= 0) {
                PLAYER_FIELD(int, crowding) = 0;
            } else if (populationCap <= 0) {
                PLAYER_FIELD(int, crowding) = 150;
            } else {
                PLAYER_FIELD(int, crowding) = (population * 100) / populationCap;
            }
            currentPopulation += sizeof(PlayerData) / sizeof(int);
        }
    }

#undef PLAYER_FIELD

}
}
