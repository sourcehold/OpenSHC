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
            // copies the open tab's parts that reach over the map onto the map surface, all but the magenta pixels
            int const tab = this->activeMenuTabIndex;
            if (tab == 0) {
                return;
            }
            // the zero-based tab as a value of its own (tab - 1 written into the index loses the match)
            int const tabIndex = tab - 1;
            // a tab's ten records (x, y, width, height) take five rows of eight ints; -1 ends them
            if (DAT_BlendingDefinedData::instance.field_0x3014[tabIndex * 5][0] == -1) {
                return;
            }
            // the asm below names COL_MAGENTA, which inline asm can only do once C++ code has instantiated it
            (void)sizeof(COL_MAGENTA::instance);
            // the record index once more, as the original computes it a second time (one shared index loses the match)
            int const record = tabIndex * 5;
            // four pointers stepping through the records, as the original keeps them (one index loses the match)
            int* width = &DAT_BlendingDefinedData::instance.field_0x3014[record][2];
            int* x = &DAT_BlendingDefinedData::instance.field_0x3014[record][0];
            int* height = &DAT_BlendingDefinedData::instance.field_0x3014[record][3];
            int* y = &DAT_BlendingDefinedData::instance.field_0x3014[record][1];
            // the end test at the bottom, as in the original (in the for's header it loses the match)
            for (;;) {
                // -2: the records after it lie outside the 800 pixels of the menu, so 800x600 stops here
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
                if (*x == -1) {
                    break;
                }
            }
        }

    }
}
}
