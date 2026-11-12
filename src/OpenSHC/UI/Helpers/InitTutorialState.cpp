#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/INT_00df5554.hpp"
#include "OpenSHC/Globals/INT_00df5564.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00df5598.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC6F0
    void Helpers::InitTutorialState()
    {
        // The main menu's tutorial button calls this once the tutorial map is loaded
        MACRO_CALL(OpenSHC::UI::Helpers_Func::InitTutorialStepTransition)(1);
        DAT_00df555c::instance = DAT_MissionAestheticsDefinedData::instance.TutorialStepActionCount[0];
        DAT_DisableTutorialRestrictions::instance = FALSE;
        DAT_TutorialCurrentStep::instance = 0;
        INT_00df5554::instance = 32;
        DAT_00df5558::instance = 0;
        DAT_00df5560::instance = 0;
        INT_00df5564::instance = 0;
        DAT_00df556c::instance = 36;
        // Where each step starts: two past the previous start, plus the previous step's action count
        int start = 1;
        for (int step = 0; step < countof(INT_ARRAY_00df5598::instance); ++step) {
            ++start;
            INT_ARRAY_00df5598::instance[step] = start;
            start += DAT_MissionAestheticsDefinedData::instance.TutorialStepActionCount[step] + 1;
        }
        MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetTutorialActionTrackers)();
    }

}
}
