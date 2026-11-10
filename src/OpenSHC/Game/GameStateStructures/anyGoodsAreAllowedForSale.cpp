#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458760
    BOOLEnum GameStateStructures::anyGoodsAreAllowedForSale()
    {
        // measured: scoping index to the for-init costs the match (100.0 -> 95.5), because the zeroing xors
        // follow declaration order and swap against the original. Both locals stay here.
        int index = 0;
        int allowedCount = 0;
        for (; DAT_TroopDefinedData::instance.MarketResourceCycleArray[index] != -1; ++index) {
            if (this->mapAndTime.isResourceTradeable[DAT_TroopDefinedData::instance.MarketResourceCycleArray[index]]) {
                ++allowedCount;
            }
        }
        if (allowedCount >= 2) {
            return TRUE;
        }
        return FALSE;
    }

}
}
