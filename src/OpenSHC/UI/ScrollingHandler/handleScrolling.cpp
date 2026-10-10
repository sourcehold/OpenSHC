#include "../ScrollingHandler.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/ScrollDirection.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {

    using UI::ScrollDirection;
    using UI::ScrollSpeed;
    using UI::Enums::MenuModalType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00468AD0
    void ScrollingHandler::handleScrolling()
    {
        int _scrollDistanceDenominator;
        int _scrollDistanceMax = (this->scrollDistanceLimit * 2) / 3;
        if (DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU) {
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
        if (!this->scrollUp) {
            if (!this->scrollDown) {
                if (!this->scrollLeft) {
                    if (!this->scrollRight) {
                        this->scrollDirection_0x4 = UI::SD_NONE;
                    } else {
                        this->scrollDirection_0x4 = UI::SD_RIGHT;
                    }
                } else {
                    this->scrollDirection_0x4 = UI::SD_LEFT;
                }
            } else if (!this->scrollLeft) {
                if (!this->scrollRight) {
                    this->scrollDirection_0x4 = UI::SD_DOWN;
                } else {
                    this->scrollDirection_0x4 = UI::SD_DOWN_RIGHT;
                }
            } else {
                this->scrollDirection_0x4 = UI::SD_DOWN_LEFT;
            }
        } else if (!this->scrollLeft) {
            if (!this->scrollRight) {
                this->scrollDirection_0x4 = UI::SD_UP;
            } else {
                this->scrollDirection_0x4 = UI::SD_UP_RIGHT;
            }
        } else {
            this->scrollDirection_0x4 = UI::SD_UP_LEFT;
        }
        if (this->scrollDirection_0x4 == UI::SD_NONE) {
            this->isScrolling_0x0 = FALSE;
            this->scrollDistanceBase = this->scrollDistanceMin;
            this->timeOfLastNotScroll_0x40 = timeGetTime();
            this->scrollLeft = FALSE;
            this->scrollRight = FALSE;
            this->scrollUp = FALSE;
            this->scrollDown = FALSE;
            this->timeScrolling_0x44 = this->timeOfLastNotScroll_0x40;
        }
        this->isScrolling_0x0 = TRUE;
        if (this->scrollSpeedSetting_0x38 == UI::SS_FAST) {
            _scrollDistanceDenominator
                = (int)((ulonglong)((longlong)this->scrollAccelerationInterval * 0x55555555) >> 0x20)
                - this->scrollAccelerationInterval;
            _scrollDistanceDenominator = (_scrollDistanceDenominator >> 1) - (_scrollDistanceDenominator >> 0x1f);
            _scrollDistanceMax = (_scrollDistanceMax * 0x85) / 100;
        } else {
            _scrollDistanceDenominator = this->scrollAccelerationInterval;
            if (this->scrollSpeedSetting_0x38 != UI::SS_SLOW)
                goto LAB_00468c01;
            _scrollDistanceDenominator = this->scrollAccelerationInterval / 2;
            _scrollDistanceMax = _scrollDistanceMax / 2;
        }
        _scrollDistanceDenominator = this->scrollAccelerationInterval + _scrollDistanceDenominator;
    LAB_00468c01:
        DWORD _timeOfScroll = timeGetTime();
        this->timeScrolling_0x44 = _timeOfScroll - this->timeOfLastNotScroll_0x40;
        this->scrollDistanceBase = (int)(_timeOfScroll - this->timeOfLastNotScroll_0x40) / _scrollDistanceDenominator;
        if (_scrollDistanceMax < this->scrollDistanceBase) {
            this->scrollDistanceBase = _scrollDistanceMax;
        }
        this->scrollLeft = FALSE;
        this->scrollRight = FALSE;
        this->scrollUp = FALSE;
        this->scrollDown = FALSE;
    }

}
}
