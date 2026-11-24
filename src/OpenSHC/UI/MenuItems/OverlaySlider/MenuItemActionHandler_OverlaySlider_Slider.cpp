#include "../OverlaySlider.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AA600
        void OverlaySlider::MenuItemActionHandler_OverlaySlider_Slider(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            // a range over 200 gets a slider 1.6 times as long: its first half moves a value in steps of 1/4, the
            // second half in steps of 1
            switch (scrollbarEvent) {
            case 1: {
                int const range = DAT_MenuModalComposition2::instance.sliderMaximum
                    - DAT_MenuModalComposition2::instance.sliderMinimum;
                // stored first and overwritten below, as the original does
                *maxValue = range;
                if (range > 200) {
                    *maxValue = range * 3 / 5 + range;
                    *minValue = 0;
                } else {
                    *minValue = DAT_MenuModalComposition2::instance.sliderMinimum;
                    *maxValue = DAT_MenuModalComposition2::instance.sliderMaximum;
                }
                *currentValue = DAT_MenuModalComposition2::instance.sliderValue;
                return;
            }
            case 2:
            case 3:
                // the slider moved: write the value it stands for
                if (DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum
                    > 200) {
                    DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                    if (*currentValue > *maxValue / 2) {
                        if (DAT_MenuModalComposition2::instance.destination != NULL) {
                            *DAT_MenuModalComposition2::instance.destination = *currentValue
                                - DAT_MenuModalComposition2::instance.sliderMaximum * 3 / 5
                                + DAT_MenuModalComposition2::instance.sliderMinimum;
                            if (*currentValue == *maxValue) {
                                *DAT_MenuModalComposition2::instance.destination
                                    = DAT_MenuModalComposition2::instance.sliderMaximum;
                            }
                            return;
                        }
                        // short operands, for the original's 16-bit subtract and add
                        *DAT_MenuModalComposition2::instance.destination2 = (short)*currentValue
                            - (short)(DAT_MenuModalComposition2::instance.sliderMaximum * 3 / 5)
                            + (short)DAT_MenuModalComposition2::instance.sliderMinimum;
                        if (*currentValue == *maxValue) {
                            *DAT_MenuModalComposition2::instance.destination2
                                = DAT_MenuModalComposition2::instance.sliderMaximum;
                        }
                        return;
                    }
                    if (DAT_MenuModalComposition2::instance.destination != NULL) {
                        *DAT_MenuModalComposition2::instance.destination
                            = *currentValue / 4 + DAT_MenuModalComposition2::instance.sliderMinimum;
                        return;
                    }
                    *DAT_MenuModalComposition2::instance.destination2
                        = *currentValue / 4 + DAT_MenuModalComposition2::instance.sliderMinimum;
                    return;
                }
                DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                if (DAT_MenuModalComposition2::instance.destination != NULL) {
                    *DAT_MenuModalComposition2::instance.destination = *currentValue;
                    return;
                }
                *DAT_MenuModalComposition2::instance.destination2 = *currentValue;
                return;
            case 4:
            case 5:
            case 6:
                return;
            case 7:
                // a click on the track: the step it moves the slider by
                if (DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum
                    > 200) {
                    if (*currentValue > *maxValue / 2) {
                        *currentValue = 1;
                    } else {
                        *currentValue = 4;
                    }
                    return;
                }
                *currentValue = 1;
                return;
            }
        }

    }
}
}
