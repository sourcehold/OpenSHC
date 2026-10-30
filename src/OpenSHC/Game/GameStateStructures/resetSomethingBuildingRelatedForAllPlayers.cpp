#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF00
    void GameStateStructures::resetSomethingBuildingRelatedForAllPlayers()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            for (int buildingCategory = 0; buildingCategory < 20; ++buildingCategory) {
                MACRO_CALL_MEMBER(GameStateStructures_Func::validateBuildingCategoryReference, this)(
                    playerID, buildingCategory);
            }
        }
    }

}
}
