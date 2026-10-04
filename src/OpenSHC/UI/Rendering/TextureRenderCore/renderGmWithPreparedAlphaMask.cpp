#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::IO::Graphics::TgxTokenByte;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044F170
        void TextureRenderCore::renderGmWithPreparedAlphaMask(
            int x, int y, int width, int height, ushort* imageDataPtr, int blendStrength)
        {
            ushort* puVar1;
            ushort uVar2;
            TgxTokenByte _tgxToken2;
            undefined2 uVar3;
            int _remainingHeight;
            int iVar4;
            uint _pixelLength;
            int _someLength;
            ushort uVar5;
            int _jumpLineByteSize;
            int _anotherLengthUnk;
            TgxTokenByte _tgxToken;
            byte bVar6;
            int iVar7;
            TgxTokenByte* _currentTgxDataPtr;
            ushort* puVar8;
            ushort* _currentRenderSurfacePtr;
            ushort* puVar9;
            int _heightRangeStart;
            int _byteWidth;
            ushort* _alphaAndButtonSurfacePtr;
            bool _stillHeightLeft;
            _alphaAndButtonSurfacePtr = AlphaAndButtonSurfaceObj::instance.surfacePtr;
            if (0 < height) {
                if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
                }
                if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                    this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                    _byteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                    _heightRangeStart = this->screenMenuSurfaceHeightRange.start;
                    _jumpLineByteSize = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + width * -2;
                    iVar7 = this->screenMenuSurfaceHeightRange.end;
                } else {
                    this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    _heightRangeStart = this->mapGameSurfaceHeightRange.start;
                    _jumpLineByteSize = (0xfd8 - width) * 2;
                    _byteWidth = 0x1fb0;
                    iVar7 = this->mapGameSurfaceHeightRange.end;
                }
                if ((y + height <= iVar7) || (height = iVar7 - y, 0 < height)) {
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                        if (-1 < x) {
                            if (y < _heightRangeStart) {
                                iVar7 = _heightRangeStart - y;
                                if (height <= iVar7) {}
                                height = height - iVar7;
                                do {
                                    while (true) {
                                        while (true) {
                                            do {
                                                _currentTgxDataPtr = (TgxTokenByte*)imageDataPtr;
                                                _tgxToken = *_currentTgxDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                imageDataPtr = (ushort*)(_currentTgxDataPtr + 1);
                                            } while (_tgxToken == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                            if (_tgxToken != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                break;
                                            imageDataPtr = (ushort*)((int)imageDataPtr
                                                + ((*_currentTgxDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH) + 1) * 2);
                                        }
                                        if (_tgxToken != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                            break;
                                        imageDataPtr = (ushort*)(_currentTgxDataPtr + 3);
                                    }
                                    _alphaAndButtonSurfacePtr = _alphaAndButtonSurfacePtr + width;
                                    _remainingHeight = iVar7 + -1;
                                    _stillHeightLeft = 0 < iVar7;
                                    y = _heightRangeStart;
                                    iVar7 = _remainingHeight;
                                } while (_remainingHeight != 0 && _stillHeightLeft);
                            }
                            _currentRenderSurfacePtr
                                = (ushort*)((int)this->currentRenderSurface + y * _byteWidth + x * 2);
                            do {
                                while (true) {
                                    while (true) {
                                        while (true) {
                                            _tgxToken2 = *(TgxTokenByte*)imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                            _pixelLength = (uint)(*(TgxTokenByte*)imageDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH);
                                            _currentTgxDataPtr = (TgxTokenByte*)((int)imageDataPtr + 1);
                                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                                break;
                                            _currentRenderSurfacePtr = _currentRenderSurfacePtr + _pixelLength + 1;
                                            imageDataPtr = (ushort*)_currentTgxDataPtr;
                                            _alphaAndButtonSurfacePtr = _alphaAndButtonSurfacePtr + _pixelLength + 1;
                                        }
                                        if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                            break;
                                        _someLength = _pixelLength + 1;
                                        imageDataPtr = (ushort*)_currentTgxDataPtr;
                                        do {
                                            puVar9 = _alphaAndButtonSurfacePtr + 1;
                                            _anotherLengthUnk = (*_alphaAndButtonSurfacePtr & 0x1f) - blendStrength;
                                            if (_anotherLengthUnk != 0
                                                && blendStrength <= (int)(*_alphaAndButtonSurfacePtr & 0x1f)) {
                                                if (_anotherLengthUnk == 0x1f) {
                                                    *_currentRenderSurfacePtr = *imageDataPtr;
                                                } else {
                                                    uVar3 = *imageDataPtr & 0xffe0
                                                        | DAT_BlendFilterArrays::instance[_anotherLengthUnk]
                                                                                         [*imageDataPtr & 0xffff001f]
                                                                                         [0];
                                                    uVar3 = uVar3 & 0xfc1f
                                                        | *(ushort*)(_anotherLengthUnk * 0x200 + 0xd7d2da
                                                            + ((ushort)uVar3 >> 5 & 0xffff001f) * 8);
                                                    uVar5 = *_currentRenderSurfacePtr;
                                                    *_currentRenderSurfacePtr = uVar3 & 0x3ff
                                                        | *(ushort*)(_anotherLengthUnk * 0x200 + 0xd7d2dc
                                                            + ((ushort)uVar3 >> 10 & 0xffff001f) * 8);
                                                    iVar7 = (0x20 - _anotherLengthUnk) * 0x200;
                                                    uVar5 = uVar5 & 0xffe0
                                                        | DAT_BlendFilterArrays::instance[0x20 - _anotherLengthUnk]
                                                                                         [uVar5 & 0x1f][0];
                                                    uVar5 = uVar5 & 0xfc1f
                                                        | *(ushort*)(iVar7 + 0xd7d2da + (uint)(uVar5 >> 5 & 0x1f) * 8);
                                                    *_currentRenderSurfacePtr = *_currentRenderSurfacePtr
                                                        + (uVar5 & 0x83ff
                                                            | *(ushort*)(iVar7 + 0xd7d2dc
                                                                + (uint)(uVar5 >> 10 & 0x1f) * 8));
                                                }
                                            }
                                            imageDataPtr = (ushort*)((int)imageDataPtr + 2);
                                            _currentRenderSurfacePtr = _currentRenderSurfacePtr + 1;
                                            _someLength = _someLength + -1;
                                            _alphaAndButtonSurfacePtr = puVar9;
                                        } while (_someLength != 0);
                                    }
                                    if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                        break;
                                    iVar7 = _pixelLength + 1;
                                    do {
                                        puVar9 = _alphaAndButtonSurfacePtr + 1;
                                        _remainingHeight = (*_alphaAndButtonSurfacePtr & 0x1f) - blendStrength;
                                        if (_remainingHeight != 0
                                            && blendStrength <= (int)(*_alphaAndButtonSurfacePtr & 0x1f)) {
                                            if (_remainingHeight == 0x1f) {
                                                *_currentRenderSurfacePtr = *(undefined2*)_currentTgxDataPtr;
                                            } else {
                                                uVar3 = *(undefined2*)_currentTgxDataPtr & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[_remainingHeight][(
                                                        ushort)(*(undefined2*)_currentTgxDataPtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH)]
                                                                                     [0];
                                                uVar3 = uVar3 & 0xfc1f
                                                    | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2da
                                                        + (uint)((ushort)uVar3 >> 5 & 0x1f) * 8);
                                                iVar4 = (0x20 - _remainingHeight) * 0x200;
                                                uVar5 = *_currentRenderSurfacePtr & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[0x20
                                                        - _remainingHeight][*_currentRenderSurfacePtr & 0x1f][0];
                                                uVar5 = uVar5 & 0xfc1f
                                                    | *(ushort*)(iVar4 + 0xd7d2da + (uint)(uVar5 >> 5 & 0x1f) * 8);
                                                *_currentRenderSurfacePtr = (uVar5 & 0x83ff
                                                                                | *(ushort*)(iVar4 + 0xd7d2dc
                                                                                    + (uint)(uVar5 >> 10 & 0x1f) * 8))
                                                    + (uVar3 & 0x3ff
                                                        | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2dc
                                                            + (uint)((ushort)uVar3 >> 10 & 0x1f) * 8));
                                            }
                                        }
                                        _currentRenderSurfacePtr = _currentRenderSurfacePtr + 1;
                                        iVar7 = iVar7 + -1;
                                        _alphaAndButtonSurfacePtr = puVar9;
                                    } while (iVar7 != 0);
                                    imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                                }
                                _currentRenderSurfacePtr = (ushort*)((int)_currentRenderSurfacePtr + _jumpLineByteSize);
                                iVar7 = height + -1;
                                _stillHeightLeft = 0 < height;
                                height = iVar7;
                                imageDataPtr = (ushort*)_currentTgxDataPtr;
                            } while (iVar7 != 0 && _stillHeightLeft);
                        }
                    }
                    if (-1 < x) {
                        if (y < _heightRangeStart) {
                            iVar7 = _heightRangeStart - y;
                            if (height <= iVar7) {}
                            height = height - iVar7;
                            do {
                                while (true) {
                                    while (true) {
                                        do {
                                            puVar9 = imageDataPtr;
                                            bVar6 = (byte)*puVar9 & 0xe0;
                                            imageDataPtr = (ushort*)((int)puVar9 + 1);
                                        } while (bVar6 == 0x20);
                                        if (bVar6 != 0)
                                            break;
                                        imageDataPtr = imageDataPtr + ((byte)*puVar9 & 0x1f) + 1;
                                    }
                                    if (bVar6 != 0x40)
                                        break;
                                    imageDataPtr = (ushort*)((int)puVar9 + 3);
                                }
                                _alphaAndButtonSurfacePtr = _alphaAndButtonSurfacePtr + width;
                                _remainingHeight = iVar7 + -1;
                                _stillHeightLeft = 0 < iVar7;
                                y = _heightRangeStart;
                                iVar7 = _remainingHeight;
                            } while (_remainingHeight != 0 && _stillHeightLeft);
                        }
                        puVar9 = (ushort*)((int)this->currentRenderSurface + y * _byteWidth + x * 2);
                        do {
                            while (true) {
                                while (true) {
                                    while (true) {
                                        bVar6 = (byte)*imageDataPtr & 0xe0;
                                        _pixelLength = (uint)((byte)*imageDataPtr & 0x1f);
                                        puVar8 = (ushort*)((int)imageDataPtr + 1);
                                        if (bVar6 != 0x20)
                                            break;
                                        puVar9 = puVar9 + _pixelLength + 1;
                                        imageDataPtr = puVar8;
                                        _alphaAndButtonSurfacePtr = _alphaAndButtonSurfacePtr + _pixelLength + 1;
                                    }
                                    if (bVar6 != 0)
                                        break;
                                    iVar7 = _pixelLength + 1;
                                    imageDataPtr = puVar8;
                                    do {
                                        puVar8 = _alphaAndButtonSurfacePtr + 1;
                                        _remainingHeight = (*_alphaAndButtonSurfacePtr & 0x1f) - blendStrength;
                                        if (_remainingHeight != 0
                                            && blendStrength <= (int)(*_alphaAndButtonSurfacePtr & 0x1f)) {
                                            if (_remainingHeight == 0x1f) {
                                                *puVar9 = *imageDataPtr;
                                            } else {
                                                uVar5 = *imageDataPtr;
                                                uVar2 = *puVar9;
                                                iVar4 = (0x20 - _remainingHeight) * 0x200;
                                                *puVar9 = (DAT_BlendFilterArrays::instance[_remainingHeight]
                                                                                          [uVar5 & 0xffff001f][0]
                                                              | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2da
                                                                  + (uVar5 >> 5 & 0xffff003f) * 8)
                                                              | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2dc
                                                                  + (uint)(uVar5 >> 0xb) * 8))
                                                    + DAT_BlendFilterArrays::instance[0x20 - _remainingHeight]
                                                                                     [uVar2 & 0xffff001f][0]
                                                    + *(short*)(iVar4 + 0xd7d2da + (uVar2 >> 5 & 0xffff003f) * 8)
                                                    + *(short*)(iVar4 + 0xd7d2dc + (uint)(uVar2 >> 0xb) * 8);
                                            }
                                        }
                                        imageDataPtr = imageDataPtr + 1;
                                        puVar9 = puVar9 + 1;
                                        iVar7 = iVar7 + -1;
                                        _alphaAndButtonSurfacePtr = puVar8;
                                    } while (iVar7 != 0);
                                }
                                if (bVar6 != 0x40)
                                    break;
                                iVar7 = _pixelLength + 1;
                                do {
                                    puVar1 = _alphaAndButtonSurfacePtr + 1;
                                    _remainingHeight = (*_alphaAndButtonSurfacePtr & 0x1f) - blendStrength;
                                    if (_remainingHeight != 0
                                        && blendStrength <= (int)(*_alphaAndButtonSurfacePtr & 0x1f)) {
                                        if (_remainingHeight == 0x1f) {
                                            *puVar9 = *puVar8;
                                        } else {
                                            uVar5 = *puVar8;
                                            iVar4 = (0x20 - _remainingHeight) * 0x200;
                                            uVar2 = *puVar9;
                                            *puVar9
                                                = (DAT_BlendFilterArrays::instance[_remainingHeight][uVar5 & 0x1f][0]
                                                      | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2da
                                                          + (uint)(uVar5 >> 5 & 0x3f) * 8)
                                                      | *(ushort*)(_remainingHeight * 0x200 + 0xd7d2dc
                                                          + (uint)(uVar5 >> 0xb) * 8))
                                                + DAT_BlendFilterArrays::instance[0x20 - _remainingHeight][uVar2 & 0x1f]
                                                                                 [0]
                                                + *(short*)(iVar4 + 0xd7d2da + (uint)(uVar2 >> 5 & 0x3f) * 8)
                                                + *(short*)(iVar4 + 0xd7d2dc + (uint)(uVar2 >> 0xb) * 8);
                                        }
                                    }
                                    puVar9 = puVar9 + 1;
                                    iVar7 = iVar7 + -1;
                                    _alphaAndButtonSurfacePtr = puVar1;
                                } while (iVar7 != 0);
                                imageDataPtr = (ushort*)((int)imageDataPtr + 3);
                            }
                            puVar9 = (ushort*)((int)puVar9 + _jumpLineByteSize);
                            iVar7 = height + -1;
                            _stillHeightLeft = 0 < height;
                            height = iVar7;
                            imageDataPtr = puVar8;
                        } while (iVar7 != 0 && _stillHeightLeft);
                    }
                }
            }
        }

    }
}
}
