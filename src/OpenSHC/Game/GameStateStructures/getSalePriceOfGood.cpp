#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004588F0
    int GameStateStructures::getSalePriceOfGood(ResourceType resourceType)
    {
        return this->mapAndTime.buyAndSalesPriceArray[resourceType].salesPrice / 5;
    }

}
}
