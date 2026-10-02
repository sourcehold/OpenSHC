#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::IO::Graphics::TgxTokenByte;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044E630
        void TextureRenderCore::renderInterfaceOrBuildingOccupationArea(
            int x, int y, int width, int height, ushort* imageDataPtr, int blendStrengthUnk)
        {
            ushort uVar1;
            int iVar2;
            TgxTokenByte _tgxToken2;
            TgxTokenByte bVar4;
            byte bVar3;
            undefined2 uVar4;
            undefined2 uVar5;
            ushort uVar6;
            int iVar7;
            int _remainingVerticalSpace;
            int _jumpLineBytes;
            ushort uVar8;
            uint _tgxPixelLength;
            int iVar9;
            TgxTokenByte _tgxToken3;
            TgxTokenByte _tgxToken;
            int iVar10;
            uint uVar11;
            TgxTokenByte* _imageDataPtr;
            TgxTokenByte* pTVar12;
            ushort* puVar13;
            ushort* puVar14;
            ushort* _surfaceDataPtr;
            ushort* _renderSurfacePtr;
            uint local_c;
            uint _heigthRangeStart2;
            ushort _surfaceColor;
            int _surfaceHeightEnd;
            int _surfaceHeightStart;
            bool _verticalSpaceLeftUnk;
            iVar10 = blendStrengthUnk;
            if (0 < height) {
                if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
                }
                iVar7 = blendStrengthUnk * 0x200;
                iVar2 = blendStrengthUnk * -0x200;
                iVar9 = iVar2 + 0xd812d8;
                if (this->isZoom2 == 0) {
                    if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                        this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                        _jumpLineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + width * -2;
                        blendStrengthUnk = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                        _surfaceHeightStart = this->screenMenuSurfaceHeightRange.start;
                        _surfaceHeightEnd = this->screenMenuSurfaceHeightRange.end;
                    } else {
                        this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                        _jumpLineBytes = (0xfd8 - width) * 2;
                        blendStrengthUnk = 0x1fb0;
                        _surfaceHeightStart = this->mapGameSurfaceHeightRange.start;
                        _surfaceHeightEnd = this->mapGameSurfaceHeightRange.end;
                    }
                    if ((y + height <= _surfaceHeightEnd) || (height = _surfaceHeightEnd - y, 0 < height)) {
                        if (DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_555) {
                            if (-1 < x) {
                                if (y < _surfaceHeightStart) {
                                    _surfaceHeightEnd = _surfaceHeightStart - y;
                                    if (height <= _surfaceHeightEnd) {}
                                    height = height - _surfaceHeightEnd;
                                    do {
                                        while (true) {
                                            while (true) {
                                                do {
                                                    _imageDataPtr = (TgxTokenByte*)imageDataPtr;
                                                    _tgxToken
                                                        = *_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                    imageDataPtr = (ushort*)(_imageDataPtr + 1);
                                                } while (_tgxToken == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                                if (_tgxToken != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                    break;
                                                imageDataPtr = (ushort*)((int)imageDataPtr
                                                    + ((*_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH)
                                                          + 1)
                                                        * 2);
                                            }
                                            if (_tgxToken != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                                break;
                                            imageDataPtr = (ushort*)(_imageDataPtr + 3);
                                        }
                                        _remainingVerticalSpace = _surfaceHeightEnd + -1;
                                        _verticalSpaceLeftUnk = 0 < _surfaceHeightEnd;
                                        y = _surfaceHeightStart;
                                        _surfaceHeightEnd = _remainingVerticalSpace;
                                    } while (_remainingVerticalSpace != 0 && _verticalSpaceLeftUnk);
                                }
                                _renderSurfacePtr
                                    = (ushort*)((int)this->currentRenderSurface + y * blendStrengthUnk + x * 2);
                                do {
                                    while (true) {
                                        while (true) {
                                            while (true) {
                                                _tgxToken2 = *(TgxTokenByte*)imageDataPtr
                                                    & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                _tgxPixelLength = (uint)(*(TgxTokenByte*)imageDataPtr
                                                    & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH);
                                                _imageDataPtr = (TgxTokenByte*)((int)imageDataPtr + 1);
                                                if (_tgxToken2 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                                    break;
                                                _renderSurfacePtr = _renderSurfacePtr + _tgxPixelLength + 1;
                                                imageDataPtr = (ushort*)_imageDataPtr;
                                            }
                                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                break;
                                            _surfaceHeightStart = _tgxPixelLength + 1;
                                            imageDataPtr = (ushort*)_imageDataPtr;
                                            do {
                                                uVar4 = *imageDataPtr;
                                                _surfaceColor = *_renderSurfacePtr;
                                                *_renderSurfacePtr
                                                    = (*(ushort*)(iVar9 + ((ushort)uVar4 & 0xffff001f) * 8)
                                                          | *(ushort*)(iVar2 + 0xd812da
                                                              + ((ushort)uVar4 >> 5 & 0xffff003f) * 8)
                                                          | *(ushort*)(iVar2 + 0xd812dc
                                                              + (uint)((ushort)uVar4 >> 0xb) * 8))
                                                    + DAT_BlendFilterArrays::instance[iVar10][_surfaceColor & 0x1f][0]
                                                    + *(short*)(iVar7 + 0xd7d2da
                                                        + (uint)(_surfaceColor >> 5 & 0x3f) * 8)
                                                    + *(short*)(iVar7 + 0xd7d2dc + (uint)(_surfaceColor >> 0xb) * 8);
                                                imageDataPtr = (ushort*)((int)imageDataPtr + 2);
                                                _renderSurfacePtr = _renderSurfacePtr + 1;
                                                _surfaceHeightStart = _surfaceHeightStart + -1;
                                            } while (_surfaceHeightStart != 0);
                                        }
                                        if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                            break;
                                        uVar4 = *(undefined2*)_imageDataPtr;
                                        imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                                        _surfaceHeightStart = _tgxPixelLength + 1;
                                        _surfaceColor = *(ushort*)(iVar9
                                            + (uint)(ushort)(uVar4 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH) * 8);
                                        uVar6 = *(ushort*)(iVar2 + 0xd812da + (uint)((ushort)uVar4 >> 5 & 0x3f) * 8);
                                        uVar8 = *(ushort*)(iVar2 + 0xd812dc + (uint)((ushort)uVar4 >> 0xb) * 8);
                                        do {
                                            uVar1 = *_renderSurfacePtr;
                                            *_renderSurfacePtr
                                                = (DAT_BlendFilterArrays::instance[iVar10][uVar1 & 0x1f][0]
                                                      | *(ushort*)(iVar7 + 0xd7d2da + (uint)(uVar1 >> 5 & 0x3f) * 8)
                                                      | *(ushort*)(iVar7 + 0xd7d2dc + (uint)(uVar1 >> 0xb) * 8))
                                                + (_surfaceColor | uVar6 | uVar8);
                                            _renderSurfacePtr = _renderSurfacePtr + 1;
                                            _surfaceHeightStart = _surfaceHeightStart + -1;
                                        } while (_surfaceHeightStart != 0);
                                    }
                                    _renderSurfacePtr = (ushort*)((int)_renderSurfacePtr + _jumpLineBytes);
                                    _surfaceHeightStart = height + -1;
                                    _verticalSpaceLeftUnk = 0 < height;
                                    height = _surfaceHeightStart;
                                    imageDataPtr = (ushort*)_imageDataPtr;
                                } while (_surfaceHeightStart != 0 && _verticalSpaceLeftUnk);
                            }
                        }
                        if (-1 < x) {
                            if (y < _surfaceHeightStart) {
                                _surfaceHeightEnd = _surfaceHeightStart - y;
                                if (height <= _surfaceHeightEnd) {}
                                height = height - _surfaceHeightEnd;
                                do {
                                    while (true) {
                                        while (true) {
                                            do {
                                                _imageDataPtr = (TgxTokenByte*)imageDataPtr;
                                                _tgxToken3
                                                    = *_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                imageDataPtr = (ushort*)(_imageDataPtr + 1);
                                            } while (_tgxToken3 == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                            if (_tgxToken3 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                break;
                                            imageDataPtr = (ushort*)((int)imageDataPtr
                                                + ((*_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH) + 1)
                                                    * 2);
                                        }
                                        if (_tgxToken3 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                            break;
                                        imageDataPtr = (ushort*)(_imageDataPtr + 3);
                                    }
                                    _surfaceHeightEnd = _surfaceHeightEnd + -1;
                                    y = _surfaceHeightStart;
                                } while (0 < _surfaceHeightEnd);
                            }
                            _surfaceDataPtr = (ushort*)((int)this->currentRenderSurface + y * blendStrengthUnk + x * 2);
                            do {
                                while (true) {
                                    while (true) {
                                        while (true) {
                                            _tgxToken2 = *(TgxTokenByte*)imageDataPtr
                                                & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                            _tgxPixelLength = *(TgxTokenByte*)imageDataPtr & 0xffffff1f;
                                            _imageDataPtr = (TgxTokenByte*)((int)imageDataPtr + 1);
                                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                                break;
                                            _surfaceDataPtr = _surfaceDataPtr + _tgxPixelLength + 1;
                                            imageDataPtr = (ushort*)_imageDataPtr;
                                        }
                                        if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                            break;
                                        _surfaceHeightStart = _tgxPixelLength + 1;
                                        do {
                                            uVar4 = *(undefined2*)_imageDataPtr & 0xffe0
                                                | *(ushort*)(iVar9
                                                    + ((ushort) * (undefined2*)_imageDataPtr & 0xffff001f) * 8);
                                            uVar4 = uVar4 & 0xfc1f
                                                | *(ushort*)(iVar2 + 0xd812da + ((ushort)uVar4 >> 5 & 0xffff001f) * 8);
                                            _surfaceColor = *_surfaceDataPtr;
                                            *_surfaceDataPtr = uVar4 & 0x3ff
                                                | *(ushort*)(iVar2 + 0xd812dc + ((ushort)uVar4 >> 10 & 0xffff001f) * 8);
                                            _surfaceColor = _surfaceColor & 0xffe0
                                                | DAT_BlendFilterArrays::instance[iVar10][_surfaceColor & 0xffff001f]
                                                                                 [0];
                                            _surfaceColor = _surfaceColor & 0xfc1f
                                                | *(ushort*)(iVar7 + 0xd7d2da + (_surfaceColor >> 5 & 0xffff001f) * 8);
                                            *_surfaceDataPtr = *_surfaceDataPtr
                                                + (_surfaceColor & 0x83ff
                                                    | *(ushort*)(iVar7 + 0xd7d2dc
                                                        + (_surfaceColor >> 10 & 0xffff001f) * 8));
                                            _imageDataPtr = _imageDataPtr + 2;
                                            _surfaceDataPtr = _surfaceDataPtr + 1;
                                            _surfaceHeightStart = _surfaceHeightStart + -1;
                                            imageDataPtr = (ushort*)_imageDataPtr;
                                        } while (_surfaceHeightStart != 0);
                                    }
                                    if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                        break;
                                    imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                                    _surfaceHeightStart = _tgxPixelLength + 1;
                                    uVar4 = *(undefined2*)_imageDataPtr & 0xffe0
                                        | *(ushort*)(iVar9 + ((ushort) * (undefined2*)_imageDataPtr & 0xffff001f) * 8);
                                    uVar5 = uVar4 & 0xfc1f
                                        | *(ushort*)(iVar2 + 0xd812da + ((ushort)uVar4 >> 5 & 0xffff001f) * 8);
                                    uVar4 = *(ushort*)(iVar2 + 0xd812dc + ((ushort)uVar5 >> 10 & 0xffff001f) * 8);
                                    do {
                                        _surfaceColor = *_surfaceDataPtr & 0xffe0
                                            | DAT_BlendFilterArrays::instance[iVar10][*_surfaceDataPtr & 0xffff001f][0];
                                        _surfaceColor = _surfaceColor & 0xfc1f
                                            | *(ushort*)(iVar7 + 0xd7d2da + (_surfaceColor >> 5 & 0xffff001f) * 8);
                                        *_surfaceDataPtr = (_surfaceColor & 0x83ff
                                                               | *(ushort*)(iVar7 + 0xd7d2dc
                                                                   + (_surfaceColor >> 10 & 0xffff001f) * 8))
                                            + (uVar5 & 0x3ff | uVar4);
                                        _surfaceDataPtr = _surfaceDataPtr + 1;
                                        _surfaceHeightStart = _surfaceHeightStart + -1;
                                    } while (_surfaceHeightStart != 0);
                                }
                                _surfaceDataPtr = (ushort*)((int)_surfaceDataPtr + _jumpLineBytes);
                                height = height + -1;
                                imageDataPtr = (ushort*)_imageDataPtr;
                            } while (0 < height);
                        }
                    }
                } else {
                    this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    if ((y + height <= this->mapGameSurfaceHeightRange.end)
                        || (height = this->mapGameSurfaceHeightRange.end - y, 0 < height)) {
                        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                            if (-1 < x) {
                                if (y < this->mapGameSurfaceHeightRange.start) {
                                    iVar10 = this->mapGameSurfaceHeightRange.start - y;
                                    if (height <= iVar10) {
                                        this->currentRenderSurface
                                            = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                                    }
                                    height = height - iVar10;
                                    do {
                                        while (true) {
                                            while (true) {
                                                do {
                                                    _imageDataPtr = (TgxTokenByte*)imageDataPtr;
                                                    _tgxToken2
                                                        = *_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                    imageDataPtr = (ushort*)(_imageDataPtr + 1);
                                                } while (_tgxToken2 == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                                if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                    break;
                                                imageDataPtr = (ushort*)((int)imageDataPtr
                                                    + ((*_imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH)
                                                          + 1)
                                                        * 2);
                                            }
                                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                                break;
                                            imageDataPtr = (ushort*)(_imageDataPtr + 3);
                                        }
                                        _jumpLineBytes = iVar10 + -1;
                                        _verticalSpaceLeftUnk = 0 < iVar10;
                                        y = this->mapGameSurfaceHeightRange.start;
                                        iVar10 = _jumpLineBytes;
                                    } while (_jumpLineBytes != 0 && _verticalSpaceLeftUnk);
                                }
                                iVar10 = (int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                                    + ((uint)y >> 1) * 0x1fb0 + (x & 0xfffffffeU);
                                local_c = 0;
                                _tgxPixelLength = local_c;
                                do {
                                    while (true) {
                                        while (true) {
                                            while (true) {
                                                local_c = _tgxPixelLength;
                                                bVar4 = *(TgxTokenByte*)imageDataPtr
                                                    & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                _tgxPixelLength = (uint)(*(TgxTokenByte*)imageDataPtr
                                                    & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH);
                                                _imageDataPtr = (TgxTokenByte*)((int)imageDataPtr + 1);
                                                if (bVar4 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                                    break;
                                                imageDataPtr = (ushort*)_imageDataPtr;
                                                _tgxPixelLength = local_c + _tgxPixelLength + 1;
                                            }
                                            if (bVar4 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                break;
                                            _jumpLineBytes = _tgxPixelLength + 1;
                                            _tgxPixelLength = local_c + _jumpLineBytes;
                                            do {
                                                if ((local_c & 1) == 0) {
                                                    uVar11 = (((uint)((short)(local_c >> 0x10)) << 0x10)
                                                                 | (uint)(ushort)(*(undefined2*)_imageDataPtr))
                                                        & 0xffff001f;
                                                    uVar4 = *(undefined2*)_imageDataPtr & 0xffe0
                                                        | *(ushort*)(iVar9 + uVar11 * 8);
                                                    uVar11 = (((uint)((short)(uVar11 >> 0x10)) << 0x10)
                                                                 | (uint)(ushort)((ushort)uVar4 >> 5))
                                                        & 0xffff001f;
                                                    uVar4 = uVar4 & 0xfc1f | *(ushort*)(iVar2 + 0xd812da + uVar11 * 8);
                                                    _surfaceColor = *(ushort*)(iVar10 + local_c);
                                                    *(ushort*)(iVar10 + local_c) = uVar4 & 0x3ff
                                                        | *(ushort*)(iVar2 + 0xd812dc
                                                            + ((((uint)((short)(uVar11 >> 0x10)) << 0x10)
                                                                   | (uint)(ushort)((ushort)uVar4 >> 10))
                                                                  & 0xffff001f)
                                                                * 8);
                                                    _surfaceColor = _surfaceColor & 0xffe0
                                                        | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                         [_surfaceColor & 0x1f][0];
                                                    _surfaceColor = _surfaceColor & 0xfc1f
                                                        | *(ushort*)(iVar7 + 0xd7d2da
                                                            + (uint)(_surfaceColor >> 5 & 0x1f) * 8);
                                                    *(short*)(iVar10 + local_c) = *(short*)(iVar10 + local_c)
                                                        + (_surfaceColor & 0x83ff
                                                            | *(ushort*)(iVar7 + 0xd7d2dc
                                                                + (uint)(_surfaceColor >> 10 & 0x1f) * 8));
                                                }
                                                local_c = local_c + 1;
                                                _imageDataPtr = _imageDataPtr + 2;
                                                _jumpLineBytes = _jumpLineBytes + -1;
                                                imageDataPtr = (ushort*)_imageDataPtr;
                                            } while (_jumpLineBytes != 0);
                                        }
                                        if (bVar4 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                            break;
                                        imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                                        uVar4 = *(undefined2*)_imageDataPtr & 0xffe0
                                            | *(ushort*)(iVar9
                                                + (uint)(ushort)(*(undefined2*)_imageDataPtr
                                                      & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH)
                                                    * 8);
                                        uVar5 = uVar4 & 0xfc1f
                                            | *(ushort*)(iVar2 + 0xd812da + (uint)((ushort)uVar4 >> 5 & 0x1f) * 8);
                                        uVar4 = *(ushort*)(iVar2 + 0xd812dc + (uint)((ushort)uVar5 >> 10 & 0x1f) * 8);
                                        _jumpLineBytes = _tgxPixelLength + 1;
                                        _tgxPixelLength = local_c + _jumpLineBytes;
                                        do {
                                            if ((local_c & 1) == 0) {
                                                _surfaceColor = *(ushort*)(iVar10 + local_c) & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                     [*(ushort*)(iVar10 + local_c)
                                                                                         & 0x1f][0];
                                                _surfaceColor = _surfaceColor & 0xfc1f
                                                    | *(ushort*)(iVar7 + 0xd7d2da
                                                        + (uint)(_surfaceColor >> 5 & 0x1f) * 8);
                                                *(ushort*)(iVar10 + local_c)
                                                    = (_surfaceColor & 0x83ff
                                                          | *(ushort*)(iVar7 + 0xd7d2dc
                                                              + (uint)(_surfaceColor >> 10 & 0x1f) * 8))
                                                    + (uVar5 & 0x3ff | uVar4);
                                            }
                                            local_c = local_c + 1;
                                            _jumpLineBytes = _jumpLineBytes + -1;
                                        } while (_jumpLineBytes != 0);
                                    }
                                    iVar10 = iVar10 + 0x1fb0;
                                    _jumpLineBytes = height + -1;
                                    if (height < 2) {}
                                    while (true) {
                                        while (true) {
                                            do {
                                                pTVar12 = _imageDataPtr;
                                                _tgxToken2 = *pTVar12 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                _imageDataPtr = pTVar12 + 1;
                                            } while (_tgxToken2 == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                break;
                                            _imageDataPtr = _imageDataPtr
                                                + ((*pTVar12 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH) + 1) * 2;
                                        }
                                        if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                            break;
                                        _imageDataPtr = pTVar12 + 3;
                                    }
                                    local_c = 0;
                                    height = height + -2;
                                    imageDataPtr = (ushort*)_imageDataPtr;
                                    _tgxPixelLength = local_c;
                                } while (height != 0 && 0 < _jumpLineBytes);
                            }
                        }
                        if (-1 < x) {
                            if (y < this->mapGameSurfaceHeightRange.start) {
                                iVar10 = this->mapGameSurfaceHeightRange.start - y;
                                if (height <= iVar10) {
                                    this->currentRenderSurface
                                        = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                                }
                                height = height - iVar10;
                                do {
                                    while (true) {
                                        while (true) {
                                            do {
                                                puVar13 = imageDataPtr;
                                                bVar3 = (byte)*puVar13 & 0xe0;
                                                imageDataPtr = (ushort*)((int)puVar13 + 1);
                                            } while (bVar3 == 0x20);
                                            if (bVar3 != 0)
                                                break;
                                            imageDataPtr = imageDataPtr + ((byte)*puVar13 & 0x1f) + 1;
                                        }
                                        if (bVar3 != 0x40)
                                            break;
                                        imageDataPtr = (ushort*)((int)puVar13 + 3);
                                    }
                                    _jumpLineBytes = iVar10 + -1;
                                    _verticalSpaceLeftUnk = 0 < iVar10;
                                    y = this->mapGameSurfaceHeightRange.start;
                                    iVar10 = _jumpLineBytes;
                                } while (_jumpLineBytes != 0 && _verticalSpaceLeftUnk);
                            }
                            iVar10 = (int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                                + ((uint)y >> 1) * 0x1fb0 + (x & 0xfffffffeU);
                            local_c = 0;
                            _tgxPixelLength = local_c;
                            do {
                                while (true) {
                                    while (true) {
                                        while (true) {
                                            local_c = _tgxPixelLength;
                                            bVar3 = (byte)*imageDataPtr & 0xe0;
                                            _tgxPixelLength = (uint)((byte)*imageDataPtr & 0x1f);
                                            puVar13 = (ushort*)((int)imageDataPtr + 1);
                                            if (bVar3 != 0x20)
                                                break;
                                            imageDataPtr = puVar13;
                                            _tgxPixelLength = local_c + _tgxPixelLength + 1;
                                        }
                                        if (bVar3 != 0)
                                            break;
                                        _jumpLineBytes = _tgxPixelLength + 1;
                                        _tgxPixelLength = local_c + _jumpLineBytes;
                                        do {
                                            if ((local_c & 1) == 0) {
                                                uVar11 = (((uint)((short)(local_c >> 0x10)) << 0x10)
                                                             | (uint)(ushort)(*puVar13))
                                                    & 0xffff001f;
                                                _surfaceColor = *puVar13 & 0xffe0 | *(ushort*)(iVar9 + uVar11 * 8);
                                                uVar11 = (((uint)((short)(uVar11 >> 0x10)) << 0x10)
                                                             | (uint)(ushort)(_surfaceColor >> 5))
                                                    & 0xffff003f;
                                                uVar6 = _surfaceColor & 0xf81f
                                                    | *(ushort*)(iVar2 + 0xd812da + uVar11 * 8);
                                                _surfaceColor = *(ushort*)(iVar10 + local_c);
                                                *(ushort*)(iVar10 + local_c) = uVar6 & 0x7ff
                                                    | *(ushort*)(iVar2 + 0xd812dc
                                                        + (((uint)((short)(uVar11 >> 0x10)) << 0x10)
                                                              | (uint)(ushort)(uVar6 >> 0xb))
                                                            * 8);
                                                _surfaceColor = _surfaceColor & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                     [_surfaceColor & 0x1f][0];
                                                _surfaceColor = _surfaceColor & 0xf81f
                                                    | *(ushort*)(iVar7 + 0xd7d2da
                                                        + (uint)(_surfaceColor >> 5 & 0x3f) * 8);
                                                *(short*)(iVar10 + local_c) = *(short*)(iVar10 + local_c)
                                                    + (_surfaceColor & 0x7ff
                                                        | *(ushort*)(iVar7 + 0xd7d2dc
                                                            + (uint)(_surfaceColor >> 0xb) * 8));
                                            }
                                            local_c = local_c + 1;
                                            puVar13 = puVar13 + 1;
                                            _jumpLineBytes = _jumpLineBytes + -1;
                                            imageDataPtr = puVar13;
                                        } while (_jumpLineBytes != 0);
                                    }
                                    if (bVar3 != 0x40)
                                        break;
                                    imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                                    _surfaceColor = *puVar13 & 0xffe0 | *(ushort*)(iVar9 + (uint)(*puVar13 & 0x1f) * 8);
                                    uVar6 = _surfaceColor & 0xf81f
                                        | *(ushort*)(iVar2 + 0xd812da + (uint)(_surfaceColor >> 5 & 0x3f) * 8);
                                    _surfaceColor = *(ushort*)(iVar2 + 0xd812dc + (uint)(uVar6 >> 0xb) * 8);
                                    _jumpLineBytes = _tgxPixelLength + 1;
                                    _tgxPixelLength = local_c + _jumpLineBytes;
                                    do {
                                        if ((local_c & 1) == 0) {
                                            uVar8 = *(ushort*)(iVar10 + local_c) & 0xffe0
                                                | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                 [*(ushort*)(iVar10 + local_c) & 0x1f]
                                                                                 [0];
                                            uVar8 = uVar8 & 0xf81f
                                                | *(ushort*)(iVar7 + 0xd7d2da + (uint)(uVar8 >> 5 & 0x3f) * 8);
                                            *(ushort*)(iVar10 + local_c)
                                                = (uVar8 & 0x7ff
                                                      | *(ushort*)(iVar7 + 0xd7d2dc + (uint)(uVar8 >> 0xb) * 8))
                                                + (uVar6 & 0x7ff | _surfaceColor);
                                        }
                                        local_c = local_c + 1;
                                        _jumpLineBytes = _jumpLineBytes + -1;
                                    } while (_jumpLineBytes != 0);
                                }
                                iVar10 = iVar10 + 0x1fb0;
                                _jumpLineBytes = height + -1;
                                if (height < 2) {}
                                while (true) {
                                    while (true) {
                                        do {
                                            puVar14 = puVar13;
                                            bVar3 = (byte)*puVar14 & 0xe0;
                                            puVar13 = (ushort*)((int)puVar14 + 1);
                                        } while (bVar3 == 0x20);
                                        if (bVar3 != 0)
                                            break;
                                        puVar13 = puVar13 + ((byte)*puVar14 & 0x1f) + 1;
                                    }
                                    if (bVar3 != 0x40)
                                        break;
                                    puVar13 = (ushort*)((int)puVar14 + 3);
                                }
                                local_c = 0;
                                height = height + -2;
                                imageDataPtr = puVar13;
                                _tgxPixelLength = local_c;
                            } while (height != 0 && 0 < _jumpLineBytes);
                        }
                    }
                }
            }
        }

    }
}
}
