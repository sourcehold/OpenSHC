#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F540
        BOOLEnum BuildingsState::hasWorker(int buildingID, int workerSlot)
        {
            int unitID = this->buildings[buildingID].workerID[workerSlot];
            if (unitID <= 0) {
                return FALSE;
            }
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_REMOVE
                && DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                && DAT_UnitsState::instance.units[unitID].buildingID == buildingID) {
                return (BOOLEnum)(DAT_UnitsState::instance.units[unitID].uid
                    == this->buildings[buildingID].workerUID[workerSlot]);
            }
            return FALSE;
        }

    }
}
}
