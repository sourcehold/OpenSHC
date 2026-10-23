#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F5C0
        void BuildingsState::assignWorkerToBuilding(int buildingID, int unitID, int workerIndex)
        {
            this->buildings[buildingID].workerID[workerIndex] = unitID;
            this->buildings[buildingID].workerUID[workerIndex] = DAT_UnitsState::instance.units[unitID].uid;
            DAT_UnitsState::instance.units[unitID].workerIndex = workerIndex;
            DAT_UnitsState::instance.units[unitID].buildingID = buildingID;
        }

    }
}
}
