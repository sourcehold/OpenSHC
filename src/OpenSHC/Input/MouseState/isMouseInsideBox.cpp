#include "../MouseState.func.hpp"

namespace OpenSHC {
namespace Input {

    // FUNCTION: STRONGHOLDCRUSADER 0x004680C0
    BOOLEnum MouseState::isMouseInsideBox(int xPos, int yPos, int width, int heigth)
    {
        if (xPos > this->screenSpaceX) {
            return FALSE;
        }
        if ((xPos + width) <= this->screenSpaceX) {
            return FALSE;
        }
        if (yPos > this->screenSpaceY) {
            return FALSE;
        }
        if ((yPos + heigth) <= this->screenSpaceY) {
            return FALSE;
        }
        return TRUE;
    }

}
}
