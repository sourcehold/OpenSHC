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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CD40
        void TextureRenderCore::drawBitmapFace(int bitmapFaceIndex, int xPos, int yPos)
        {
            int _pixelToJump;
            int _widthInByte;
            short* _ptrInSurface;
            int _facePixelWidth;
            short* _bitmapPtr;
            short _currentPixel;
            _bitmapPtr
                = (short*)(bitmapFaceIndex * 0x2100 + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94);
            if (DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_MAP_GAME) {
                _pixelToJump = 0xf98;
                _widthInByte = 0x1fb0;
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
            } else if (DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                == OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA) {
                _pixelToJump = AlphaAndButtonSurfaceObj::instance.currentImageWidth + -0x40;
                _widthInByte = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = AlphaAndButtonSurfaceObj::instance.surfacePtr;
            } else {
                _pixelToJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 + -0x40;
                _widthInByte = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
            }
            _ptrInSurface = (short*)((int)DAT_TextureRenderCoreObject::instance.currentRenderSurface + xPos * 2
                + _widthInByte * yPos);
            _widthInByte = 0x42;
            do {
                _facePixelWidth = 0x40;
                do {
                    _currentPixel = *_bitmapPtr;
                    _bitmapPtr = _bitmapPtr + 1;
                    if (_currentPixel != COL_MAGENTA::instance.shortValue) {
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
