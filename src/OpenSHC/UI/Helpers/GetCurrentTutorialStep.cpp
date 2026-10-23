#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BC620
        undefined4 __cdecl GetCurrentTutorialStep() { return DAT_TutorialCurrentStep::instance; }

    }
}
}
