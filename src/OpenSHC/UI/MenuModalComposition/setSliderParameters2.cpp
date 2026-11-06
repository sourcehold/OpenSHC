#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AA540
    void MenuModalComposition::setSliderParameters2(
        dword minimum, dword maximum, dword value, dword destination, undefined* callbackFunction)
    {
        int const range = maximum - minimum;
        this->sliderMinimum = minimum;
        this->sliderMaximum = maximum;
        if (200 < range) {
            // ranges wider than 200 are compressed: the lowest fifth of the values takes 4 slider steps each
            int const offset = value - minimum;
            // stored first and overwritten below, as the original does
            this->sliderValue = offset;
            if (offset > range / 5) {
                this->sliderValue = range * 3 / 5 + offset;
            } else {
                this->sliderValue = offset * 4;
            }
            if (value == maximum) {
                this->sliderValue = range * 3 / 5 - minimum + maximum;
            }
        } else {
            this->sliderValue = value;
        }
        this->destination2 = (short*)destination;
        this->destination = NULL;
        Menu_OverlaySlider::instance.one = 1;
        this->textGroup = -1;
        this->textIndex = -1;
        this->sliderCallbackFunction = callbackFunction;
    }

}
}
