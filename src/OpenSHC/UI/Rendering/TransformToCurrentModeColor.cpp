#include "../Rendering.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::ColorMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00467850
    uint Rendering::TransformToCurrentModeColor(int red, int green, int blue)
    {
        char _redShift;
        char _greenShift;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
            _greenShift = 3;
            _redShift = 10;
        } else {
            _greenShift = 2;
            _redShift = 11;
        }
        return (red >> 3) << _redShift | (green >> _greenShift) << 5 | blue >> 3;
    }

}
}
