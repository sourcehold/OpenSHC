#include "../ScrollingHandler.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/ScrollDirection.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ScrollDirection;
    using OpenSHC::UI::ScrollSpeed;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00468AD0
    void ScrollingHandler::handleScrolling()
    {
        int _scrollDistanceMax;
        DWORD _timeOfScroll;
        int _scrollDistanceDenominator;
        _scrollDistanceMax = (this->field13_0x34 * 2) / 3;
        if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
            if (this->rightKeyDown_0x18 != FALSE) {
                this->scrollRight = TRUE;
            }
            if (this->leftKeyDown_0x1c != FALSE) {
                this->scrollLeft = TRUE;
            }
            if (this->upKeyDown_0x24 != FALSE) {
                this->scrollUp = TRUE;
            }
            if (this->downKeyDown_0x20 != FALSE) {
                this->scrollDown = TRUE;
            }
        }
        if (this->scrollUp == FALSE) {
            if (this->scrollDown == FALSE) {
                if (this->scrollLeft == FALSE) {
                    if (this->scrollRight == FALSE) {
                        this->scrollDirection_0x4 = OpenSHC::UI::SD_NONE;
                    } else {
                        this->scrollDirection_0x4 = OpenSHC::UI::SD_RIGHT;
                    }
                } else {
                    this->scrollDirection_0x4 = OpenSHC::UI::SD_LEFT;
                }
            } else if (this->scrollLeft == FALSE) {
                if (this->scrollRight == FALSE) {
                    this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN;
                } else {
                    this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN_RIGHT;
                }
            } else {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_DOWN_LEFT;
            }
        } else if (this->scrollLeft == FALSE) {
            if (this->scrollRight == FALSE) {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_UP;
            } else {
                this->scrollDirection_0x4 = OpenSHC::UI::SD_UP_RIGHT;
            }
        } else {
            this->scrollDirection_0x4 = OpenSHC::UI::SD_UP_LEFT;
        }
        if (this->scrollDirection_0x4 == OpenSHC::UI::SD_NONE) {
            this->isScrolling_0x0 = FALSE;
            this->scrollDistanceBase = this->field11_0x2c;
            this->timeOfLastNotScroll_0x40 = timeGetTime();
            this->scrollLeft = FALSE;
            this->scrollRight = FALSE;
            this->scrollUp = FALSE;
            this->scrollDown = FALSE;
            this->timeScrolling_0x44 = this->timeOfLastNotScroll_0x40;
        }
        this->isScrolling_0x0 = TRUE;
        if (this->scrollSpeedSetting_0x38 == OpenSHC::UI::SS_FAST) {
            _scrollDistanceDenominator
                = (int)((ulonglong)((longlong)this->field12_0x30 * 0x55555555) >> 0x20) - this->field12_0x30;
            _scrollDistanceDenominator = (_scrollDistanceDenominator >> 1) - (_scrollDistanceDenominator >> 0x1f);
            _scrollDistanceMax = (_scrollDistanceMax * 0x85) / 100;
        } else {
            _scrollDistanceDenominator = this->field12_0x30;
            if (this->scrollSpeedSetting_0x38 != OpenSHC::UI::SS_SLOW)
                goto LAB_00468c01;
            _scrollDistanceDenominator = this->field12_0x30 / 2;
            _scrollDistanceMax = _scrollDistanceMax / 2;
        }
        _scrollDistanceDenominator = this->field12_0x30 + _scrollDistanceDenominator;
    LAB_00468c01:
        _timeOfScroll = timeGetTime();
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
