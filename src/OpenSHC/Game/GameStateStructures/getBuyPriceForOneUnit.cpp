#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004588D0
    int GameStateStructures::getBuyPriceForOneUnit(int resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].buyPrice / 5;
    }

}
}
