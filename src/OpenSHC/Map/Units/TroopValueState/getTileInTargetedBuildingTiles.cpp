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
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArraySize; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.targetedBuildingTilesArray[i] == tile) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
