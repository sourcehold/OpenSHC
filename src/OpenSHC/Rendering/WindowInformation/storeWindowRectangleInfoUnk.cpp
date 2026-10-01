#include "OpenSHC/Rendering/WindowInformation.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x00467F60
    void WindowInformation::storeWindowRectangleInfoUnk(LONG left, LONG right, LONG top, LONG bottom)
    {
        this->RECT_SomeGameWindowRectUnk.left = left;
        this->RECT_SomeGameWindowRectUnk.top = top;
        this->RECT_SomeGameWindowRectUnk.right = right;
        this->RECT_SomeGameWindowRectUnk.bottom = bottom;
    }

}
}
