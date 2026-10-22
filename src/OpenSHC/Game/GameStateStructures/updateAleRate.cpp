#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458D50
    void GameStateStructures::updateAleRate()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].keep.id > 0 && this->playerDataArray[playerID].campground.id > 0) {
                this->playerDataArray[playerID].aleRate = 36;
            }
        }
    }

}
}
