#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/MissionWinDefeatBannerDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C560
    void Init::CreateMissionWinDefeatBannerDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            MissionWinDefeatBannerDisplayElement::ptr)(DE::SHCDE::OST_MISSION_FINISHED, 400, 30, 0,
            UI::DisplayElements_Func::RenderMissionWinDefeatBannerDisplayElement::get(), UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
