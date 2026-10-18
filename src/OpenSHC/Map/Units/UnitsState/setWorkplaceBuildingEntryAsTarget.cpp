#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005343F0
        undefined4 UnitsState::setWorkplaceBuildingEntryAsTarget(int unitID, int entryAngleUnk)
        {
            int _buildingID = this->units[unitID].workplaceBuildingID_1;
            if (DAT_BuildingsState::instance.buildings[_buildingID].uid == this->units[unitID].workplaceBuildingUID) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(_buildingID, entryAngleUnk)
                    != 0) {
                    this->units[unitID].targetX_2 = DAT_BuildingsState::instance.buildings[_buildingID].buildingEntryX;
                    this->units[unitID].targetY_2 = DAT_BuildingsState::instance.buildings[_buildingID].buildingEntryY;
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
