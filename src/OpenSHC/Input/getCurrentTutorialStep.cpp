#include "OpenSHC/Input.func.hpp"

#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC620
    undefined4 __cdecl OpenSHC::Input::GetCurrentTutorialStep(void) { return DAT_TutorialCurrentStep::instance; }
}
}
