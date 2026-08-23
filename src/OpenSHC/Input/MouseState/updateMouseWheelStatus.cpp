#include "OpenSHC/Input/MouseState.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004680b0
    void MouseState::updateMouseWheelStatus(int delta) { this->mouseWheelDelta = (unsigned short)delta; }

} // namespace Input
} // namespace OpenSHC
