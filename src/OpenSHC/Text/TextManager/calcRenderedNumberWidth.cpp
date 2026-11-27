#include "../TextManager.func.hpp"

#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Computes the pixel width of number rendered with the digit glyphs of the slanted font, from the hundred
      thousands down to the units, subtracting 2px of kerning per digit. fontSet selects the digit set (0 small,
      1 medium, 2 large, 3 extra large). -1 returns the width of the placeholder glyph of that set.
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
            return DAT_GMImageHeaders::instance
                       .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + pictureOffset]
                       .width
                - 2;
        }
        // the decimal places are written out: the original has a separate constant division for each
        int numberPicOffset;
        numberPicOffset = number / 100000;
        if (numberPicOffset != 0) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth += DAT_GMImageHeaders::instance
                             .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                             .width
                - 2;
        }
        numberPicOffset = number / 10000;
        if (numberPicOffset != 0) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth += DAT_GMImageHeaders::instance
                             .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                             .width
                - 2;
        }
        numberPicOffset = number / 1000;
        if (numberPicOffset != 0) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth += DAT_GMImageHeaders::instance
                             .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                             .width
                - 2;
        }
        numberPicOffset = number / 100;
        if (numberPicOffset != 0) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth += DAT_GMImageHeaders::instance
                             .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                             .width
                - 2;
        }
        numberPicOffset = number / 10;
        if (numberPicOffset != 0) {
            numberPicOffset %= 10;
            if (fontSet == 1) {
                numberPicOffset += 11;
            } else if (fontSet == 2) {
                numberPicOffset += 22;
            } else if (fontSet == 3) {
                numberPicOffset += 33;
            }
            fullWidth += DAT_GMImageHeaders::instance
                             .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                             .width
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
            + DAT_GMImageHeaders::instance
                  .imh[GMFirstPictureIndex::instance[IO::Graphics::GID_FONT_SLANTED] + numberPicOffset]
                  .width
            - 2;
    }

}
}
