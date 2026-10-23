#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530B40
    void Units::IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV)
    {
        // workTimer, workRelatedA, workRelatedB and workRelatedC are four timers, working is the current index
        (&DAT_UnitsState::instance.units[unitID].workTimer)[DAT_UnitsState::instance.units[unitID].working] += 1;
        int count = 0;
        if (updateAV == FALSE) {
            return;
        }
        DAT_UnitsState::instance.units[unitID].av = 0;
        for (int i = 0; i < 4; ++i) {
            DAT_UnitsState::instance.units[unitID].av += (&DAT_UnitsState::instance.units[unitID].workTimer)[i];
            if ((&DAT_UnitsState::instance.units[unitID].workTimer)[i] > 0) {
                ++count;
            }
        }
        if (count > 0) {
            DAT_UnitsState::instance.units[unitID].av /= count;
        }
        DAT_UnitsState::instance.units[unitID].working += 1;
        if (DAT_UnitsState::instance.units[unitID].working >= 4) {
            DAT_UnitsState::instance.units[unitID].working = 0;
        }
        (&DAT_UnitsState::instance.units[unitID].workTimer)[DAT_UnitsState::instance.units[unitID].working] = 0;
    }

}
}
