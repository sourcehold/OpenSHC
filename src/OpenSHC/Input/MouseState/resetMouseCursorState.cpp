#include "OpenSHC/Input/MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468590
    void MouseState::resetMouseCursorState()
    {
        this->selectionBox.left = 0;
        this->selectionBox.top = 0;
        this->selectionBox.right = 0;
        this->selectionBox.bottom = 0;
        this->previousSelectionBox.left = 0;
        this->previousSelectionBox.top = 0;
        this->previousSelectionBox.right = 0;
        this->previousSelectionBox.bottom = 0;
        this->selectionBoxMode = 0;
        this->field31_0x94 = 0;
    }

}
}
