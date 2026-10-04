#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469A70
    int FontSizeClass::getWidthOfText(char* text, int length)
    {
        int _currentLineWidthUnk = 0;
        int _maxSingleLineWidth = -1;

        int local_c = DAT_TextManagerObject::instance.field9_0x24;
        if (DAT_TextManagerObject::instance.field9_0x24 <= DAT_TextManagerObject::instance.field10_0x28) {
            local_c = DAT_TextManagerObject::instance.field10_0x28;
        }

        int iVar1 = 0;
        if (this->fontStartImageId_0x8 == -1) {
            this->fontStartImageId_0x8
                = GMTotalPicturesProcessed::instance[this->fontGmID_0x0] + -1 + this->numberOfFontStartInGm_0x4;
        }

        for (int _textIndex = 0; _textIndex < length; ++_textIndex) {
            byte _char = text[_textIndex];

            int imageID
                = DAT_TextInputDefinedData::instance
                      .CharToImageSeqIDMapping[DAT_TextManagerObject::instance.alternativeCodePageUsedUnk][_char];
            if (imageID == -1) {
                if (_char >= ' ') {
                    _currentLineWidthUnk += this->whiteSpaceWidth_0x1c;
                } else if (_char == '\n' && _currentLineWidthUnk > _maxSingleLineWidth) {
                    _maxSingleLineWidth = _currentLineWidthUnk;
                    _currentLineWidthUnk = 0;
                }
            } else {
                imageID += this->fontStartImageId_0x8;
                if (local_c != 0) {
                    local_c = 0;

                    if (this->lineHeight_0x14 == 27) {
                        iVar1 = 19;
                    }

                    if (this->lineHeight_0x14 == 20) {
                        iVar1 = 20;
                    }

                    if (iVar1 != 0) {
                        _currentLineWidthUnk += 3
                            + DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[156] + iVar1 - 1]
                                  .width
                            - DAT_GMImageHeaders::instance.imh[imageID].width - this->letterSpacing_0x18;
                    }
                }
                _currentLineWidthUnk += DAT_GMImageHeaders::instance.imh[imageID].width + this->letterSpacing_0x18;
            }
        }
        if (_currentLineWidthUnk <= _maxSingleLineWidth) {
            _currentLineWidthUnk = _maxSingleLineWidth;
        }

        return _currentLineWidthUnk;
    }

}
}
