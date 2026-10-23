#include "../MouseState.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Input {

    // TODO: We later also need to add the proper resources.

    // FUNCTION: STRONGHOLDCRUSADER 0x00470A00
    void MouseState::loadAndSetCursor(int notAniDefaultCursorRef, int notAniDeleteCursorRef,
        int notAniDeleteNotCursorRef, int unused1, int unused2, int unused3, int unused4, int notAniUnknownCursorRef)
    {
        this->notAniDefaultCursor_0x24c
            = LoadCursorA(DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDefaultCursorRef));

        this->notAniDeleteCursor_0x250
            = LoadCursorA(DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDeleteCursorRef));

        this->notAniWaitCursor_0x258 = LoadCursorA(NULL, IDC_WAIT);

        this->notAniHandCursor_0x25c
            = LoadCursorA(DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDefaultCursorRef));

        this->notAniDeleteNotCursor_0x260 = LoadCursorA(
            DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDeleteNotCursorRef));

        this->notAniDefaultArabCursor_0x264
            = LoadCursorA(DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDefaultCursorRef));

        this->swordCursor_0x224 = LoadCursorFromFileA(s_sword_ani_005a625c);
        this->deleteCursor_0x228 = LoadCursorFromFileA(s_delete_ani_005a6250);
        this->jesterCursor_0x230 = LoadCursorFromFileA(s_jester_ani_005a6244);
        this->handCursor_0x234 = LoadCursorFromFileA(s_hand_ani_005a6238);
        this->deleteNotCursor_0x238 = LoadCursorFromFileA(s_delete_not_ani_005a6228);
        this->scimitarCursor_0x23c = LoadCursorFromFileA(s_scimitar_ani_005a6218);

        if (!this->cursorType) {
            if (DAT_WindowAndDirectDraw::instance.not_DDCAPS2_CANBOBHARDWARE_0xe0) {
                this->cursorType = 2;
            } else {
                this->cursorType = 1;
            }
        }
        MACRO_CALL_MEMBER(MouseState_Func::makeSelectedCursorTypeCurrent, this)();

        if (notAniDeleteNotCursorRef) {
            this->unknownNotAniDeleteNotCursor_0x204 = LoadCursorA(
                DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniDeleteNotCursorRef));
        }
        if (notAniUnknownCursorRef) {
            this->unknownNotAniCursor_0x218 = LoadCursorA(
                DAT_WindowAndDirectDraw::instance.hInstanceUnk_0xa8, MAKEINTRESOURCE(notAniUnknownCursorRef));
        }
    }

}
}
