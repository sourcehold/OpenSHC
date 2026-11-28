#include "../TextManager.func.hpp"

#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Text {

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
        int const divisors[] = { 100000, 10000, 1000, 100, 10 };
        for (int i = 0; i < countof(divisors); ++i) {
            int numberPicOffset = number / divisors[i];
            if (numberPicOffset == 0) {
                continue;
            }
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
        int numberPicOffset = number % 10;
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
