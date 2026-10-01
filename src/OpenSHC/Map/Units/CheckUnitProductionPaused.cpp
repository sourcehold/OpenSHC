#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530D50
    BOOLEnum Units::CheckUnitProductionPaused(int unitID)
    {
        return DAT_UnitsState::instance.units[unitID].field166_0x2fe == 1;
    }

}
}
