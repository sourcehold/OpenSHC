#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::IO::Graphics::TgxTokenByte;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00451E00
        void TextureRenderCore::renderUnitAnimationWithBlendingUnk(
            int xPosition, int yPosition, int width, int height, byte* imageAddress, int blendStrengthUnk)
        {
            ushort uVar1;
            int iVar2;
            TgxTokenByte TVar3;
            ushort uVar4;
            ushort uVar5;
            int iVar6;
            uint uVar7;
            int iVar8;
            ushort uVar9;
            int iVar10;
            uint uVar11;
            byte bVar13;
            TgxTokenByte bVar12;
            int iVar14;
            uint uVar15;
            byte* pbVar16;
            TgxTokenByte* pTVar17;
            byte* pbVar18;
            ushort* puVar19;
            ushort* puVar20;
            undefined2 uStack_36;
            uint local_14;
            ushort* _colorPaletteRef;
            int local_c;
            int local_8;
            if (DAT_RenderedUnitOwner::instance == 1) {
                DAT_RenderedUnitOwner::instance = 4;
            } else if (DAT_RenderedUnitOwner::instance == 4) {
                DAT_RenderedUnitOwner::instance = 1;
            }
            /*
              According to another comment, this indexes into the right   gmfileheadercolorpalette and accesses the
              color data. --TheRedDaemon
             */
            _colorPaletteRef = (ushort*)(DAT_CurrentlyRenderedSpriteID::instance * 0x1458
                + DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[DAT_RenderedUnitOwner::instance] * 0x200
                + 0x1fea604);
            if (0 < height) {
                if (DAT_TextureRenderCoreObject::instance.mbr_0x70 != 0) {
                    _colorPaletteRef = (ushort*)DAT_TextureRenderCoreObject::instance.mbr_0x70;
                }
                if (blendStrengthUnk < 0x20) {
                    if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
                    }
                    iVar6 = blendStrengthUnk * 0x200;
                    iVar2 = blendStrengthUnk * -0x200;
                    iVar10 = iVar2 + 0xd812d8;
                    if (DAT_TextureRenderCoreObject::instance.isZoom2 == 0) {
                        if (DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                            DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                            local_8 = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                            local_c = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.start;
                            iVar14 = DAT_TextureRenderCoreObject::instance.screenMenuSurfaceHeightRange.end;
                        } else {
                            DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                            local_8 = 0x1fb0;
                            local_c = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                            iVar14 = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end;
                        }
                        if ((yPosition + height <= iVar14) || (height = iVar14 - yPosition, 0 < height)) {
                            if (DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_555) {
                                if (-1 < xPosition) {
                                    if (yPosition < local_c) {
                                        iVar14 = local_c - yPosition;
                                        if (height <= iVar14) {}
                                        height = height - iVar14;
                                        do {
                                            while (true) {
                                                while (true) {
                                                    do {
                                                        pTVar17 = (OpenSHC::IO::Graphics::TgxTokenByte*)(imageAddress);
                                                        bVar12 = *pTVar17 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                        imageAddress = (byte*)(pTVar17 + 1);
                                                    } while (bVar12 == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                                    if (bVar12 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                        break;
                                                    imageAddress = imageAddress + (*pTVar17 & 0xffffff1f) + 1;
                                                }
                                                if (bVar12 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                                    break;
                                                imageAddress = (byte*)(pTVar17 + 2);
                                            }
                                            iVar14 = iVar14 + -1;
                                            yPosition = local_c;
                                        } while (0 < iVar14);
                                    }
                                    puVar19 = (ushort*)((int)DAT_TextureRenderCoreObject::instance.currentRenderSurface + yPosition * local_8
                                        + xPosition * 2);
                                    puVar20 = puVar19;
                                    do {
                                        while (true) {
                                            while (true) {
                                                while (true) {
                                                    TVar3 = *imageAddress & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                                    uVar11 = *imageAddress & 0xffffff1f;
                                                    pTVar17 = (OpenSHC::IO::Graphics::TgxTokenByte*)(imageAddress + 1);
                                                    if (TVar3 != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                                        break;
                                                    puVar19 = puVar19 + uVar11 + 1;
                                                    imageAddress = (byte*)(pTVar17);
                                                }
                                                if (TVar3 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                                    break;
                                                iVar14 = uVar11 + 1;
                                                imageAddress = (byte*)(pTVar17);
                                                do {
                                                    uVar4 = _colorPaletteRef[*imageAddress];
                                                    uVar5 = *puVar19;
                                                    *puVar19
                                                        = (*(ushort*)(iVar10 + (uVar4 & 0xffff001f) * 8)
                                                              | *(ushort*)(iVar2 + 0xd812da
                                                                  + (uVar4 >> 5 & 0xffff003f) * 8)
                                                              | *(ushort*)(iVar2 + 0xd812dc + (uint)(uVar4 >> 0xb) * 8))
                                                        + DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                         [uVar5 & 0xffff001f][0]
                                                        + *(short*)(iVar6 + 0xd7d2da + (uVar5 >> 5 & 0xffff003f) * 8)
                                                        + *(short*)(iVar6 + 0xd7d2dc + (uint)(uVar5 >> 0xb) * 8);
                                                    imageAddress = imageAddress + 1;
                                                    puVar19 = puVar19 + 1;
                                                    iVar14 = iVar14 + -1;
                                                } while (iVar14 != 0);
                                            }
                                            if (TVar3 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                                break;
                                            uVar4 = _colorPaletteRef[*pTVar17];
                                            imageAddress = imageAddress + 2;
                                            iVar14 = uVar11 + 1;
                                            uVar5 = *(ushort*)(iVar10 + (uVar4 & 0xffff001f) * 8);
                                            uVar9 = *(ushort*)(iVar2 + 0xd812da + (uVar4 >> 5 & 0xffff003f) * 8);
                                            uVar4 = *(ushort*)(iVar2 + 0xd812dc + (uint)(uVar4 >> 0xb) * 8);
                                            do {
                                                uVar1 = *puVar19;
                                                *puVar19
                                                    = (DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                      [uVar1 & 0xffff001f][0]
                                                          | *(ushort*)(iVar6 + 0xd7d2da + (uVar1 >> 5 & 0xffff003f) * 8)
                                                          | *(ushort*)(iVar6 + 0xd7d2dc + (uint)(uVar1 >> 0xb) * 8))
                                                    + (uVar5 | uVar9 | uVar4);
                                                puVar19 = puVar19 + 1;
                                                iVar14 = iVar14 + -1;
                                            } while (iVar14 != 0);
                                        }
                                        puVar19 = (ushort*)((int)puVar20 + local_8);
                                        height = height + -1;
                                        imageAddress = (byte*)(pTVar17);
                                        puVar20 = puVar19;
                                    } while (0 < height);
                                }
                            }
                            if (-1 < xPosition) {
                                if (yPosition < local_c) {
                                    iVar14 = local_c - yPosition;
                                    if (height <= iVar14) {}
                                    height = height - iVar14;
                                    do {
                                        while (true) {
                                            while (true) {
                                                do {
                                                    pbVar16 = imageAddress;
                                                    bVar13 = *pbVar16 & 0xe0;
                                                    imageAddress = pbVar16 + 1;
                                                } while (bVar13 == 0x20);
                                                if (bVar13 != 0)
                                                    break;
                                                imageAddress = imageAddress + (*pbVar16 & 0xffffff1f) + 1;
                                            }
                                            if (bVar13 != 0x40)
                                                break;
                                            imageAddress = pbVar16 + 2;
                                        }
                                        iVar14 = iVar14 + -1;
                                        yPosition = local_c;
                                    } while (0 < iVar14);
                                }
                                puVar19
                                    = (ushort*)((int)DAT_TextureRenderCoreObject::instance.currentRenderSurface + yPosition * local_8 + xPosition * 2);
                                puVar20 = puVar19;
                                do {
                                    while (true) {
                                        while (true) {
                                            while (true) {
                                                bVar13 = *imageAddress & 0xe0;
                                                uVar11 = *imageAddress & 0xffffff1f;
                                                pbVar16 = imageAddress + 1;
                                                if (bVar13 != 0x20)
                                                    break;
                                                puVar19 = puVar19 + uVar11 + 1;
                                                imageAddress = pbVar16;
                                            }
                                            if (bVar13 != 0)
                                                break;
                                            iVar14 = uVar11 + 1;
                                            do {
                                                uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                                    | *(ushort*)(iVar10
                                                        + (_colorPaletteRef[*pbVar16] & 0xffff001f) * 8);
                                                uVar5 = uVar4 & 0xfc1f
                                                    | *(ushort*)(iVar2 + 0xd812da + (uVar4 >> 5 & 0xffff001f) * 8);
                                                uVar4 = *puVar19;
                                                *puVar19 = uVar5 & 0x3ff
                                                    | *(ushort*)(iVar2 + 0xd812dc + (uVar5 >> 10 & 0xffff001f) * 8);
                                                uVar4 = uVar4 & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                     [uVar4 & 0xffff001f][0];
                                                uVar4 = uVar4 & 0xfc1f
                                                    | *(ushort*)(iVar6 + 0xd7d2da + (uVar4 >> 5 & 0xffff001f) * 8);
                                                *puVar19 = *puVar19
                                                    + (uVar4 & 0x83ff
                                                        | *(ushort*)(iVar6 + 0xd7d2dc
                                                            + (uVar4 >> 10 & 0xffff001f) * 8));
                                                pbVar16 = pbVar16 + 1;
                                                puVar19 = puVar19 + 1;
                                                iVar14 = iVar14 + -1;
                                                imageAddress = pbVar16;
                                            } while (iVar14 != 0);
                                        }
                                        if (bVar13 != 0x40)
                                            break;
                                        imageAddress = imageAddress + 2;
                                        iVar14 = uVar11 + 1;
                                        uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                            | *(ushort*)(iVar10 + (_colorPaletteRef[*pbVar16] & 0xffff001f) * 8);
                                        uVar5 = uVar4 & 0xfc1f
                                            | *(ushort*)(iVar2 + 0xd812da + (uVar4 >> 5 & 0xffff001f) * 8);
                                        uVar4 = *(ushort*)(iVar2 + 0xd812dc + (uVar5 >> 10 & 0xffff001f) * 8);
                                        do {
                                            uVar9 = *puVar19 & 0xffe0
                                                | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                 [*puVar19 & 0xffff001f][0];
                                            uVar9 = uVar9 & 0xfc1f
                                                | *(ushort*)(iVar6 + 0xd7d2da + (uVar9 >> 5 & 0xffff001f) * 8);
                                            *puVar19
                                                = (uVar9 & 0x83ff
                                                      | *(ushort*)(iVar6 + 0xd7d2dc + (uVar9 >> 10 & 0xffff001f) * 8))
                                                + (uVar5 & 0x3ff | uVar4);
                                            puVar19 = puVar19 + 1;
                                            iVar14 = iVar14 + -1;
                                        } while (iVar14 != 0);
                                    }
                                    puVar19 = (ushort*)((int)puVar20 + local_8);
                                    height = height + -1;
                                    imageAddress = pbVar16;
                                    puVar20 = puVar19;
                                } while (0 < height);
                            }
                        }
                    } else {
                        DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                        uVar11 = xPosition & 1;
                        if ((yPosition + height <= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end)
                            || (height = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end - yPosition, 0 < height)) {
                            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                                if (-1 < xPosition) {
                                    if (yPosition < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
                                        iVar14 = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - yPosition;
                                        if (height <= iVar14) {
                                            DAT_TextureRenderCoreObject::instance.currentRenderSurface
                                                = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                                        }
                                        height = height - iVar14;
                                        do {
                                            while (true) {
                                                while (true) {
                                                    do {
                                                        pbVar16 = imageAddress;
                                                        bVar13 = *pbVar16 & 0xe0;
                                                        imageAddress = pbVar16 + 1;
                                                    } while (bVar13 == 0x20);
                                                    if (bVar13 != 0)
                                                        break;
                                                    imageAddress = imageAddress + (*pbVar16 & 0xffffff1f) + 1;
                                                }
                                                if (bVar13 != 0x40)
                                                    break;
                                                imageAddress = pbVar16 + 2;
                                            }
                                            iVar14 = iVar14 + -1;
                                            yPosition = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                                        } while (0 < iVar14);
                                    }
                                    iVar14 = (int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                                        + ((uint)yPosition >> 1) * 0x1fb0 + (xPosition & 0xfffffffeU);
                                    uVar7 = uVar11;
                                    do {
                                        while (true) {
                                            while (true) {
                                                while (true) {
                                                    local_14 = uVar7;
                                                    bVar13 = *imageAddress & 0xe0;
                                                    uVar7 = *imageAddress & 0xffffff1f;
                                                    pbVar16 = imageAddress + 1;
                                                    if (bVar13 != 0x20)
                                                        break;
                                                    imageAddress = pbVar16;
                                                    uVar7 = local_14 + uVar7 + 1;
                                                }
                                                if (bVar13 != 0)
                                                    break;
                                                iVar8 = uVar7 + 1;
                                                uVar7 = local_14 + iVar8;
                                                do {
                                                    if ((local_14 & 1) == 0) {
                                                        uStack_36 = (undefined2)(local_14 >> 0x10);
                                                        uVar15 = (((uint)(uStack_36) << 0x10)
                                                                     | (uint)(ushort)(_colorPaletteRef[*pbVar16]))
                                                            & 0xffff001f;
                                                        uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                                            | *(ushort*)(iVar10 + uVar15 * 8);
                                                        uVar15 = (((uint)((short)(uVar15 >> 0x10)) << 0x10)
                                                                     | (uint)(ushort)(uVar4 >> 5))
                                                            & 0xffff001f;
                                                        uVar5 = uVar4 & 0xfc1f
                                                            | *(ushort*)(iVar2 + 0xd812da + uVar15 * 8);
                                                        uVar4 = *(ushort*)(iVar14 + local_14);
                                                        *(ushort*)(iVar14 + local_14) = uVar5 & 0x3ff
                                                            | *(ushort*)(iVar2 + 0xd812dc
                                                                + ((((uint)((short)(uVar15 >> 0x10)) << 0x10)
                                                                       | (uint)(ushort)(uVar5 >> 10))
                                                                      & 0xffff001f)
                                                                    * 8);
                                                        uVar4 = uVar4 & 0xffe0
                                                            | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                             [uVar4 & 0xffff001f][0];
                                                        uVar4 = uVar4 & 0xfc1f
                                                            | *(ushort*)(iVar6 + 0xd7d2da
                                                                + (uVar4 >> 5 & 0xffff001f) * 8);
                                                        *(short*)(iVar14 + local_14) = *(short*)(iVar14 + local_14)
                                                            + (uVar4 & 0x83ff
                                                                | *(ushort*)(iVar6 + 0xd7d2dc
                                                                    + (uVar4 >> 10 & 0xffff001f) * 8));
                                                    }
                                                    pbVar16 = pbVar16 + 1;
                                                    local_14 = local_14 + 1;
                                                    iVar8 = iVar8 + -1;
                                                    imageAddress = pbVar16;
                                                } while (iVar8 != 0);
                                            }
                                            if (bVar13 != 0x40)
                                                break;
                                            imageAddress = imageAddress + 2;
                                            uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                                | *(ushort*)(iVar10 + (_colorPaletteRef[*pbVar16] & 0xffff001f) * 8);
                                            uVar5 = uVar4 & 0xfc1f
                                                | *(ushort*)(iVar2 + 0xd812da + (uVar4 >> 5 & 0xffff001f) * 8);
                                            uVar4 = *(ushort*)(iVar2 + 0xd812dc + (uVar5 >> 10 & 0xffff001f) * 8);
                                            iVar8 = uVar7 + 1;
                                            uVar7 = local_14 + iVar8;
                                            do {
                                                if ((local_14 & 1) == 0) {
                                                    uVar9 = *(ushort*)(iVar14 + local_14) & 0xffe0
                                                        | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                         [*(ushort*)(iVar14 + local_14)
                                                                                             & 0xffff001f][0];
                                                    uVar9 = uVar9 & 0xfc1f
                                                        | *(ushort*)(iVar6 + 0xd7d2da + (uVar9 >> 5 & 0xffff001f) * 8);
                                                    *(ushort*)(iVar14 + local_14)
                                                        = (uVar9 & 0x83ff
                                                              | *(ushort*)(iVar6 + 0xd7d2dc
                                                                  + (uVar9 >> 10 & 0xffff001f) * 8))
                                                        + (uVar5 & 0x3ff | uVar4);
                                                }
                                                local_14 = local_14 + 1;
                                                iVar8 = iVar8 + -1;
                                            } while (iVar8 != 0);
                                        }
                                        iVar14 = iVar14 + 0x1fb0;
                                        if (height + -1 < 1) {}
                                        while (true) {
                                            while (true) {
                                                do {
                                                    pbVar18 = pbVar16;
                                                    bVar13 = *pbVar18 & 0xe0;
                                                    pbVar16 = pbVar18 + 1;
                                                } while (bVar13 == 0x20);
                                                if (bVar13 != 0)
                                                    break;
                                                pbVar16 = pbVar16 + (*pbVar18 & 0xffffff1f) + 1;
                                            }
                                            if (bVar13 != 0x40)
                                                break;
                                            pbVar16 = pbVar18 + 2;
                                        }
                                        height = height + -2;
                                        imageAddress = pbVar16;
                                        uVar7 = uVar11;
                                    } while (0 < height);
                                }
                            }
                            if (-1 < xPosition) {
                                if (yPosition < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
                                    iVar14 = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start - yPosition;
                                    if (height <= iVar14) {
                                        DAT_TextureRenderCoreObject::instance.currentRenderSurface
                                            = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                                    }
                                    height = height - iVar14;
                                    do {
                                        while (true) {
                                            while (true) {
                                                do {
                                                    pbVar16 = imageAddress;
                                                    bVar13 = *pbVar16 & 0xe0;
                                                    imageAddress = pbVar16 + 1;
                                                } while (bVar13 == 0x20);
                                                if (bVar13 != 0)
                                                    break;
                                                imageAddress = imageAddress + (*pbVar16 & 0xffffff1f) + 1;
                                            }
                                            if (bVar13 != 0x40)
                                                break;
                                            imageAddress = pbVar16 + 2;
                                        }
                                        iVar14 = iVar14 + -1;
                                        yPosition = DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start;
                                    } while (0 < iVar14);
                                }
                                iVar14 = (int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                                    + ((uint)yPosition >> 1) * 0x1fb0 + (xPosition & 0xfffffffeU);
                                uVar7 = uVar11;
                                do {
                                    while (true) {
                                        while (true) {
                                            while (true) {
                                                local_14 = uVar7;
                                                bVar13 = *imageAddress & 0xe0;
                                                uVar7 = *imageAddress & 0xffffff1f;
                                                pbVar16 = imageAddress + 1;
                                                if (bVar13 != 0x20)
                                                    break;
                                                imageAddress = pbVar16;
                                                uVar7 = local_14 + uVar7 + 1;
                                            }
                                            if (bVar13 != 0)
                                                break;
                                            iVar8 = uVar7 + 1;
                                            uVar7 = local_14 + iVar8;
                                            do {
                                                if ((local_14 & 1) == 0) {
                                                    uStack_36 = (undefined2)(local_14 >> 0x10);
                                                    uVar15 = (((uint)(uStack_36) << 0x10)
                                                                 | (uint)(ushort)(_colorPaletteRef[*pbVar16]))
                                                        & 0xffff001f;
                                                    uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                                        | *(ushort*)(iVar10 + uVar15 * 8);
                                                    uVar15 = (((uint)((short)(uVar15 >> 0x10)) << 0x10)
                                                                 | (uint)(ushort)(uVar4 >> 5))
                                                        & 0xffff003f;
                                                    uVar5 = uVar4 & 0xf81f | *(ushort*)(iVar2 + 0xd812da + uVar15 * 8);
                                                    uVar4 = *(ushort*)(iVar14 + local_14);
                                                    *(ushort*)(iVar14 + local_14) = uVar5 & 0x7ff
                                                        | *(ushort*)(iVar2 + 0xd812dc
                                                            + (((uint)((short)(uVar15 >> 0x10)) << 0x10)
                                                                  | (uint)(ushort)(uVar5 >> 0xb))
                                                                * 8);
                                                    uVar4 = uVar4 & 0xffe0
                                                        | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                         [uVar4 & 0xffff001f][0];
                                                    uVar4 = uVar4 & 0xf81f
                                                        | *(ushort*)(iVar6 + 0xd7d2da + (uVar4 >> 5 & 0xffff003f) * 8);
                                                    *(short*)(iVar14 + local_14) = *(short*)(iVar14 + local_14)
                                                        + (uVar4 & 0x7ff
                                                            | *(ushort*)(iVar6 + 0xd7d2dc + (uint)(uVar4 >> 0xb) * 8));
                                                }
                                                pbVar16 = pbVar16 + 1;
                                                local_14 = local_14 + 1;
                                                iVar8 = iVar8 + -1;
                                                imageAddress = pbVar16;
                                            } while (iVar8 != 0);
                                        }
                                        if (bVar13 != 0x40)
                                            break;
                                        imageAddress = imageAddress + 2;
                                        uVar4 = _colorPaletteRef[*pbVar16] & 0xffe0
                                            | *(ushort*)(iVar10 + (_colorPaletteRef[*pbVar16] & 0xffff001f) * 8);
                                        uVar5 = uVar4 & 0xf81f
                                            | *(ushort*)(iVar2 + 0xd812da + (uVar4 >> 5 & 0xffff003f) * 8);
                                        uVar4 = *(ushort*)(iVar2 + 0xd812dc + (uint)(uVar5 >> 0xb) * 8);
                                        iVar8 = uVar7 + 1;
                                        uVar7 = local_14 + iVar8;
                                        do {
                                            if ((local_14 & 1) == 0) {
                                                uVar9 = *(ushort*)(iVar14 + local_14) & 0xffe0
                                                    | DAT_BlendFilterArrays::instance[blendStrengthUnk]
                                                                                     [*(ushort*)(iVar14 + local_14)
                                                                                         & 0xffff001f][0];
                                                uVar9 = uVar9 & 0xf81f
                                                    | *(ushort*)(iVar6 + 0xd7d2da + (uVar9 >> 5 & 0xffff003f) * 8);
                                                *(ushort*)(iVar14 + local_14)
                                                    = (uVar9 & 0x7ff
                                                          | *(ushort*)(iVar6 + 0xd7d2dc + (uint)(uVar9 >> 0xb) * 8))
                                                    + (uVar5 & 0x7ff | uVar4);
                                            }
                                            local_14 = local_14 + 1;
                                            iVar8 = iVar8 + -1;
                                        } while (iVar8 != 0);
                                    }
                                    iVar14 = iVar14 + 0x1fb0;
                                    if (height + -1 < 1) {}
                                    while (true) {
                                        while (true) {
                                            do {
                                                pbVar18 = pbVar16;
                                                bVar13 = *pbVar18 & 0xe0;
                                                pbVar16 = pbVar18 + 1;
                                            } while (bVar13 == 0x20);
                                            if (bVar13 != 0)
                                                break;
                                            pbVar16 = pbVar16 + (*pbVar18 & 0xffffff1f) + 1;
                                        }
                                        if (bVar13 != 0x40)
                                            break;
                                        pbVar16 = pbVar18 + 2;
                                    }
                                    height = height + -2;
                                    imageAddress = pbVar16;
                                    uVar7 = uVar11;
                                } while (0 < height);
                            }
                        }
                    }
                }
            }
        }

    }
}
}
