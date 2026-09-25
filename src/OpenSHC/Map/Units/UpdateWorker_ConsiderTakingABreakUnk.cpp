#include "OpenSHC/Map/Units.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053CAC0
    BOOLEnum Units::UpdateWorker_ConsiderTakingABreakUnk(int unitID)
    {
        return MACRO_CALL(OpenSHC::Map::Units_Func::ConsiderHavingABreakNowUnk)(
            unitID, (UnitState)DAT_UnitsState::instance.units[unitID].state.generic);
    }

}
}
