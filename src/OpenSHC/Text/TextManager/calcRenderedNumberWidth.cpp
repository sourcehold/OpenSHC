#include "../TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Computes the total pixel width needed to render integer param_1 using digit glyphs from GMImageHeaders.
      Processes each decimal place (100000 down to units), looks up the glyph width for each digit with a font-set
      offset derived from param_2 (0=small, 1=medium, 2=large, 3=xlarge) and sums widths minus 2px kerning per digit.
      If param_1 == -1, returns the width of a special placeholder glyph for the given font size.
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A4D0
    int TextManager::calcRenderedNumberWidth(int number, int fontSet)
    {
        int fullWidth = 0;

        if (number == -1) {
            int pictureOffset;
            if (fontSet == 0) {
                pictureOffset = 10;
            } else if (fontSet == 1) {
                pictureOffset = 21;
            } else if (fontSet == 2) {
                pictureOffset = 32;
            } else {
                pictureOffset = 43;
            }
            return DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + pictureOffset].width - 2;
        }

        int numberPicOffset;

        numberPicOffset = number / 100000;
        if (numberPicOffset) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth
                += DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width
                - 2;
        }

        numberPicOffset = number / 10000;
        if (numberPicOffset) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth
                += DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width
                - 2;
        }

        numberPicOffset = number / 1000;
        if (numberPicOffset) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth
                += DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width
                - 2;
        }

        numberPicOffset = number / 100;
        if (numberPicOffset) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth
                += DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width
                - 2;
        }

        numberPicOffset = number / 10;
        if (numberPicOffset) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth
                += DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width
                - 2;
        }

        numberPicOffset = number % 10;
        if (fontSet == 1) {
            numberPicOffset += 11;
        } else if (fontSet == 2) {
            numberPicOffset += 22;
        } else if (fontSet == 3) {
            numberPicOffset += 33;
        }
        return fullWidth
            + DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[146] + numberPicOffset].width + -2;
    }

}
}
