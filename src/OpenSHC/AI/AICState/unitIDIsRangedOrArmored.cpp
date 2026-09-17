#include "../AICState.func.hpp"

#include "OpenSHC/Game/Skirmish/SkirmishDefinedData.hpp"

#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Skirmish::SkirmishDefinedData;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC8D0
    undefined4 AICState::unitIDIsRangedOrArmored(int unitID)
    {
        int _unitType = DAT_UnitsState::instance.units[unitID].unitType;

        for (int i = 0; i < 7; i++) {
            if (DAT_SkirmishDefinedData::instance.RangedAndArmoredUnits[i] == _unitType) {
                return TRUE;
            }
        }

        return FALSE;
    }
}
}
