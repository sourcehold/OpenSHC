#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004588A0
    int GameStateStructures::getBuyPrice(undefined4 playerID, int resourceType, int amount)
    {
        return (this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice / 5) * amount;
    }

}
}
