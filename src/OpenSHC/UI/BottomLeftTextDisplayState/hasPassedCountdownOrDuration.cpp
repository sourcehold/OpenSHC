#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_TextRelatedTime.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4EF0
    void BottomLeftTextDisplayState::hasPassedCountdownOrDuration()
    {
        if (this->currentlyDisplayedTextIsDisplayedUnk != 0) {
            if (this->textMessageDurationUnk == 0) {
                this->textMessageDurationUnk = -1;
            } else if (this->textMessageDurationUnk == -1
                || timeGetTime() - this->textMessageTime > (DWORD)this->textMessageDurationUnk) {
                this->currentlyDisplayedTextIsDisplayedUnk = 0;
                this->unknownCountdown01 = 1;
            }
        } else if (this->unknownCountdown01 != 0) {
            --this->unknownCountdown01;
        }
        DWORD const now = timeGetTime();
        DWORD const previousTime = DAT_TextRelatedTime::instance;
        DAT_TextRelatedTime::instance = now;
        if (previousTime != 0) {
            this->countdown -= now - previousTime;
        }
    }

}
}
