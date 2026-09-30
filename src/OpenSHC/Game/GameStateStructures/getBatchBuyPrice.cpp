#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      batch is 5   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458890
    int GameStateStructures::getBatchBuyPrice(undefined4 playerID, int resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice;
    }

}
}
