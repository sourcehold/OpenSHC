#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TacticalPowersHelpTextDisplayBool.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004D9D90
void UI::TacticalPowersFill()

{
    if ((DAT_TacticalPowersHelpTextDisplayBool::instance != '\0')
        && (DAT_MissionDefinedData::instance.field39_0x1370 = DAT_MissionDefinedData::instance.field39_0x1370 + -1,
            DAT_MissionDefinedData::instance.field39_0x1370 == 0)) {
        DAT_TacticalPowersHelpTextDisplayBool::instance = '\0';
    }
}

}
