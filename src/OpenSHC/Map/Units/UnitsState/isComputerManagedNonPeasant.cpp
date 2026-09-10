#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530080
        BOOLEnum UnitsState::isComputerManagedNonPeasant(int param_1)
        {
            // fixme: UnitType is loaded as an unsigned short in this function (movzx), but cast to a signed version on
            // the stack for use later.
            short UVar1 = (unsigned short)this->units[param_1].unitType;
            if (UVar1 == OpenSHC::Map::Units::UT_PEASANT) {
                return FALSE;
            }
            return DAT_UnitPropertiesDefinedData::instance.COMPUTER_MANAGED[UVar1] != 0;
        }

    }
}
}
