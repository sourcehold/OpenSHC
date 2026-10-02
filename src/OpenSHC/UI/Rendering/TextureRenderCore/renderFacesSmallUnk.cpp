#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CE00
        void TextureRenderCore::renderFacesSmallUnk(int facesIndex, int drawX, int drawY)
        {
            int _byteWidth;
            short* _surface;
            short* _surfacePixel;
            int i;
            short* _potraitDataBegin;
            short* _color;
            int j;
            _potraitDataBegin = (short*)(facesIndex * 0x2100 + (int)this->bitmapsFaces_0x94);
            if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_MAP_GAME) {
                _byteWidth = 8112;
                this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
            } else {
                _byteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA) {
                    _byteWidth = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                    this->currentRenderSurface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                }
            }
            _surface = (short*)((int)this->currentRenderSurface + drawX * 2 + _byteWidth * drawY);
            i = 33;
            do {
                j = 32;
                _surfacePixel = _surface;
                do {
                    _color = _potraitDataBegin;
                    if (*_color != COL_MAGENTA::instance.shortValue) {
                        *_surfacePixel = *_color;
                    }
                    _surfacePixel = _surfacePixel + 1;
                    j = j + -1;
                    _potraitDataBegin = _color + 2;
                } while (j != 0);
                _potraitDataBegin = _color + 0x42;
                i = i + -1;
                _surface = _surface + _byteWidth / 2;
            } while (i != 0);
        }

    }
}
}
