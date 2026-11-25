#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ColorChannelMask.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::CCM_RGB555_GREEN;
        using OpenSHC::Rendering::CCM_RGB555_RED;
        using OpenSHC::Rendering::CCM_RGB565_GREEN;
        using OpenSHC::Rendering::CCM_RGB565_RED;
        using OpenSHC::Rendering::CCM_RGB_BLUE;

        // Draws a face bitmap blended by a strength out of 32 (0: drawn plainly, 32: not drawn).
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CEB0
        void TextureRenderCore::drawBitmapFaceWithBlendUnk(
            int bitmapFaceIndex, int xPos, int yPos, int colorOrBlendOrGammaUnk)
        {
            if (colorOrBlendOrGammaUnk == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace, this)(
                    bitmapFaceIndex, xPos, yPos);
                return;
            }
            if (colorOrBlendOrGammaUnk == 32) {
                return;
            }
            // A face bitmap is 64 x 66 pixels; rowSkip is the surface's gap between two face rows
            ushort* face = this->bitmapsFaces_0x94 + bitmapFaceIndex * 66 * 64;
            // Before the switch, as in the original (in the RGB565 branch it loses the match)
            int const faceWeight = 32 - colorOrBlendOrGammaUnk;
            ushort* surface;
            int rowSkip;
            int lineByteWidth;
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                surface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                rowSkip = 4056 - 64;
                lineByteWidth = 4056 * 2;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                surface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                rowSkip = AlphaAndButtonSurfaceObj::instance.currentImageWidth - 64;
                lineByteWidth = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                break;
            default:
                surface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                rowSkip = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 - 64;
                lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            DAT_TextureRenderCoreObject::instance.currentRenderSurface = surface;
            ushort* pixel = (ushort*)((byte*)surface + lineByteWidth * yPos + xPos * 2);
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                // The face weighs 32 - strength and the surface under it the strength
                for (int row = 0; row < 66; ++row) {
                    for (int column = 0; column < 64; ++column) {
                        ushort const color = *face;
                        ++face;
                        // ++pixel in both branches (a single ++pixel after the if loses the match)
                        if (color == (ushort)COL_MAGENTA::instance.shortValue) {
                            ++pixel;
                            continue;
                        }
                        ushort const surfaceColor = *pixel;
                        int const green = (((color & CCM_RGB565_GREEN) * faceWeight / 32) & CCM_RGB565_GREEN)
                            + (((surfaceColor & CCM_RGB565_GREEN) * colorOrBlendOrGammaUnk / 32) & CCM_RGB565_GREEN);
                        int const red = (((color & CCM_RGB565_RED) * faceWeight / 32) & CCM_RGB565_RED)
                            + (((surfaceColor & CCM_RGB565_RED) * colorOrBlendOrGammaUnk / 32) & CCM_RGB565_RED);
                        int const blue = (color & CCM_RGB_BLUE) * faceWeight / 32
                            + (surfaceColor & CCM_RGB_BLUE) * colorOrBlendOrGammaUnk / 32;
                        *pixel = (ushort)(green | red | blue);
                        ++pixel;
                    }
                    pixel += rowSkip;
                }
                return;
            }
            // fixme: RGB555 weighs the face by the strength, not 32 - strength, and leaves out the surface under it
            for (int row = 0; row < 66; ++row) {
                for (int column = 0; column < 64; ++column) {
                    ushort const color = *face;
                    ++face;
                    if (color != (ushort)COL_MAGENTA::instance.shortValue) {
                        // One local per channel (one expression loses the match: the RGB565 loop then puts red first)
                        int const green = ((color & CCM_RGB555_GREEN) * colorOrBlendOrGammaUnk / 32) & CCM_RGB555_GREEN;
                        int const red = ((color & CCM_RGB555_RED) * colorOrBlendOrGammaUnk / 32) & CCM_RGB555_RED;
                        int const blue = (color & CCM_RGB_BLUE) * colorOrBlendOrGammaUnk / 32;
                        *pixel = (ushort)(green | red | blue);
                    }
                    ++pixel;
                }
                pixel += rowSkip;
            }
        }

    }
}
}
