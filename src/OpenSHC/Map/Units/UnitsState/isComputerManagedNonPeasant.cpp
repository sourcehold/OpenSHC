#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
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
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_PEASANT) {
                return FALSE;
            }
            return (
                BOOLEnum)(DAT_UnitPropertiesDefinedData::instance.COMPUTER_MANAGED[(short)this->units[unitID].unitType]
                != 0);
        }

    }
}
}
