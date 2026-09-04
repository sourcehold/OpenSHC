#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement1.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::AttackInfoSubArrayElement1;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AC80
        BOOLEnum TroopValueState::attackInfoHasHigh2Building(int buildingID)
        {
            for (int i = 0; i < 1000; i++) {
                // fixme: this function doesn't use this-> (would be not 100% matching!)
                if (buildingID == DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].buildingID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
