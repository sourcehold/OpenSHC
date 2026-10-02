#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::IO::Graphics::TgxTokenByte;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044F6F0
        void TextureRenderCore::renderTgxWithColorUnk(
            int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk)
        {
            TgxTokenByte _tgxToken2;
            uint _length;
            TgxTokenByte _tgxToken;
            int iVar1;
            TgxTokenByte* _tgxHeader;
            ushort* _drawingPosition;
            int _heightStart;
            int _lineByteWidth;
            if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                _lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                width = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + width * -2;
                _heightStart = this->screenMenuSurfaceHeightRange.start;
                iVar1 = this->screenMenuSurfaceHeightRange.end;
            } else {
                this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                width = (0xfd8 - width) * 2;
                _heightStart = this->mapGameSurfaceHeightRange.start;
                _lineByteWidth = 0x1fb0;
                iVar1 = this->mapGameSurfaceHeightRange.end;
            }
            if (((height + yPos <= iVar1) || (height = iVar1 - yPos, 0 < height)) && (-1 < xPos)) {
                if (yPos < _heightStart) {
                    iVar1 = _heightStart - yPos;
                    if (height <= iVar1) {}
                    height = height - iVar1;
                    do {
                        while (true) {
                            while (true) {
                                do {
                                    _tgxHeader = (TgxTokenByte*)imageSource;
                                    _tgxToken = *_tgxHeader & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                    imageSource = (ushort*)(_tgxHeader + 1);
                                } while (_tgxToken == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                if (_tgxToken != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                    break;
                                imageSource = (ushort*)((int)imageSource + ((*_tgxHeader & 0xffffff1f) + 1) * 2);
                            }
                            if (_tgxToken != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                break;
                            imageSource = (ushort*)(_tgxHeader + 3);
                        }
                        iVar1 = iVar1 + -1;
                        yPos = _heightStart;
                    } while (0 < iVar1);
                }
                _drawingPosition = (ushort*)((int)this->currentRenderSurface + yPos * _lineByteWidth + xPos * 2);
                do {
                    while (true) {
                        while (true) {
                            while (true) {
                                _tgxToken2 = *(TgxTokenByte*)imageSource & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                _length = *(TgxTokenByte*)imageSource & 0xffffff1f;
                                _tgxHeader = (TgxTokenByte*)((int)imageSource + 1);
                                if (_tgxToken2 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                    break;
                                _drawingPosition = _drawingPosition + _length + 1;
                                imageSource = (ushort*)_tgxHeader;
                            }
                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                break;
                            iVar1 = _length + 1;
                            do {
                                *_drawingPosition = fillColorUnk;
                                _tgxHeader = _tgxHeader + 2;
                                _drawingPosition = _drawingPosition + 1;
                                iVar1 = iVar1 + -1;
                                imageSource = (ushort*)_tgxHeader;
                            } while (iVar1 != 0);
                        }
                        if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                            break;
                        imageSource = (ushort*)((int)imageSource + 3);
                        iVar1 = _length + 1;
                        do {
                            *_drawingPosition = fillColorUnk;
                            _drawingPosition = _drawingPosition + 1;
                            iVar1 = iVar1 + -1;
                        } while (iVar1 != 0);
                    }
                    _drawingPosition = (ushort*)((int)_drawingPosition + width);
                    height = height + -1;
                    imageSource = (ushort*)_tgxHeader;
                } while (0 < height);
            }
        }

    }
}
}
