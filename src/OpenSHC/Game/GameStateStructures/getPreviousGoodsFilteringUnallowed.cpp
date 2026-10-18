#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458820
    int GameStateStructures::getPreviousGoodsFilteringUnallowed(ResourceType resourceType)
    {
        if (resourceType == Resources::RT_PITCH) {
            resourceType = Resources::RT_PARTIALPITCH;
        }
        int index = 0;
        for (; DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] != resourceType; ++index) {}
        --index;
        if (index < 0) {
            index = 19;
        }
        while (
            this->mapAndTime.isResourceTradeable[DAT_TroopDefinedData::instance.MarketResourceCycleArray[index]] == 0) {
            --index;
            if (index < 0) {
                index = 19;
            }
        }
        return DAT_TroopDefinedData::instance.MarketResourceCycleArray[index];
    }

}
}
