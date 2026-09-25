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
        BOOLEnum UnitsState::isComputerManagedNonPeasant(int unitID)
        {
            // the unit type is loaded zero-extended but used as a signed short afterwards
            short const unitType = (ushort)this->units[unitID].unitType;
            if (unitType == OpenSHC::Map::Units::UT_PEASANT) {
                return FALSE;
            }
            return DAT_UnitPropertiesDefinedData::instance.COMPUTER_MANAGED[unitType] != 0;
        }

    }
}
}
