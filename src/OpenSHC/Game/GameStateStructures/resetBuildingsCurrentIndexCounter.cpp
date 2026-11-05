#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AE70
    void GameStateStructures::resetBuildingsCurrentIndexCounter()
    {
        for (int playerID = 0; playerID < 9; ++playerID) {
            this->first500BuildingsCurrentIndexCounter[playerID] = 0;
        }
    }

}
}
