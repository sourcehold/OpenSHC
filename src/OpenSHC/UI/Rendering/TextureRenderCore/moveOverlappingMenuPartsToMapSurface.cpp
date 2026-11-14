#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The copy loop is handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x00454F00
        void TextureRenderCore::moveOverlappingMenuPartsToMapSurface()
        {
            // copies the parts of the open menu tab that reach over the map from the menu surface onto the map
            // surface, all but the magenta pixels; the tab's records hold x, y, width and height, -1 ends them and
            // -2 marks the ones that only apply above 800x600
            int const tab = this->activeMenuTabIndex;
            if (tab == 0) {
                return;
            }
            if (DAT_BlendingDefinedData::instance.field_0x3014[(tab - 1) * 5][0] == -1) {
                return;
            }
            // the asm below names COL_MAGENTA, which inline asm can only do once C++ code has instantiated it
            (void)sizeof(COL_MAGENTA::instance);
            // the index in a local: the original computes it again here (inline: 98 instructions to its 100)
            int const record = (tab - 1) * 5;
            int* width = &DAT_BlendingDefinedData::instance.field_0x3014[record][2];
            int* x = &DAT_BlendingDefinedData::instance.field_0x3014[record][0];
            int* height = &DAT_BlendingDefinedData::instance.field_0x3014[record][3];
            int* y = &DAT_BlendingDefinedData::instance.field_0x3014[record][1];
            do {
                if (*x == -2) {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                        return;
                    }
                    y += 4;
                    height += 4;
                    width += 4;
                    x += 4;
                }
                ushort* const screen = (ushort*)((byte*)DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu
                    + (*y + DAT_MenuHandlerState::instance.y)
                        * DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine
                    + (DAT_MenuHandlerState::instance.x + *x) * 2);
                // the map surface is 4056 pixels wide
                ushort* const map = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                    + (*y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY
                          + DAT_MenuHandlerState::instance.y)
                        * 4056
                    + *x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                    + DAT_MenuHandlerState::instance.x;
                int const mapLineJump = (4056 - *width) * 2;
                int const screenLineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine - *width * 2;
                int const partHeight = *height;
                int const partWidth = *width;
                // clang-format off
                __asm {
                    mov esi, screen
                    mov edi, map
                    mov ecx, partHeight
                    mov bx, COL_MAGENTA::instance.shortValue
                rowLoop:
                    mov edx, partWidth
                pixelLoop:
                    mov ax, word ptr [esi]
                    cmp ax, bx
                    je skipPixel
                    mov word ptr [edi], ax
                skipPixel:
                    add esi, 2
                    add edi, 2
                    sub edx, 1
                    jne pixelLoop
                    add esi, screenLineJump
                    add edi, mapLineJump
                    sub ecx, 1
                    jne rowLoop
                }
                // clang-format on
                y += 4;
                height += 4;
                width += 4;
                x += 4;
            } while (*x != -1);
        }

    }
}
}
