#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6320
    void MinimapViewState::convertLoadedMinimapColors()
    {
        // a loaded minimap is a 256-colour RGB555 palette followed by one palette index per tile
        int const tileCount = countof(this->loadedMiniMap) * countof(this->loadedMiniMap[0]);
        ushort palette[256];
        byte* const colorIndices = (byte*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(tileCount);
        memcpy(palette, this->loadedMiniMap, sizeof(palette));
        MACRO_CALL(OpenSHC::OS_Func::_memcpy)(colorIndices, (byte*)this->loadedMiniMap + sizeof(palette), tileCount);
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            for (int i = 0; i < countof(palette); ++i) {
                // read once, not per use (per use, MSVC unrolls the loop: quick_diff 0.8276 -> 0.6506)
                ushort const color = palette[i];
                palette[i] = (color & ~0x1f) * 2 | color & 0x1f;
            }
        }
        for (int i = 0; i < tileCount; ++i) {
            ((ushort*)this->loadedMiniMap)[i] = palette[colorIndices[i]];
        }
        MACRO_CALL(OpenSHC::OS_Func::_free_base)(colorIndices);
    }

}
}
