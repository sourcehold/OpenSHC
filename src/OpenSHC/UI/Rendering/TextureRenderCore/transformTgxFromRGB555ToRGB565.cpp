#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::TgxToken;
        using IO::Graphics::TgxTokenByte;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C9C0
#pragma optimize("", off)
        void TextureRenderCore::transformTgxFromRGB555ToRGB565(ushort* tgxDataPtr, int tgxByteSize)
        {
            TgxTokenByte _pixToken;
            int _lengthOfPixelString;
            int _numBytesLeft;
            TgxTokenByte* _texPtr;
            undefined2 _current555col;
            while (_texPtr = (TgxTokenByte*)tgxDataPtr, _numBytesLeft = tgxByteSize, 0 < _numBytesLeft) {
                _pixToken = *_texPtr & IO::Graphics::TT_TGX_PIXEL_HEADER;
                _lengthOfPixelString = (*_texPtr & 0x1f) + 1;
                tgxByteSize = _numBytesLeft + -1;
                tgxDataPtr = (ushort*)(_texPtr + 1);
                if (_pixToken != IO::Graphics::TT_NEWLINE) {
                    if (_pixToken == IO::Graphics::TT_REPEATING_PIXELS) {
                        _current555col = *tgxDataPtr;
                        *tgxDataPtr = (_current555col & IO::Graphics::TT_TGX_PIXEL_LENGTH)
                            + ((ushort)(_current555col & 0x3e0) >> 5) * 0x40
                            + ((ushort)(_current555col & 0x7c00) >> 10) * 0x800;
                        tgxByteSize = _numBytesLeft + -3;
                        tgxDataPtr = (ushort*)(_texPtr + 3);
                    } else if (_pixToken != IO::Graphics::TT_TRANSPARENT_PIXELS) {
                        do {
                            _current555col = *tgxDataPtr;
                            if (_current555col != 63519) {
                                *tgxDataPtr = (_current555col & IO::Graphics::TT_TGX_PIXEL_LENGTH)
                                    + ((ushort)(_current555col & 0x3e0) >> 5) * 0x40
                                    + ((ushort)(_current555col & 0x7c00) >> 10) * 0x800;
                            }
                            tgxByteSize = tgxByteSize + -2;
                            tgxDataPtr = (ushort*)((int)tgxDataPtr + 2);
                            _lengthOfPixelString = _lengthOfPixelString + -1;
                        } while (0 < _lengthOfPixelString);
                    }
                }
            }
        }
#pragma optimize("", on)

    }
}
}
