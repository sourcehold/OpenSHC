#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B7F0
    int GameStateStructures::getSalesPrice(int playerID, int resourceType)
    {
        int sellAmount
            = MACRO_CALL_MEMBER(GameStateStructures_Func::getSellResourceAmount, this)(playerID, resourceType);
        return (this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5) * sellAmount;
    }

}
}
