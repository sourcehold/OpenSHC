#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::IO::Graphics::TgxTokenByte;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044F850
        void TextureRenderCore::renderTgxWithColorAndBlendingUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk, int blendStrengthUnk)
        {
            TgxTokenByte _tgxToken2;
            ushort uVar1;
            uint _length;
            TgxTokenByte _tgxToken;
            int iVar2;
            TgxTokenByte* pTVar3;
            ushort* _drawPointer;
            int _heightStart;
            int _lineByteWidth;
            int _jumpLineByteWidth;
            char _greenOffset;
            short _overlayStrengthUnk;
            _overlayStrengthUnk = 0x20 - (short)blendStrengthUnk;
            if (DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                _jumpLineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + width * -2;
                _heightStart = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start;
                iVar2 = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end;
            } else {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                _jumpLineByteWidth = (0xfd8 - width) * 2;
                _lineByteWidth = 0x1fb0;
                _heightStart = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                iVar2 = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end;
            }
            if ((height + yPos <= iVar2) || (height = iVar2 - yPos, 0 < height)) {
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                    _greenOffset = 5;
                    (*(char*)&width) = 10;
                } else {
                    _greenOffset = 6;
                    (*(char*)&width) = 0xb;
                }
                if (-1 < xPos) {
                    if (yPos < _heightStart) {
                        iVar2 = _heightStart - yPos;
                        if (height <= iVar2) {}
                        height = height - iVar2;
                        do {
                            while (true) {
                                while (true) {
                                    do {
                                        pTVar3 = (TgxTokenByte*)imageSource;
                                        _tgxToken = *pTVar3 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                        imageSource = (ushort*)(pTVar3 + 1);
                                    } while (_tgxToken == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                    if (_tgxToken != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                        break;
                                    imageSource = (ushort*)((int)imageSource + ((*pTVar3 & 0xffffff1f) + 1) * 2);
                                }
                                if (_tgxToken != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                    break;
                                imageSource = (ushort*)(pTVar3 + 3);
                            }
                            iVar2 = iVar2 + -1;
                            yPos = _heightStart;
                        } while (0 < iVar2);
                    }
                    _drawPointer = (ushort*)((int)DAT_TextureRenderCoreObject::instance.currentRenderSurface + yPos * _lineByteWidth + xPos * 2);
                LAB_0044f97b:
                    do {
                        while (true) {
                            _tgxToken2 = *(TgxTokenByte*)imageSource & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                            _length = *(TgxTokenByte*)imageSource & 0xffffff1f;
                            pTVar3 = (TgxTokenByte*)((int)imageSource + 1);
                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                break;
                            _drawPointer = _drawPointer + _length + 1;
                            imageSource = (ushort*)pTVar3;
                        }
                        if (_tgxToken2 == OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS) {
                            iVar2 = _length + 1;
                            do {
                                while (true) {
                                    uVar1 = (ushort)(_overlayStrengthUnk
                                                * ((ushort) * (undefined2*)pTVar3 >> _greenOffset & 0x1f))
                                        >> 5;
                                    if (uVar1 == 0x1f)
                                        break;
                                    _length = (((iVar2 >> 0x10) << 0x10) | (uint)(ushort)*_drawPointer) & 0xffff001f;
                                    *_drawPointer = ((((ushort)(((fillColorUnk >> (char)width & 0x1f)
                                                                    - (*_drawPointer >> (char)width & 0x1f))
                                                           * uVar1)
                                                          >> 5)
                                                             + (*_drawPointer >> (char)width & 0x1f)
                                                         & 0x1f)
                                                        << (char)width)
                                        + ((((ushort)(((fillColorUnk >> _greenOffset & 0x1f)
                                                          - (*_drawPointer >> _greenOffset & 0x1f))
                                                 * uVar1)
                                                >> 5)
                                                   + (*_drawPointer >> _greenOffset & 0x1f)
                                               & 0x1f)
                                            << _greenOffset)
                                        + (((ushort)(((fillColorUnk & 0x1f) - (short)_length) * uVar1) >> 5)
                                                + (*_drawPointer & 0x1f)
                                            & 0x1f);
                                    pTVar3 = pTVar3 + 2;
                                    _drawPointer = _drawPointer + 1;
                                    iVar2 = ((_length & 0xffff0000) | (uint)(ushort)iVar2) + -1;
                                    imageSource = (ushort*)pTVar3;
                                    if (iVar2 == 0)
                                        goto LAB_0044f97b;
                                }
                                *_drawPointer = fillColorUnk;
                                pTVar3 = pTVar3 + 2;
                                _drawPointer = _drawPointer + 1;
                                iVar2 = iVar2 + -1;
                                imageSource = (ushort*)pTVar3;
                            } while (iVar2 != 0);
                            goto LAB_0044f97b;
                        }
                        if (_tgxToken2 == OpenSHC::IO::Graphics::TT_REPEATING_PIXELS) {
                            imageSource = (ushort*)((int)imageSource + 3);
                            iVar2 = _length + 1;
                            uVar1 = (ushort)(_overlayStrengthUnk
                                        * ((ushort) * (undefined2*)pTVar3 >> _greenOffset & 0x1f))
                                >> 5;
                            if (uVar1 == 0x1f) {
                                do {
                                    *_drawPointer = fillColorUnk;
                                    _drawPointer = _drawPointer + 1;
                                    iVar2 = iVar2 + -1;
                                } while (iVar2 != 0);
                            } else {
                                do {
                                    _length = (((iVar2 >> 0x10) << 0x10) | (uint)(ushort)*_drawPointer) & 0xffff001f;
                                    *_drawPointer = ((((ushort)(((fillColorUnk >> (char)width & 0x1f)
                                                                    - (*_drawPointer >> (char)width & 0x1f))
                                                           * uVar1)
                                                          >> 5)
                                                             + (*_drawPointer >> (char)width & 0x1f)
                                                         & 0x1f)
                                                        << (char)width)
                                        + ((((ushort)(((fillColorUnk >> _greenOffset & 0x1f)
                                                          - (*_drawPointer >> _greenOffset & 0x1f))
                                                 * uVar1)
                                                >> 5)
                                                   + (*_drawPointer >> _greenOffset & 0x1f)
                                               & 0x1f)
                                            << _greenOffset)
                                        + (((ushort)(((fillColorUnk & 0x1f) - (short)_length) * uVar1) >> 5)
                                                + (*_drawPointer & 0x1f)
                                            & 0x1f);
                                    _drawPointer = _drawPointer + 1;
                                    iVar2 = ((_length & 0xffff0000) | (uint)(ushort)iVar2) + -1;
                                } while (iVar2 != 0);
                            }
                            goto LAB_0044f97b;
                        }
                        _drawPointer = (ushort*)((int)_drawPointer + _jumpLineByteWidth);
                        height = height + -1;
                        imageSource = (ushort*)pTVar3;
                    } while (0 < height);
                }
            }
        }

    }
}
}
