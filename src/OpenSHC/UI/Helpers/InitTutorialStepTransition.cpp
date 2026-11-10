#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DWORD_00df5548.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC5F0
    void Helpers::InitTutorialStepTransition(int transition)
    {
        DWORD_00df5548::instance = timeGetTime();
        DAT_00df5540::instance = transition;
        DAT_00df5544::instance = 1;
        if (transition == 1) {
            DAT_00df5544::instance = 31;
        }
    }

}
}
