#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044C8F0
        void TextureRenderCore::transformGmColorTableFromRGB555To565IfRequired(int gmID)
        {
            ushort* _colorTableRunPtr;
            int _counter;
            ushort _color;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                _colorTableRunPtr = (ushort*)this->gmFileHeaderColorpaletteArray[gmID].colorPalette;
                _counter = 2560;
                do {
                    _color = *_colorTableRunPtr;
                    *_colorTableRunPtr = (_color & 0x1f) + ((_color & 0xfc00) + (_color & 0x3e0)) * 2;
                    _colorTableRunPtr = _colorTableRunPtr + 1;
                    _counter = _counter + -1;
                } while (_counter != 0);
            }
        }

    }
}
}
