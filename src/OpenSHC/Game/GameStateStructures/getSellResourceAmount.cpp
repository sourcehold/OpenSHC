#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458940
    int GameStateStructures::getSellResourceAmount(int playerID, int resourceType)
    {
        int stock = this->playerDataArray[playerID].currentResources[resourceType];
        if (stock < 5) {
            return stock;
        }
        if (stock < 50) {
            return 5;
        }
        if (stock < 100) {
            return 10;
        }
        if (stock < 200) {
            return 20;
        }
        return 50;
    }

}
}
