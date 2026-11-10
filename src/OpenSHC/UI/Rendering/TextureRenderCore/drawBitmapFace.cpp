#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CD40
        void TextureRenderCore::drawBitmapFace(int bitmapFaceIndex, int xPos, int yPos)
        {
            // A face bitmap is 64 x 66 pixels; rowSkip is the surface's gap between two face rows
            int rowSkip;
            int lineByteWidth;
            ushort* face = this->bitmapsFaces_0x94 + bitmapFaceIndex * 66 * 64;
            // Stored through the global in each arm (a surface local: quick_diff 0.9804 -> 0.7255; this->: 0.5524)
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                rowSkip = 4056 - 64;
                lineByteWidth = 4056 * 2;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                rowSkip = AlphaAndButtonSurfaceObj::instance.currentImageWidth - 64;
                lineByteWidth = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                break;
            default:
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                rowSkip = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 - 64;
                lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            ushort* pixel = (ushort*)((byte*)DAT_TextureRenderCoreObject::instance.currentRenderSurface
                + lineByteWidth * yPos + xPos * 2);
            for (int row = 0; row < 66; ++row) {
                for (int column = 0; column < 64; ++column) {
                    ushort const color = *face;
                    ++face;
                    if (color != (ushort)COL_MAGENTA::instance.shortValue) {
                        *pixel = color;
                    }
                    ++pixel;
                }
                pixel += rowSkip;
            }
        }

    }
}
}
