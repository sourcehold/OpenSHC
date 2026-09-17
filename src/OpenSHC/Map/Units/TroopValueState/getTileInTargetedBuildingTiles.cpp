#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00519960
        BOOLEnum TroopValueState::getTileInTargetedBuildingTiles(int tile)
        {
            // fixme: this function doesn't use this-> (would be not 100% matching!)
            for (int _index = 0; _index < DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize;
                _index++) {
                if (DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray[_index] == tile) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
