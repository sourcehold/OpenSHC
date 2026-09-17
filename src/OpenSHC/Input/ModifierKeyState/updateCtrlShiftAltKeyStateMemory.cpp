#include "../ModifierKeyState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468A20
    void ModifierKeyState::updateCtrlShiftAltKeyStateMemory()
    {
        this->ctrl = FALSE;
        this->shift = FALSE;
        this->alt = FALSE;

        if (GetAsyncKeyState(VK_SHIFT)) {
            this->shift = TRUE;
        }

        if (GetAsyncKeyState(VK_CONTROL)) {
            this->ctrl = TRUE;
        }

        if (GetAsyncKeyState(VK_MENU)) {
            this->alt = TRUE;
        }

        if (!GetAsyncKeyState(VK_DOWN)) {
            this->downArrow = FALSE;
        }

        if (!GetAsyncKeyState('V')) {
            this->v = FALSE;
        }
    }

}
}
