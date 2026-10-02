#include "../OverlaySlider.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AA600
        void OverlaySlider::MenuItemActionHandler_OverlaySlider_Slider(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            switch (param_2) {
            case 1:
                iVar1 = DAT_MenuModalComposition2::instance.sliderMaximum
                    - DAT_MenuModalComposition2::instance.sliderMinimum;
                *maxValue = iVar1;
                if (200 < iVar1) {
                    *maxValue = (iVar1 * 3) / 5 + iVar1;
                    *minValue = 0;
                    *currentValue = DAT_MenuModalComposition2::instance.sliderValue;
                }
                *minValue = DAT_MenuModalComposition2::instance.sliderMinimum;
                *maxValue = DAT_MenuModalComposition2::instance.sliderMaximum;
                *currentValue = DAT_MenuModalComposition2::instance.sliderValue;
                return;
            case 2:
            case 3:
                if ((int)(DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum)
                    < 0xc9) {
                    DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                    if (DAT_MenuModalComposition2::instance.destination != (int*)0x0) {
                        *DAT_MenuModalComposition2::instance.destination = *currentValue;
                    }
                    *DAT_MenuModalComposition2::instance.destination2 = (short)*currentValue;
                }
                DAT_MenuModalComposition2::instance.sliderValue = *currentValue;
                iVar1 = *currentValue;
                if (iVar1 <= *maxValue / 2) {
                    iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2)
                        + DAT_MenuModalComposition2::instance.sliderMinimum;
                    if (DAT_MenuModalComposition2::instance.destination != (int*)0x0) {
                        *DAT_MenuModalComposition2::instance.destination = iVar1;
                    }
                    *DAT_MenuModalComposition2::instance.destination2 = (short)iVar1;
                }
                if (DAT_MenuModalComposition2::instance.destination == (int*)0x0) {
                    iVar1 = DAT_MenuModalComposition2::instance.sliderMaximum * 3;
                    *DAT_MenuModalComposition2::instance.destination2
                        = ((short)*currentValue
                              - (((short)(iVar1 / 5) + (short)(iVar1 >> 0x1f))
                                  - (short)((longlong)iVar1 * 0x66666667 >> 0x3f)))
                        + (short)DAT_MenuModalComposition2::instance.sliderMinimum;
                    if (*currentValue == *maxValue) {
                        *DAT_MenuModalComposition2::instance.destination2
                            = (short)DAT_MenuModalComposition2::instance.sliderMaximum;
                    }
                } else {
                    *DAT_MenuModalComposition2::instance.destination
                        = (iVar1 - (int)(DAT_MenuModalComposition2::instance.sliderMaximum * 3) / 5)
                        + DAT_MenuModalComposition2::instance.sliderMinimum;
                    if (*currentValue == *maxValue) {
                        *DAT_MenuModalComposition2::instance.destination
                            = DAT_MenuModalComposition2::instance.sliderMaximum;
                    }
                }
                return;
            case 4:
            case 5:
            case 6:
                return;
            case 7:
                if (200 < (int)(DAT_MenuModalComposition2::instance.sliderMaximum
                        - DAT_MenuModalComposition2::instance.sliderMinimum)) {
                    *currentValue = (*currentValue <= *maxValue / 2) ? 4 : 1;
                }
                *currentValue = 1;
                return;
            default:
                break;
            }
        }

    }
}
}
