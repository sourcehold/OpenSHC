#include "../AICState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD070
    BOOLEnum AICState::checkTribeActivityPercentages(int tribeID, BOOLEnum ignoreShooting, BOOLEnum includeMoving)
    {
        if (includeMoving != FALSE && DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk > 10) {
            return TRUE;
        }
        if (DAT_TribesState::instance.tribes[tribeID].percentageShootingUnk > 10 && ignoreShooting != TRUE) {
            return TRUE;
        }
        return DAT_TribesState::instance.tribes[tribeID].percentageAttackingUnk > 10;
    }

}
}
