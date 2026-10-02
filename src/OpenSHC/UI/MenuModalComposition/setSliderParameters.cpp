#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace UI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AA480
    void MenuModalComposition::setSliderParameters(
        int minimum, int maximum, int value, undefined* destination, void* callbackFunction)
    {
        int _range;
        int _lower;
        _range = maximum - minimum;
        this->sliderMinimum = minimum;
        this->sliderMaximum = maximum;
        if (_range < 200) {
            this->sliderValue = value;
        } else {
            _lower = value - minimum;
            if (_range / 5 < _lower) {
                this->sliderValue = (_range * 3) / 5 + _lower;
            } else {
                this->sliderValue = _lower * 4;
            }
            if (value == maximum) {
                this->sliderValue = ((_range * 3) / 5 - minimum) + maximum;
            }
        }
        this->destination = (int*)destination;
        this->destination2 = (short*)0x0;
        Menu_OverlaySlider::instance.one = 1;
        this->textGroup = -1;
        this->textIndex = -1;
        this->sliderCallbackFunction = callbackFunction;
    }

}
}
