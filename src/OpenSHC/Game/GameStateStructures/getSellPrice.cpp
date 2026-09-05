#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458910
    int GameStateStructures::getSellPrice(int playerID, int resourceType, int amount)
    {
        // Preserve division before multiplication, including non-multiples of five.
        return (this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5) * amount;
    }

}
}
