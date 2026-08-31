#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468030
    void MouseState::updateMousePositionAndClicks(short xMousePos, short yMousePos, MouseClickInteraction clickType)
    {
        this->mouseWindowX = xMousePos;
        this->mouseWindowY = yMousePos;

        if (clickType == Mouse::MCI_LEFTDOWN) {
            this->mouseClickTypes |= Mouse::CTBME_LEFT_DOWN;
            return;
        }

        if (clickType == Mouse::MCI_LEFTUP) {
            this->mouseClickTypes &= Mouse::CTBME_LEFT_UP;
            return;
        }

        if (clickType == Mouse::MCI_MIDDOWN) {
            this->mouseClickTypes |= Mouse::CTBME_MID_DOWN;
            return;
        }

        if (clickType == Mouse::MCI_MIDUP) {
            this->mouseClickTypes &= Mouse::CTBME_MIDUP;
            return;
        }

        if (clickType == Mouse::MCI_RIGHTDOWN) {
            this->mouseClickTypes |= Mouse::CTBME_RIGHT_DOWN;
            return;
        }

        if (clickType == Mouse::MCI_RIGHTUP) {
            this->mouseClickTypes &= Mouse::CTBME_RIGHT_UP;
            return;
        }
    }

}
}
