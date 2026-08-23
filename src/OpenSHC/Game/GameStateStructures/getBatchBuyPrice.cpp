#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458890
    int GameStateStructures::getBatchBuyPrice(undefined4 playerID, int resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice;
    }

}
}
