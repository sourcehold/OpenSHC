#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458740
    BOOLEnum GameStateStructures::isResourceTypeTradeable(ResourceType resourceType)
    {
        if (resourceType == OpenSHC::Game::Resources::RT_PITCH) {
            resourceType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
        }
        return this->mapAndTime.isResourceTradeable[resourceType] != 0;
    }

}
}
