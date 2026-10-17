#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AE70
    void GameStateStructures::resetBuildingsCurrentIndexCounter()
    {
        for (int playerID = 0; playerID < 9; playerID++) {
            this->first500BuildingsCurrentIndexCounter[playerID] = 0;
        }
    }

}
}
