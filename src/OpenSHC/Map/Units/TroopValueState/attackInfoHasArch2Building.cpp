#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051ACB0
        BOOLEnum TroopValueState::attackInfoHasArch2Building(int buildingID)
        {
            for (int i = 0; i < 1000; ++i) {
                if (buildingID == DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[i].buildingID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
