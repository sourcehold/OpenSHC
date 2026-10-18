#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace Game {

    using Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458740
    BOOLEnum GameStateStructures::isResourceTypeTradeable(ResourceType resourceType)
    {
        if (resourceType == Resources::RT_PITCH) {
            resourceType = Resources::RT_PARTIALPITCH;
        }
        return (uint)(this->mapAndTime.isResourceTradeable[resourceType] != 0);
    }

}
}
