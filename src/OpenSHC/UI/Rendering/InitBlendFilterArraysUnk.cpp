#include "../Rendering.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044E510
    void Rendering::InitBlendFilterArraysUnk()
    {
        // DAT_BlendFilterArrays[level][value]: a colour component value scaled by level / 32, already shifted to its
        // place in the screen colour (0 blue, 1 green, 2 red)
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
            for (int level = 0; level < 33; ++level) {
                for (int value = 0; value < 32; ++value) {
                    ushort const scaled = value * level / 32;
                    DAT_BlendFilterArrays::instance[level][value][0] = scaled;
                    DAT_BlendFilterArrays::instance[level][value][1] = scaled << 5;
                    DAT_BlendFilterArrays::instance[level][value][2] = scaled << 10;
                }
            }
        } else {
            for (int level = 0; level < 33; ++level) {
                for (int value = 0; value < 32; ++value) {
                    ushort const scaled = value * level / 32;
                    DAT_BlendFilterArrays::instance[level][value][0] = scaled;
                    DAT_BlendFilterArrays::instance[level][value][2] = scaled << 11;
                    // green has 6 bits, so two entries per step
                    DAT_BlendFilterArrays::instance[level][value * 2][1] = (value * level * 4 / 64) << 5;
                    DAT_BlendFilterArrays::instance[level][value * 2 + 1][1] = ((value * level * 4 + level) / 64) << 5;
                }
            }
        }
    }

}
}
