#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458700
    int GameStateStructures::findNextPlayerWithMarketplace(int playerID)
    {
        for (int nextPlayerID = playerID + 1; nextPlayerID < 9; ++nextPlayerID) {
            if (this->playerDataArray[nextPlayerID].marketplace.id > 0) {
                return nextPlayerID;
            }
        }
        return 0;
    }

}
}
