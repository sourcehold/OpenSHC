#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468100
    void MouseState::updateMouseStateBasedOnCursorAndTime()
    {
        DWORD _now = timeGetTime();

        this->anyActivity = FALSE;

        this->previousScreenSpaceX = this->screenSpaceX;
        this->previousScreenSpaceY = this->screenSpaceY;

        this->previousLeftClickState = this->leftClickState;
        this->previousRightClickState = this->rightClickState;

        this->screenSpaceX = this->mouseWindowX;
        this->screenSpaceY = this->mouseWindowY;

        if (this->previousScreenSpaceX != this->mouseWindowX) {
            this->anyActivity = TRUE;
        }
        if (this->previousScreenSpaceY != this->mouseWindowY) {
            this->anyActivity = TRUE;
        }
        if (this->anyActivity) {
            this->flag = 1;

            this->mouseXY[this->index].x = this->screenSpaceX;
            this->mouseXY[this->index].y = this->screenSpaceY;
            this->mouseXY[this->index].unknownZero01 = 0;
            this->mouseXY[this->index].unknownOne02 = 1;

            ++this->index;
            if (this->index >= 10) {
                this->index = 0;
            }
        }

        POINT _cursorPos;
        GetCursorPos(&_cursorPos);
        this->cursorPosX = _cursorPos.x;
        this->cursorPosY = _cursorPos.y;
        if (this->cursorPosX <= 0) {
            DAT_ScrollingHandler::instance.scrollLeft = TRUE;
        }
        if (this->cursorPosX >= DAT_WindowAndDirectDraw::instance.screenHorizontalResolutionInPixels + -1) {
            DAT_ScrollingHandler::instance.scrollRight = TRUE;
        }
        if (this->cursorPosY <= 0) {
            DAT_ScrollingHandler::instance.scrollUp = TRUE;
        }
        if (this->cursorPosY >= DAT_WindowAndDirectDraw::instance.screenVerticalResolutionInPixels + -1) {
            DAT_ScrollingHandler::instance.scrollDown = TRUE;
        }

        if (this->mouseClickTypes & Mouse::CTBME_RIGHT_DOWN) {
            this->rightClickState = TRUE;
        } else {
            this->rightClickState = FALSE;
        }
        this->rightClickStart = 0;
        this->rightClickStop = 0;
        if (this->rightClickState != this->previousRightClickState) {
            this->anyActivity = TRUE;

            if (this->rightClickState) {
                this->rightClickStart = TRUE;
            } else {
                this->rightClickStop = TRUE;
            }
        }

        if (this->mouseClickTypes & Mouse::CTBME_MID_DOWN) {
            this->midClickState = TRUE;
        } else {
            this->midClickState = FALSE;
        }
        this->midClickStart = 0;
        this->midClickStop = 0;
        if (this->midClickState != this->previousMidClickStateUnk) {
            this->anyActivity = TRUE;

            if (this->midClickState) {
                this->midClickStart = TRUE;
            } else {
                this->midClickStop = TRUE;
            }
        }

        if (this->mouseClickTypes & Mouse::CTBME_LEFT_DOWN) {
            if (!this->leftClickState) {
                this->leftClickStartMoment = _now;
                this->dragReleaseX = this->mouseWindowX;
                this->dragReleaseY = this->mouseWindowY;
                this->leftClickState = TRUE;
            } else {
                if (this->dragReleaseX != this->mouseWindowX || this->dragReleaseY != this->mouseWindowY) {
                    this->leftClickStartMoment = -1;
                }
                this->leftClickState = TRUE;
            }
        } else {
            this->leftClickState = FALSE;
            if (this->dragReleaseX == this->mouseWindowX && this->dragReleaseY == this->mouseWindowY
                && this->leftClickStartMoment != -1) {
                this->leftClickStartMoment = -2;
            } else {
                this->leftClickStartMoment = -3;
            }
        }

        this->leftClickStart = FALSE;
        this->draggingStopped = FALSE;
        if (this->leftClickState != this->previousLeftClickState) {
            this->anyActivity = TRUE;

            if (this->leftClickState) {
                this->leftClickStart = TRUE;
            } else {
                this->draggingStopped = TRUE;
            }
        }

        if (!this->anyActivity) {
            this->inactiveTime = _now - this->time0;
        } else {
            this->time0 = _now;
            this->inactiveTime = 0;
        }

        if (this->mouseWheelDelta < 0) {
            this->scrollEventData = 7;
        } else if (this->mouseWheelDelta > 0) {
            this->scrollEventData = 8;
        } else {
            this->scrollEventData = 9;
        }
        this->mouseWheelDelta = 0;
    }

}
}
