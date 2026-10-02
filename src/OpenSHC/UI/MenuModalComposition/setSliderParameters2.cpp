#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA540
    void MenuModalComposition::setSliderParameters2(
        dword minimum, dword maximum, dword value, dword destination, undefined* callbackFunction)
    {
        int iVar1;
        int iVar2;
        iVar1 = maximum - minimum;
        this->sliderMinimum = minimum;
        this->sliderMaximum = maximum;
        if (iVar1 < 0xc9) {
            this->sliderValue = value;
        } else {
            iVar2 = value - minimum;
            if (iVar1 / 5 < iVar2) {
                this->sliderValue = (iVar1 * 3) / 5 + iVar2;
            } else {
                this->sliderValue = iVar2 * 4;
            }
            if (value == maximum) {
                this->sliderValue = ((iVar1 * 3) / 5 - minimum) + maximum;
            }
        }
        this->destination2 = (short*)destination;
        this->destination = (int*)0x0;
        Menu_OverlaySlider::instance.one = 1;
        this->textGroup = -1;
        this->textIndex = -1;
        this->sliderCallbackFunction = callbackFunction;
    }

}
}
