#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004588D0
    int GameStateStructures::getBuyPriceForOneUnit(int param_1)
    {
        return this->mapAndTime.buyAndSalesPriceArray[param_1].buyPrice / 5;
    }

}
}
