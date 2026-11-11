#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B61F0
    int MinimapViewState::generateMinimapImage()
    {
        // packs the minimap into a palette of up to 256 RGB555 colours and one palette index per tile
        int const tileCount = countof(this->loadedMiniMap) * countof(this->loadedMiniMap[0]);
        ushort palette[256];
        int colorCount = 0;
        byte* const colorIndices = (byte*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(tileCount);
        // the lowest bit of each channel (RGB565's green: the two lowest) is cleared, so close colours share an entry
        ushort colorMask;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            colorMask = (ushort) ~(1 << 11 | 3 << 5 | 1);
        } else {
            colorMask = (ushort) ~(1 << 10 | 1 << 5 | 1);
        }
        for (int i = 0; i < tileCount; ++i) {
            uint const color = ((ushort*)this->loadedMiniMap)[i] & colorMask;
            for (int index = 0; index < colorCount; ++index) {
                if (color == palette[index]) {
                    colorIndices[i] = index;
                    // a goto out of the search, not a break and an index test (the test: quick_diff 0.8636 -> 0.8539)
                    goto nextTile;
                }
            }
            if (colorCount < countof(palette)) {
                palette[colorCount] = color;
                colorIndices[i] = colorCount;
                ++colorCount;
            } else {
                colorIndices[i] = 0;
            }
        nextTile:;
        }
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            for (int i = 0; i < colorCount; ++i) {
                int const color = palette[i];
                // red and green shifted down, not ~0x1f (~0x1f: quick_diff 0.8636 -> 0.7458)
                palette[i] = color >> 1 & (31 << 10 | 31 << 5) | color & 0x1f;
            }
        }
        memcpy(this->loadedMiniMap, palette, sizeof(palette));
        MACRO_CALL(OpenSHC::OS_Func::_memcpy)((byte*)this->loadedMiniMap + sizeof(palette), colorIndices, tileCount);
        MACRO_CALL(OpenSHC::OS_Func::_free_base)(colorIndices);
        return sizeof(palette) + tileCount;
    }

}
}
