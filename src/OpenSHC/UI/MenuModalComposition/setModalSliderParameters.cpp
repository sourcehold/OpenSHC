#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedWinCondition.hpp"
#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA930
    void MenuModalComposition::setModalSliderParameters(
        int param_1, int param_2, dword param_3, dword param_4, undefined* param_5, undefined* param_6)
    {
        this->textGroup = param_1;
        this->textIndex = param_2;
        this->mbr_0x64 = param_3;
        this->sliderValue = param_4;
        this->destination = (int*)param_5;
        Menu_OverlaySlider::instance.one = 1;
        this->sliderCallbackFunction = param_6;
        MenuModal_UnusedWinCondition::instance.height = param_3 * 0x19;
    }

}
}
