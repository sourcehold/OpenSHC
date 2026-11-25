#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CE00
        void TextureRenderCore::renderFacesSmallUnk(int facesIndex, int drawX, int drawY)
        {
            // A face bitmap is 64 x 66 pixels; the small face draws every other pixel of every other row
            ushort* face = this->bitmapsFaces_0x94 + facesIndex * 66 * 64;
            ushort* surface;
            int lineByteWidth;
            switch (this->drawBufferChoiceValue) {
            case OpenSHC::Rendering::Enums::RT_MAP_GAME:
                surface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                lineByteWidth = 4056 * 2;
                break;
            case OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA:
                surface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                lineByteWidth = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                break;
            default:
                surface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                lineByteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                break;
            }
            // Stored through the global (this->: quick_diff 0.9903 -> 0.8155)
            DAT_TextureRenderCoreObject::instance.currentRenderSurface = surface;
            ushort* pixel = (ushort*)((byte*)surface + lineByteWidth * drawY + drawX * 2);
            for (int row = 0; row < 33; ++row) {
                ushort* const rowStart = pixel;
                // != keeps the column loop rolled (column < 32: quick_diff 0.9903 -> 0.8348)
                for (int column = 0; column != 32; ++column) {
                    if (*face != (ushort)COL_MAGENTA::instance.shortValue) {
                        *pixel = *face;
                    }
                    ++pixel;
                    face += 2;
                }
                face += 64;
                pixel = rowStart + lineByteWidth / 2;
            }
        }

    }
}
}
