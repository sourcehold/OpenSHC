#include "../UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F0A0
        int UnitsState::checkUnitHasPropertyBasedOnUnitType(int unitID, int property)
        {
            return DAT_UnitPropertiesDefinedData::instance.UnitClimbStateFlags[property][this->units[unitID].unitType];
        }

    }
}
}
