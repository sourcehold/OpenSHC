#include "../ScrollingHandler.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/ScrollDirection.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468AD0
    void ScrollingHandler::handleScrolling()
    {
        int interval = this->scrollAccelerationInterval;
        int maxDistance = (int)this->scrollDistanceLimit * 2 / 3;
        // the held keys scroll too, while no dialog is open
        if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
            if (this->rightKeyDown_0x18) {
                this->scrollRight = TRUE;
            }
            if (this->leftKeyDown_0x1c) {
                this->scrollLeft = TRUE;
            }
            if (this->upKeyDown_0x24) {
                this->scrollUp = TRUE;
            }
            if (this->downKeyDown_0x20) {
                this->scrollDown = TRUE;
            }
        }
        if (this->scrollUp) {
            if (this->scrollLeft) {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_UP_LEFT;
            } else if (this->scrollRight) {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_UP_RIGHT;
            } else {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_UP;
            }
        } else if (this->scrollDown) {
            if (this->scrollLeft) {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN_LEFT;
            } else if (this->scrollRight) {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN_RIGHT;
            } else {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN;
            }
        } else if (this->scrollLeft) {
            this->scrollDirection_0x4 = OpenSHC::UI::SD_LEFT;
        } else if (this->scrollRight) {
            this->scrollDirection_0x4 = OpenSHC::UI::SD_RIGHT;
        } else {
            this->scrollDirection_0x4 = OpenSHC::UI::SD_NONE;
        }
        // set here and tested below: as one test with the no-direction block in it, the match is lost
        if (this->scrollDirection_0x4 != OpenSHC::UI::SD_NONE) {
            this->isScrolling_0x0 = TRUE;
        } else {
            this->isScrolling_0x0 = FALSE;
        }
        // no direction: back to the minimum distance; the stop time and the scrolling time are both now
        if (!this->isScrolling_0x0) {
            this->scrollDistanceBase = this->scrollDistanceMin;
            DWORD const now = timeGetTime();
            this->scrollDown = FALSE;
            this->scrollUp = FALSE;
            this->scrollRight = FALSE;
            this->scrollLeft = FALSE;
            this->timeOfLastNotScroll_0x40 = now;
            this->timeScrolling_0x44 = now;
            return;
        }
        // fast: the interval less a third, the maximum at 133%; slow: the interval plus a half, half the maximum
        switch (this->scrollSpeedSetting_0x38) {
        case OpenSHC::UI::SS_FAST:
            interval -= interval / 3;
            maxDistance = maxDistance * 133 / 100;
            break;
        case OpenSHC::UI::SS_SLOW:
            interval += interval / 2;
            maxDistance /= 2;
            break;
        }
        // the longer the scrolling lasts, the further a step goes, up to the maximum
        this->timeScrolling_0x44 = timeGetTime() - this->timeOfLastNotScroll_0x40;
        this->scrollDistanceBase = this->timeScrolling_0x44 / interval;
        if (this->scrollDistanceBase > maxDistance) {
            this->scrollDistanceBase = maxDistance;
        }
        this->scrollDown = FALSE;
        this->scrollUp = FALSE;
        this->scrollRight = FALSE;
        this->scrollLeft = FALSE;
    }

}
}
