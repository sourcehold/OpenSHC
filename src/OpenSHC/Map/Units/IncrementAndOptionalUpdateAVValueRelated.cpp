#include "../Units.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530B40
    void Units::IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV)
    {
        DAT_UnitsState::instance.units[unitID].workTimers[DAT_UnitsState::instance.units[unitID].working] += 1;
        // zeroed before the early return, as the original does (after it: quick_diff 0.9811 -> 0.9057)
        int activeTimerCount = 0;
        if (!updateAV) {
            return;
        }
        DAT_UnitsState::instance.units[unitID].av = 0;
        for (int i = 0; i < countof(DAT_UnitsState::instance.units[unitID].workTimers); ++i) {
            DAT_UnitsState::instance.units[unitID].av += DAT_UnitsState::instance.units[unitID].workTimers[i];
            if (DAT_UnitsState::instance.units[unitID].workTimers[i] > 0) {
                ++activeTimerCount;
            }
        }
        if (activeTimerCount > 0) {
            DAT_UnitsState::instance.units[unitID].av /= activeTimerCount;
        }
        DAT_UnitsState::instance.units[unitID].working += 1;
        if (DAT_UnitsState::instance.units[unitID].working
            >= countof(DAT_UnitsState::instance.units[unitID].workTimers)) {
            DAT_UnitsState::instance.units[unitID].working = 0;
        }
        DAT_UnitsState::instance.units[unitID].workTimers[DAT_UnitsState::instance.units[unitID].working] = 0;
    }

}
}
