#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CEB0
        void TextureRenderCore::drawBitmapFaceWithBlendUnk(
            int bitmapFaceIndex, int xPos, int yPos, int colorOrBlendOrGammaUnk)
        {
            ushort uVar1;
            int _pixelToLineJump;
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            int iVar7;
            int _widthInByte;
            ushort* _surfacePtr;
            ushort* _bitmapFacePtr;
            uint uVar8;
            uint uVar9;
            int iVar10;
            int local_c;
            int local_8;
            iVar7 = colorOrBlendOrGammaUnk;
            if (colorOrBlendOrGammaUnk == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace, this)(
                    bitmapFaceIndex, xPos, yPos);
            }
            if (colorOrBlendOrGammaUnk != 0x20) {
                _bitmapFacePtr = (ushort*)(bitmapFaceIndex * 0x2100 + (int)this->bitmapsFaces_0x94);
                iVar10 = 0x20 - colorOrBlendOrGammaUnk;
                if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_MAP_GAME) {
                    _pixelToLineJump = 0xf98;
                    _widthInByte = 0x1fb0;
                    this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                } else if (this->drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA) {
                    _pixelToLineJump = AlphaAndButtonSurfaceObj::instance.currentImageWidth + -0x40;
                    _widthInByte = AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2;
                    this->currentRenderSurface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
                } else {
                    _pixelToLineJump = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine / 2 + -0x40;
                    _widthInByte = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                    this->currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                }
                _surfacePtr = (ushort*)((int)this->currentRenderSurface + xPos * 2 + _widthInByte * yPos);
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                    local_8 = 0x42;
                    do {
                        local_c = 0x10;
                        colorOrBlendOrGammaUnk = (int)_bitmapFacePtr;
                        do {
                            if (*(ushort*)colorOrBlendOrGammaUnk != COL_MAGENTA::instance.shortValue) {
                                uVar9 = (uint)*_surfacePtr;
                                uVar8 = (uint) * (ushort*)colorOrBlendOrGammaUnk;
                                _widthInByte = (uVar8 & 0x7e0) * iVar10;
                                iVar2 = (uVar9 & 0x7e0) * iVar7;
                                iVar3 = (uVar8 & 0xf800) * iVar10;
                                iVar4 = (uVar9 & 0xf800) * iVar7;
                                iVar5 = (uVar8 & 0x1f) * iVar10;
                                iVar6 = (uVar9 & 0x1f) * iVar7;
                                *_surfacePtr = ((ushort)(_widthInByte / 32) & 0x7e0) + ((ushort)(iVar2 / 32) & 0x7e0)
                                    | ((ushort)(iVar3 / 32) & 0xf800) + ((ushort)(iVar4 / 32) & 0xf800)
                                    | (short)(iVar5 / 32) + (short)(iVar6 / 32);
                            }
                            if (*(ushort*)(colorOrBlendOrGammaUnk + 2) != COL_MAGENTA::instance.shortValue) {
                                uVar9 = (uint)_surfacePtr[1];
                                uVar8 = (uint) * (ushort*)(colorOrBlendOrGammaUnk + 2);
                                _widthInByte = (uVar8 & 0x7e0) * iVar10;
                                iVar2 = (uVar9 & 0x7e0) * iVar7;
                                iVar3 = (uVar8 & 0xf800) * iVar10;
                                iVar4 = (uVar9 & 0xf800) * iVar7;
                                iVar5 = (uVar8 & 0x1f) * iVar10;
                                iVar6 = (uVar9 & 0x1f) * iVar7;
                                _surfacePtr[1] = ((ushort)(_widthInByte / 32) & 0x7e0) + ((ushort)(iVar2 / 32) & 0x7e0)
                                    | ((ushort)(iVar3 / 32) & 0xf800) + ((ushort)(iVar4 / 32) & 0xf800)
                                    | (short)(iVar5 / 32) + (short)(iVar6 / 32);
                            }
                            if (*(ushort*)(colorOrBlendOrGammaUnk + 4) != COL_MAGENTA::instance.shortValue) {
                                uVar9 = (uint)_surfacePtr[2];
                                uVar8 = (uint) * (ushort*)(colorOrBlendOrGammaUnk + 4);
                                _widthInByte = (uVar8 & 0x7e0) * iVar10;
                                iVar2 = (uVar9 & 0x7e0) * iVar7;
                                iVar3 = (uVar8 & 0xf800) * iVar10;
                                iVar4 = (uVar9 & 0xf800) * iVar7;
                                iVar5 = (uVar8 & 0x1f) * iVar10;
                                iVar6 = (uVar9 & 0x1f) * iVar7;
                                _surfacePtr[2] = ((ushort)(_widthInByte / 32) & 0x7e0) + ((ushort)(iVar2 / 32) & 0x7e0)
                                    | ((ushort)(iVar3 / 32) & 0xf800) + ((ushort)(iVar4 / 32) & 0xf800)
                                    | (short)(iVar5 / 32) + (short)(iVar6 / 32);
                            }
                            if (*(ushort*)(colorOrBlendOrGammaUnk + 6) != COL_MAGENTA::instance.shortValue) {
                                uVar9 = (uint)_surfacePtr[3];
                                uVar8 = (uint) * (ushort*)(colorOrBlendOrGammaUnk + 6);
                                _widthInByte = (uVar8 & 0x7e0) * iVar10;
                                iVar2 = (uVar9 & 0x7e0) * iVar7;
                                iVar3 = (uVar8 & 0xf800) * iVar10;
                                iVar4 = (uVar9 & 0xf800) * iVar7;
                                iVar5 = (uVar8 & 0x1f) * iVar10;
                                iVar6 = (uVar9 & 0x1f) * iVar7;
                                _surfacePtr[3] = ((ushort)(_widthInByte / 32) & 0x7e0) + ((ushort)(iVar2 / 32) & 0x7e0)
                                    | ((ushort)(iVar3 / 32) & 0xf800) + ((ushort)(iVar4 / 32) & 0xf800)
                                    | (short)(iVar5 / 32) + (short)(iVar6 / 32);
                            }
                            _bitmapFacePtr = (ushort*)(colorOrBlendOrGammaUnk + 8);
                            _surfacePtr = _surfacePtr + 4;
                            local_c = local_c + -1;
                            colorOrBlendOrGammaUnk = (int)_bitmapFacePtr;
                        } while (local_c != 0);
                        _surfacePtr = _surfacePtr + _pixelToLineJump;
                        local_8 = local_8 + -1;
                    } while (local_8 != 0);
                }
                yPos = 0x42;
                do {
                    bitmapFaceIndex = 0x40;
                    do {
                        uVar1 = *_bitmapFacePtr;
                        _bitmapFacePtr = _bitmapFacePtr + 1;
                        if (uVar1 != COL_MAGENTA::instance.shortValue) {
                            uVar8 = (uint)uVar1;
                            iVar7 = (uVar8 & 0x3e0) * colorOrBlendOrGammaUnk;
                            iVar10 = (uVar8 & 0x7c00) * colorOrBlendOrGammaUnk;
                            _widthInByte = (uVar8 & 0x1f) * colorOrBlendOrGammaUnk;
                            *_surfacePtr = (ushort)(iVar7 / 32) & 0x3e0 | (ushort)(iVar10 / 32) & 0x7c00
                                | (ushort)(_widthInByte / 32);
                        }
                        _surfacePtr = _surfacePtr + 1;
                        bitmapFaceIndex = bitmapFaceIndex + -1;
                    } while (bitmapFaceIndex != 0);
                    _surfacePtr = _surfacePtr + _pixelToLineJump;
                    yPos = yPos + -1;
                } while (yPos != 0);
            }
        }

    }
}
}
