#include "../MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

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

        DAT_MouseState::instance.selectionBoxMode = 0;
        DAT_MouseState::instance.field31_0x94 = 0;
    }

}
}
