#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CE00
        void TextureRenderCore::renderFacesSmallUnk(int facesIndex, int drawX, int drawY)
        {
            int _byteWidth;
            ushort* _rowStart;
            ushort* _surfacePixel;
            int i;
            ushort* _potraitDataBegin;
            int j;
            ushort* _renderSurface;
            int _pixelsPerLine;
            _potraitDataBegin = (ushort*)(facesIndex * 0x2100 + (int)this->bitmapsFaces_0x94);
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                _renderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _byteWidth = 0x1fb0;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                _byteWidth = AlphaAndButtonSurfaceObj::instance.currentImageWidth;
                _renderSurface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                _byteWidth = _byteWidth * 2;
                break;
            default:
                _renderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _byteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            DAT_TextureRenderCoreObject::instance.currentRenderSurface = _renderSurface;
            _surfacePixel = (ushort*)((int)_renderSurface + _byteWidth * drawY + drawX * 2);
            _pixelsPerLine = _byteWidth / 2;
            i = 0x21;
            do {
                _rowStart = _surfacePixel;
                j = 0x20;
                do {
                    if (*_potraitDataBegin != (ushort)COL_MAGENTA::instance.shortValue) {
                        *_surfacePixel = *_potraitDataBegin;
                    }
                    _surfacePixel = _surfacePixel + 1;
                    _potraitDataBegin = _potraitDataBegin + 2;
                    j = j + -1;
                } while (j != 0);
                _potraitDataBegin = _potraitDataBegin + 0x40;
                i = i + -1;
                _surfacePixel = _rowStart + _pixelsPerLine;
            } while (i != 0);
        }

    }
}
}
