#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F540
        BOOLEnum BuildingsState::hasWorker(int buildingID, int workerSlot)
        {
            int const unitID = this->buildings[buildingID].workerID[workerSlot];
            if (unitID <= 0) {
                return FALSE;
            }
            if (DAT_UnitsState::instance.units[unitID].logicalState == Units::ULS_REMOVE) {
                return FALSE;
            }
            if (DAT_UnitsState::instance.units[unitID].logicalState == Units::ULS_INVISIBLE) {
                return FALSE;
            }
            if (DAT_UnitsState::instance.units[unitID].buildingID != buildingID) {
                return FALSE;
            }
            return DAT_UnitsState::instance.units[unitID].uid == this->buildings[buildingID].workerUID[workerSlot];
        }

    }
}
}
