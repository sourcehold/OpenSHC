#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using Resources::ResourceType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458760
    BOOLEnum GameStateStructures::anyGoodsAreAllowedForSale()
    {
        int index = 0;
        int allowedCount = 0;
        while (DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] != -1) {
            if (this->mapAndTime.isResourceTradeable[DAT_TroopDefinedData::instance.MarketResourceCycleArray[index]]
                != 0) {
                ++allowedCount;
            }
            ++index;
        }
        if (allowedCount >= 2) {
            return TRUE;
        }
        return FALSE;
    }

}
}
