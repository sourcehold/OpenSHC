#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Resources::ResourceType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004587A0
    int GameStateStructures::getNextGoodFilteringUnallowed(ResourceType resourceType)
    {
        if (resourceType == OpenSHC::Game::Resources::RT_PITCH) {
            resourceType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
        }
        int index = 0;
        for (; DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] != resourceType; index++) {
        }
        index = index + 1;
        if (DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] == -1) {
            index = 0;
        }
        while (this->mapAndTime.isResourceTradeable[DAT_TroopDefinedData::instance.MarketResourceCycleArray[index]]
            == 0) {
            index = index + 1;
            if (DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] == -1) {
                index = 0;
            }
        }
        return DAT_TroopDefinedData::instance.MarketResourceCycleArray[index];
    }
}
}
