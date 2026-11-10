#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004588F0
    int GameStateStructures::getSalePriceOfGood(ResourceType resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5;
    }

}
}
