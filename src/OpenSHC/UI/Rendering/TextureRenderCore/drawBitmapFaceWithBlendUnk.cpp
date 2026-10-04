#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          Each channel is scaled and divided by 0x20 signed, so the decompiler's shift-plus-bias
          sequences are plain divisions. In RGB565 the source and destination are blended by
          weight; in RGB555 only the source is scaled. The 565 loop is written out four pixels at
          a time because MSVC1400 does not unroll.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CEB0
        void TextureRenderCore::drawBitmapFaceWithBlendUnk(
            int bitmapFaceIndex, int xPos, int yPos, int colorOrBlendOrGammaUnk)
        {
            int _pixelToLineJump;
            int _widthInByte;
            int _lineJumpBytes;
            int _rowCount;
            int _columnCount;
            int _srcWeight;
            ushort _srcPixel;
            ushort _dstPixel;
            int _blended;
            ushort* _surfacePtr;
            ushort* _bitmapPtr;
            ushort* _renderSurface;
            if (colorOrBlendOrGammaUnk == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace, this)(
                    bitmapFaceIndex, xPos, yPos);
                return;
            }
            if (colorOrBlendOrGammaUnk == 0x20) {
                return;
            }
            _bitmapPtr = (ushort*)(bitmapFaceIndex * 0x2100 + (int)this->bitmapsFaces_0x94);
            _srcWeight = 0x20 - colorOrBlendOrGammaUnk;
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                _renderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _pixelToLineJump = 0xf98;
                _widthInByte = 0x1fb0;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                _pixelToLineJump = AlphaAndButtonSurfaceObj::instance.currentImageWidth + -0x40;
                _renderSurface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                _widthInByte = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                break;
            default:
                _renderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _pixelToLineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 + -0x40;
                _widthInByte = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            DAT_TextureRenderCoreObject::instance.currentRenderSurface = _renderSurface;
            _surfacePtr = (ushort*)((int)_renderSurface + _widthInByte * yPos + xPos * 2);
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                _lineJumpBytes = _pixelToLineJump * 2;
                _rowCount = 0x42;
                do {
                    _columnCount = 0x10;
                    do {
                        _srcPixel = _bitmapPtr[0];
                        if (_srcPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                            _dstPixel = *_surfacePtr;
                            _blended = (((_srcPixel & 0x7e0) * _srcWeight / 0x20) & 0x7e0)
                                + (((_dstPixel & 0x7e0) * colorOrBlendOrGammaUnk / 0x20) & 0x7e0);
                            _blended = _blended
                                | (((_srcPixel & 0xf800) * _srcWeight / 0x20) & 0xf800)
                                    + (((_dstPixel & 0xf800) * colorOrBlendOrGammaUnk / 0x20) & 0xf800);
                            _blended = _blended
                                | ((_srcPixel & 0x1f) * _srcWeight / 0x20)
                                    + ((_dstPixel & 0x1f) * colorOrBlendOrGammaUnk / 0x20);
                            *_surfacePtr = (ushort)_blended;
                        }
                        _surfacePtr = _surfacePtr + 1;
                        _srcPixel = _bitmapPtr[1];
                        if (_srcPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                            _dstPixel = *_surfacePtr;
                            _blended = (((_srcPixel & 0x7e0) * _srcWeight / 0x20) & 0x7e0)
                                + (((_dstPixel & 0x7e0) * colorOrBlendOrGammaUnk / 0x20) & 0x7e0);
                            _blended = _blended
                                | (((_srcPixel & 0xf800) * _srcWeight / 0x20) & 0xf800)
                                    + (((_dstPixel & 0xf800) * colorOrBlendOrGammaUnk / 0x20) & 0xf800);
                            _blended = _blended
                                | ((_srcPixel & 0x1f) * _srcWeight / 0x20)
                                    + ((_dstPixel & 0x1f) * colorOrBlendOrGammaUnk / 0x20);
                            *_surfacePtr = (ushort)_blended;
                        }
                        _surfacePtr = _surfacePtr + 1;
                        _srcPixel = _bitmapPtr[2];
                        if (_srcPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                            _dstPixel = *_surfacePtr;
                            _blended = (((_srcPixel & 0x7e0) * _srcWeight / 0x20) & 0x7e0)
                                + (((_dstPixel & 0x7e0) * colorOrBlendOrGammaUnk / 0x20) & 0x7e0);
                            _blended = _blended
                                | (((_srcPixel & 0xf800) * _srcWeight / 0x20) & 0xf800)
                                    + (((_dstPixel & 0xf800) * colorOrBlendOrGammaUnk / 0x20) & 0xf800);
                            _blended = _blended
                                | ((_srcPixel & 0x1f) * _srcWeight / 0x20)
                                    + ((_dstPixel & 0x1f) * colorOrBlendOrGammaUnk / 0x20);
                            *_surfacePtr = (ushort)_blended;
                        }
                        _surfacePtr = _surfacePtr + 1;
                        _srcPixel = _bitmapPtr[3];
                        if (_srcPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                            _dstPixel = *_surfacePtr;
                            _blended = (((_srcPixel & 0x7e0) * _srcWeight / 0x20) & 0x7e0)
                                + (((_dstPixel & 0x7e0) * colorOrBlendOrGammaUnk / 0x20) & 0x7e0);
                            _blended = _blended
                                | (((_srcPixel & 0xf800) * _srcWeight / 0x20) & 0xf800)
                                    + (((_dstPixel & 0xf800) * colorOrBlendOrGammaUnk / 0x20) & 0xf800);
                            _blended = _blended
                                | ((_srcPixel & 0x1f) * _srcWeight / 0x20)
                                    + ((_dstPixel & 0x1f) * colorOrBlendOrGammaUnk / 0x20);
                            *_surfacePtr = (ushort)_blended;
                        }
                        _surfacePtr = _surfacePtr + 1;
                        _bitmapPtr = _bitmapPtr + 4;
                        _columnCount = _columnCount + -1;
                    } while (_columnCount != 0);
                    _surfacePtr = (ushort*)((int)_surfacePtr + _lineJumpBytes);
                    _rowCount = _rowCount + -1;
                } while (_rowCount != 0);
                return;
            }
            _lineJumpBytes = _pixelToLineJump * 2;
            _rowCount = 0x42;
            do {
                _columnCount = 0x40;
                do {
                    _srcPixel = *_bitmapPtr;
                    _bitmapPtr = _bitmapPtr + 1;
                    if (_srcPixel != (ushort)COL_MAGENTA::instance.shortValue) {
                        *_surfacePtr = (ushort)(((((_srcPixel & 0x3e0) * colorOrBlendOrGammaUnk / 0x20) & 0x3e0)
                                                    | (((_srcPixel & 0x7c00) * colorOrBlendOrGammaUnk / 0x20) & 0x7c00))
                            | ((_srcPixel & 0x1f) * colorOrBlendOrGammaUnk / 0x20));
                    }
                    _surfacePtr = _surfacePtr + 1;
                    _columnCount = _columnCount + -1;
                } while (_columnCount != 0);
                _surfacePtr = (ushort*)((int)_surfacePtr + _lineJumpBytes);
                _rowCount = _rowCount + -1;
            } while (_rowCount != 0);
        }

    }
}
}
