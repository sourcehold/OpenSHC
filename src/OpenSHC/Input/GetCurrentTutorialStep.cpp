#include "../Input.func.hpp"

#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004BC620
undefined4 Input::GetCurrentTutorialStep() { return DAT_TutorialCurrentStep::instance; }

}
