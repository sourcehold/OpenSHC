#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00df5588.hpp"
#include "OpenSHC/Globals/DAT_00df558c.hpp"
#include "OpenSHC/Globals/DAT_00df5590.hpp"
#include "OpenSHC/Globals/INT_00df5574.hpp"
#include "OpenSHC/Globals/INT_00df557c.hpp"
#include "OpenSHC/Globals/INT_00df5580.hpp"
#include "OpenSHC/Globals/INT_00df5584.hpp"
#include "OpenSHC/Globals/TUT_RotateMapHappened.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC6C0
    void Helpers::ResetTutorialActionTrackers()
    {
        INT_00df5574::instance = 0;
        TUT_RotateMapHappened::instance = 0;
        INT_00df557c::instance = 0;
        INT_00df5580::instance = 0;
        INT_00df5584::instance = 0;
        DAT_00df5588::instance = 0;
        DAT_00df558c::instance = 0;
        DAT_00df5590::instance = 0;
    }

}
}
