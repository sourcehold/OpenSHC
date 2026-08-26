#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004188C0
    void Buildings::UpdatePlacedSiegeTower()
    {
        int iVar1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefID;
        if ((iVar1 == 0)
            || (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefUID
                != DAT_UnitsState::instance.units[iVar1].uid)) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].logicalState
                = OpenSHC::Map::Buildings::BLS_REMOVE;
        }
    }

}
}
