#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053A020
    BOOLEnum Units::CurrentUnitHasHealer()
    {
        for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
            if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                && DAT_UnitsState::instance.units[i].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_HEALER) {
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
