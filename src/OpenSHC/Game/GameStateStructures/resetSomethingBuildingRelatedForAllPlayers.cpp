#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF00
    void GameStateStructures::resetSomethingBuildingRelatedForAllPlayers()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            for (int buildingCategory = 0; buildingCategory < 0x14; buildingCategory++) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, this)(
                    playerID, buildingCategory);
            }
        }
    }
}
}
