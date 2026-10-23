#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B7F0
    int GameStateStructures::getSalesPrice(int playerID, int resourceType)
    {
        return (this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5)
            * MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellResourceAmount, this)(
                playerID, resourceType);
    }

}
}
