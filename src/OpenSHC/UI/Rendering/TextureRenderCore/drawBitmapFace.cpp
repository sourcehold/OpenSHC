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

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CD40
        void TextureRenderCore::drawBitmapFace(int bitmapFaceIndex, int xPos, int yPos)
        {
            int _pixelToJump;
            int _widthInByte;
            short* _ptrInSurface;
            int _facePixelWidth;
            short* _bitmapPtr;
            ushort _currentPixel;
            short* _renderSurface;
            _bitmapPtr = (short*)(bitmapFaceIndex * 0x2100 + (int)this->bitmapsFaces_0x94);
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                _renderSurface = (short*)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _pixelToJump = 0xf98;
                _widthInByte = 0x1fb0;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                _renderSurface = (short*)AlphaAndButtonSurfaceObj::instance.surfacePtr;
                _pixelToJump = AlphaAndButtonSurfaceObj::instance.currentImageWidth + -0x40;
                _widthInByte = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                break;
            default:
                _renderSurface = (short*)DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _pixelToJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 + -0x40;
                _widthInByte = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            DAT_TextureRenderCoreObject::instance.currentRenderSurface = (ushort*)_renderSurface;
            _ptrInSurface = (short*)((int)_renderSurface + _widthInByte * yPos + xPos * 2);
            _widthInByte = 0x42;
            do {
                _facePixelWidth = 0x40;
                do {
                    _currentPixel = *_bitmapPtr;
                    _bitmapPtr = _bitmapPtr + 1;
                    if (_currentPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                        *_ptrInSurface = _currentPixel;
                    }
                    _ptrInSurface = _ptrInSurface + 1;
                    _facePixelWidth = _facePixelWidth + -1;
                } while (_facePixelWidth != 0);
                _ptrInSurface = _ptrInSurface + _pixelToJump;
                _widthInByte = _widthInByte + -1;
            } while (_widthInByte != 0);
        }

    }
}
}
