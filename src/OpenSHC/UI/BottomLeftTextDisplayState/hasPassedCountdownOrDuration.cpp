#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_TextRelatedTime.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F4EF0
    void BottomLeftTextDisplayState::hasPassedCountdownOrDuration()
    {
        DWORD _now2;
        DWORD _now;
        bool _hasTime;
        DWORD _textRelatedTime;
        if (this->currentlyDisplayedTextIsDisplayedUnk == 0) {
            if (this->unknownCountdown01 != 0) {
                this->unknownCountdown01 = this->unknownCountdown01 + -1;
            }
        } else if (this->textMessageDurationUnk == 0) {
            this->textMessageDurationUnk = -1;
        } else {
            if (this->textMessageDurationUnk != -1) {
                _now2 = timeGetTime();
                if (_now2 - this->textMessageTime <= (uint)this->textMessageDurationUnk)
                    goto LAB_004f4f3a;
            }
            this->currentlyDisplayedTextIsDisplayedUnk = 0;
            this->unknownCountdown01 = 1;
        }
    LAB_004f4f3a:
        _now = timeGetTime();
        _textRelatedTime = DAT_TextRelatedTime::instance;
        _hasTime = DAT_TextRelatedTime::instance != 0;
        DAT_TextRelatedTime::instance = _now;
        if (_hasTime) {
            this->countdown = this->countdown + (_textRelatedTime - _now);
        }
    }

}
}
