#include "../ModifierKeyState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x00468A10
    ModifierKeyState* ModifierKeyState::Constructor_ModifierKeyState()
    {
        this->keyDownUnk = 0;
        this->ctrl = 0;
        this->shift = 0;
        return this;
    }

}
}
