#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469E10
    int FontSizeClass::getCharWidthUnk(byte charUnk)
    {
        int _width = 0;
        if (this->fontStartImageId_0x8 == -1) {
            this->fontStartImageId_0x8
                = GMTotalPicturesProcessed::instance[this->fontGmID_0x0] + this->numberOfFontStartInGm_0x4 - 1;
        }

        int const imageSeqID
            = DAT_TextInputDefinedData::instance
                  .CharToImageSeqIDMapping[DAT_TextManagerObject::instance.alternativeCodePageUsedUnk][charUnk];

        if (imageSeqID == -1) {
            if (charUnk >= ' ') {
                return this->whiteSpaceWidth_0x1c;
            }
        } else {
            _width = DAT_GMImageHeaders::instance.imh[this->fontStartImageId_0x8 + imageSeqID].width
                + this->letterSpacing_0x18;
        }
        return _width;
    }

}
}
