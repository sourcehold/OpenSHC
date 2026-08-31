#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004689D0
    void MouseState::resetMouseState2()
    {
        if (!this->resetPending) {
            this->draggingStopped = FALSE;

            this->midClickStop = FALSE;
            this->rightClickStop = FALSE;

            this->leftClickStart = FALSE;
            this->midClickStart = FALSE;
            this->rightClickStart = FALSE;

            this->leftClickState = FALSE;
            this->midClickState = FALSE;
            this->rightClickState = FALSE;

            this->previousLeftClickState = FALSE;
            this->previousMidClickStateUnk = FALSE;
            this->previousRightClickState = FALSE;

            this->mouseClickTypes = 0;
        }
        this->resetPending = 0;
    }

}
}
