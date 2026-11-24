#include "../MenuHandlerState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4CD0
    void MenuHandlerState::computeBuildMenuTransitionShift()
    {
        // the time is read before the test for 100, as the original does
        int const now = timeGetTime();
        if (this->buildMenuTransitionProgress_0x38 == 100) {
            this->isBuildMenuTransitioning_0x18 = FALSE;
            return;
        }
        // progress in percent of the transition's duration, kept between 1 and 100
        int const progress
            = (now - this->buildMenuTransitionStartTime_0x30) * 100 / this->buildMenuTransitionDuration_0x34;
        this->buildMenuTransitionProgress_0x38 = progress;
        if (progress > 100) {
            this->buildMenuTransitionProgress_0x38 = 100;
        } else if (progress < 1) {
            this->buildMenuTransitionProgress_0x38 = 1;
        }
        // the menu slides 376 pixels; its items slide with it, jump to the other side half way and slide back
        // each arm computes the shift itself and the items' shift reads it back: one local for it loses the match
        if (this->buildMenuTransitionDirection_0x2c > 0) {
            this->buildMenuBackgroundLeftShift_0x24 = this->buildMenuTransitionProgress_0x38 * 376 / 100;
            if (this->buildMenuTransitionProgress_0x38 >= 50) {
                this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24 - 376;
            } else {
                this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24;
            }
        } else {
            this->buildMenuBackgroundLeftShift_0x24 = 376 - this->buildMenuTransitionProgress_0x38 * 376 / 100;
            if (this->buildMenuTransitionProgress_0x38 < 50) {
                this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24 - 376;
            } else {
                this->buildMenuItemsLeftShift_0x28 = this->buildMenuBackgroundLeftShift_0x24;
            }
        }
    }

}
}
