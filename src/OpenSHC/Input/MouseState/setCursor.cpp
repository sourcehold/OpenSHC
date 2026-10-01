#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468370
    HCURSOR MouseState::setCursor(DWORD cursorType)
    {
        if (cursorType == 0) {
            if (this->lastSetCursorType) {
                return SetCursor(this->currentDefaultCursor);
            }
            return SetCursor(this->currentDefaultCursor);
        }

        if (cursorType == 1) {
            return SetCursor(this->unknownNotAniDeleteNotCursor_0x204);
        }

        if (cursorType == 3) {
            return SetCursor(this->currentWaitCursor_0x208);
        }

        if (cursorType == 4) {
            return SetCursor(this->currentHandCursor_0x20c);
        }

        if (cursorType == 5) {
            return SetCursor(this->currentDeleteNotCursor_0x210);
        }

        if (cursorType == 6) {
            return SetCursor(this->currentDefaultArabCursor_0x214);
        }
        return SetCursor(this->currentDeleteCursor_0x200);
    }

}
}
