#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // NOTE: batch is 5

    // FUNCTION: STRONGHOLDCRUSADER 0x00458890
    int GameStateStructures::getBatchBuyPrice(undefined4 playerID, int resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice;
    }

}
}
