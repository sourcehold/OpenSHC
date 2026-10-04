#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00467F80
    void MouseState::makeSelectedCursorTypeCurrent()
    {
        if (this->cursorType == 1) {
            this->currentDefaultCursor = this->swordCursor_0x224;
            this->currentDeleteCursor_0x200 = this->deleteCursor_0x228;
            this->currentWaitCursor_0x208 = this->jesterCursor_0x230;
            this->currentHandCursor_0x20c = this->handCursor_0x234;
            this->currentDeleteNotCursor_0x210 = this->deleteNotCursor_0x238;
            this->currentDefaultArabCursor_0x214 = this->scimitarCursor_0x23c;
            return;
        }

        if (this->cursorType == 2) {
            this->currentDefaultCursor = this->notAniDefaultCursor_0x24c;
            this->currentDeleteCursor_0x200 = this->notAniDeleteCursor_0x250;
            this->currentWaitCursor_0x208 = this->notAniWaitCursor_0x258;
            this->currentHandCursor_0x20c = this->notAniHandCursor_0x25c;
            this->currentDeleteNotCursor_0x210 = this->notAniDeleteNotCursor_0x260;
            this->currentDefaultArabCursor_0x214 = this->notAniDefaultArabCursor_0x264;
        }
    }

}
}
