#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004588F0
    int GameStateStructures::getSalePriceOfGood(ResourceType param_1)
    {
        return this->mapAndTime.buyAndSalesPriceArray[param_1].salesPrice / 5;
    }

}
}
