#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF00
    void GameStateStructures::resetSomethingBuildingRelatedForAllPlayers()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            for (int iVar1 = 0; iVar1 < 20; iVar1++) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, this)(
                    playerID, iVar1);
            }
        }
    }

}
}
