#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/INT_00df5574.hpp"
#include "OpenSHC/Globals/INT_00df557c.hpp"
#include "OpenSHC/Globals/INT_00df5580.hpp"
#include "OpenSHC/Globals/INT_00df5584.hpp"
#include "OpenSHC/Globals/TUT_RotateMapHappened.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC630
    void Helpers::RecordTutorialPlayerAction(int action)
    {
        if (action == 1) {
            INT_00df5574::instance = 1;
        }
        if (action == 2) {
            ++TUT_RotateMapHappened::instance;
        }
        if (action == 3) {
            ++INT_00df557c::instance;
        }
        if (action == 4) {
            INT_00df5580::instance = 1;
        }
        if (action == 5) {
            if (INT_00df5580::instance == 1) {
                INT_00df5580::instance = 2;
            }
        } else if (action == 17) {
            ++INT_00df5584::instance;
        }
    }

}
}
