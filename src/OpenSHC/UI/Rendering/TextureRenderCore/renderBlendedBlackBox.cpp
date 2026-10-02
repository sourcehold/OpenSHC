#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;

        /*
          Used surface perpared through PencilRenderCore. --TheRedDaemon   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044F020
        void TextureRenderCore::renderBlendedBlackBox(
            int drawX, int drawY, int drawXEnd, int drawYEnd, int blendStrengthUnk)
        {
            int iVar1;
            ushort uVar2;
            int iVar3;
            int iVar4;
            ushort* _drawPtr;
            iVar1 = (DAT_PencilRenderCore::instance.horizontalByteSize - 2) + (drawX - drawXEnd) * 2;
            if (blendStrengthUnk < 0x41) {
                if (blendStrengthUnk < 0x21)
                    goto LAB_0044f057;
            } else {
                blendStrengthUnk = 0x40;
            }
            blendStrengthUnk = 0x40 - blendStrengthUnk;
        LAB_0044f057:
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            iVar4 = blendStrengthUnk * 0x200;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_555) {
                _drawPtr = (ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                    + drawY * DAT_PencilRenderCore::instance.horizontalByteSize + drawX * 2);
                iVar3 = drawX;
                do {
                    for (; iVar3 <= drawXEnd; iVar3 = iVar3 + 1) {
                        uVar2 = *_drawPtr;
                        if (uVar2 != 0) {
                            *_drawPtr = DAT_BlendFilterArrays::instance[blendStrengthUnk][uVar2 & 0x1f][0]
                                | *(ushort*)(iVar4 + 0xd7d2da + (uint)(uVar2 >> 5 & 0x3f) * 8)
                                | *(ushort*)(iVar4 + 0xd7d2dc + (uint)(uVar2 >> 0xb) * 8);
                        }
                        _drawPtr = _drawPtr + 1;
                    }
                    drawY = drawY + 1;
                    _drawPtr = (ushort*)((int)_drawPtr + iVar1);
                    iVar3 = drawX;
                } while (drawY <= drawYEnd);
            }
            _drawPtr = (ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                + drawY * DAT_PencilRenderCore::instance.horizontalByteSize + drawX * 2);
            iVar3 = drawX;
            do {
                for (; iVar3 <= drawXEnd; iVar3 = iVar3 + 1) {
                    uVar2 = *_drawPtr;
                    if (uVar2 != 0) {
                        *_drawPtr = DAT_BlendFilterArrays::instance[blendStrengthUnk][uVar2 & 0x1f][0]
                            | *(ushort*)(iVar4 + 0xd7d2da + (uint)(uVar2 >> 5 & 0x1f) * 8)
                            | *(ushort*)(iVar4 + 0xd7d2dc + (uVar2 >> 10 & 0x1f) * 8);
                    }
                    _drawPtr = _drawPtr + 1;
                }
                drawY = drawY + 1;
                _drawPtr = (ushort*)((int)_drawPtr + iVar1);
                iVar3 = drawX;
            } while (drawY <= drawYEnd);
        }

    }
}
}
