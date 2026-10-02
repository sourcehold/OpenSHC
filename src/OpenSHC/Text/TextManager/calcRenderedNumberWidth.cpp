#include "../TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Computes the total pixel width needed to render integer param_1 using digit glyphs from   GMImageHeaders.
      Processes each decimal place (100000 down to units), looks up the glyph width for   each digit with a font-set
      offset derived from param_2 (0=small, 1=medium, 2=large, 3=xlarge),   and sums widths minus 2px kerning per digit.
      If param_1 == -1, returns the width of a special   placeholder glyph for the given font size.      renamed by:
      Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A4D0
    int TextManager::calcRenderedNumberWidth(int param_1, int param_2)
    {
        int iVar2;
        int iVar3 = 0;
        if (param_1 == -1) {
            if (param_2 == 0) {
                iVar3 = 10;
            } else if (param_2 == 1) {
                iVar3 = 0x15;
            } else {
                iVar3 = (-(uint)(param_2 != 2) & 0xb) + 0x20;
            }
            return DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x92] + iVar3].width + -2;
        }
        int iVar1 = param_1 / 100000;
        if (iVar1 != 0) {
            iVar3 = (int)((ulonglong)((longlong)iVar1 * -0x66666667) >> 0x20);
            iVar1 = iVar1 + ((iVar3 >> 2) - (iVar3 >> 0x1f)) * 10;
            if (param_2 == 1) {
                iVar1 = iVar1 + 0xb;
            } else if (param_2 == 2) {
                iVar1 = iVar1 + 0x16;
            } else if (param_2 == 3) {
                iVar1 = iVar1 + 0x21;
            }
            iVar3 = DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x92]].width + -2;
        }
        iVar1 = param_1 / 10000;
        if (iVar1 != 0) {
            iVar2 = (int)((ulonglong)((longlong)iVar1 * -0x66666667) >> 0x20);
            iVar1 = iVar1 + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            if (param_2 == 1) {
                iVar1 = iVar1 + 0xb;
            } else if (param_2 == 2) {
                iVar1 = iVar1 + 0x16;
            } else if (param_2 == 3) {
                iVar1 = iVar1 + 0x21;
            }
            iVar3 = iVar3 + -2
                + (int)DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x92]].width;
        }
        iVar1 = param_1 / 1000;
        if (iVar1 != 0) {
            iVar2 = (int)((ulonglong)((longlong)iVar1 * -0x66666667) >> 0x20);
            iVar1 = iVar1 + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            if (param_2 == 1) {
                iVar1 = iVar1 + 0xb;
            } else if (param_2 == 2) {
                iVar1 = iVar1 + 0x16;
            } else if (param_2 == 3) {
                iVar1 = iVar1 + 0x21;
            }
            iVar3 = iVar3 + -2
                + (int)DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x92]].width;
        }
        iVar1 = param_1 / 100;
        if (iVar1 != 0) {
            iVar2 = (int)((ulonglong)((longlong)iVar1 * -0x66666667) >> 0x20);
            iVar1 = iVar1 + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            if (param_2 == 1) {
                iVar1 = iVar1 + 0xb;
            } else if (param_2 == 2) {
                iVar1 = iVar1 + 0x16;
            } else if (param_2 == 3) {
                iVar1 = iVar1 + 0x21;
            }
            iVar3 = iVar3 + -2
                + (int)DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x92]].width;
        }
        iVar1 = param_1 / 10;
        if (iVar1 != 0) {
            iVar2 = (int)((ulonglong)((longlong)iVar1 * -0x66666667) >> 0x20);
            iVar1 = iVar1 + ((iVar2 >> 2) - (iVar2 >> 0x1f)) * 10;
            if (param_2 == 1) {
                iVar1 = iVar1 + 0xb;
            } else if (param_2 == 2) {
                iVar1 = iVar1 + 0x16;
            } else if (param_2 == 3) {
                iVar1 = iVar1 + 0x21;
            }
            iVar3 = iVar3 + -2
                + (int)DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x92]].width;
        }
        iVar1 = param_1 % 10;
        if (param_2 == 1) {
            iVar1 = iVar1 + 0xb;
        } else if (param_2 == 2) {
            iVar1 = iVar1 + 0x16;
        } else if (param_2 == 3) {
            iVar1 = iVar1 + 0x21;
        }
        return DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x92] + iVar1].width + -2 + iVar3;
    }

}
}
