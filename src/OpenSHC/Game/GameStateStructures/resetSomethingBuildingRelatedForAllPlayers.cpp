#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF00
    void GameStateStructures::resetSomethingBuildingRelatedForAllPlayers()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            for (int category = 0; category < 20; ++category) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, this)(
                    playerID, category);
            }
        }
    }

}
}
