#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using Rendering::ColorMode;

// FUNCTION: STRONGHOLDCRUSADER 0x00453600
void Rendering::ApplyBlending(int param_1)
{
    short* psVar1;
    int iVar2;
    int iVar3;
    void* pvVar4;
    ushort uVar5;
    ushort uVar6;
    ushort uVar7;
    ushort* puVar8;
    int iVar9;
    int iVar10;
    short sVar11;
    uint uVar12;
    ushort* puVar13;
    undefined* puVar14;
    int* local_8;
    pvVar4 = DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
    uVar12 = (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + DAT_RenderMap_DrawSomeY::instance;
    if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
        local_8 = DAT_BlendingDefinedData::instance.field164_0x27fc;
        if (DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start <= (int)uVar12
            && (int)uVar12 < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
            puVar8 = (ushort*)((int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]);
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            iVar9 = param_1 * 0x200;
            iVar2 = param_1 * -0x200;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
                puVar13 = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame + DAT_RenderMap_DrawSomeX::instance
                    + uVar12 * 0xfd8;
                sVar11 = 0x100;
                DAT_WindowAndDirectDraw::instance.unknownSpecificPointer = (undefined*)puVar13;
                do {
                    uVar5 = *puVar8 & 0xffe0 | *(ushort*)(iVar2 + 0xd812d8 + (*puVar8 & 0xffff001f) * 8);
                    uVar6 = uVar5 & 0xfc1f | *(ushort*)(iVar2 + 0xd812da + (uVar5 >> 5 & 0xffff001f) * 8);
                    uVar5 = *(ushort*)(iVar2 + 0xd812dc + (uVar6 >> 10 & 0xffff001f) * 8);
                    uVar7 = *(ushort*)((int)puVar13 + *local_8) & 0xffe0
                        | DAT_BlendFilterArrays::instance[param_1][*(ushort*)((int)puVar13 + *local_8) & 0xffff001f][0];
                    uVar7 = uVar7 & 0xfc1f | *(ushort*)(iVar9 + 0xd7d2da + (uVar7 >> 5 & 0xffff001f) * 8);
                    iVar10 = *local_8;
                    *(ushort*)((int)puVar13 + iVar10)
                        = uVar7 & 0x83ff | *(ushort*)(iVar9 + 0xd7d2dc + (uVar7 >> 10 & 0xffff001f) * 8);
                    psVar1 = (short*)((int)puVar13 + iVar10);
                    *psVar1 = *psVar1 + (uVar6 & 0x3ff | uVar5);
                    puVar8 = puVar8 + 1;
                    local_8 = local_8 + 1;
                    sVar11 = sVar11 + -1;
                } while (sVar11);
            }
            puVar13 = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame + DAT_RenderMap_DrawSomeX::instance
                + uVar12 * 0xfd8;
            sVar11 = 0x100;
            DAT_WindowAndDirectDraw::instance.unknownSpecificPointer = (undefined*)puVar13;
            do {
                uVar5 = *puVar8 & 0xffe0 | *(ushort*)(iVar2 + 0xd812d8 + (*puVar8 & 0xffff001f) * 8);
                uVar6 = uVar5 & 0xf81f | *(ushort*)(iVar2 + 0xd812da + (uVar5 >> 5 & 0xffff003f) * 8);
                uVar5 = *(ushort*)(iVar2 + 0xd812dc + (uint)(uVar6 >> 0xb) * 8);
                uVar7 = *(ushort*)((int)puVar13 + *local_8) & 0xffe0
                    | DAT_BlendFilterArrays::instance[param_1][*(ushort*)((int)puVar13 + *local_8) & 0xffff001f][0];
                uVar7 = uVar7 & 0xf81f | *(ushort*)(iVar9 + 0xd7d2da + (uVar7 >> 5 & 0xffff003f) * 8);
                iVar10 = *local_8;
                *(ushort*)((int)puVar13 + iVar10)
                    = uVar7 & 0x7ff | *(ushort*)(iVar9 + 0xd7d2dc + (uint)(uVar7 >> 0xb) * 8);
                psVar1 = (short*)((int)puVar13 + iVar10);
                *psVar1 = *psVar1 + (uVar6 & 0x7ff | uVar5);
                puVar8 = puVar8 + 1;
                local_8 = local_8 + 1;
                sVar11 = sVar11 + -1;
            } while (sVar11);
        }
    } else {
        local_8 = DAT_BlendingDefinedData::instance.field166_0x2dfc;
        if (DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start <= (int)uVar12
            && (int)uVar12 < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end) {
            iVar2 = DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance];
            if (DAT_BlendFilterArrays::instance[0x20][0x1f][0] == 0) {
                MACRO_CALL(UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            iVar10 = param_1 * 0x200;
            iVar9 = param_1 * -0x200;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
                puVar14 = (undefined*)((int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                    + (uVar12 >> 1) * 0x1fb0 + (DAT_RenderMap_DrawSomeX::instance & 0xfffffffe));
                if (!(uVar12 & 1)) {
                    local_8 = DAT_BlendingDefinedData::instance.field165_0x2bfc;
                }
                sVar11 = 0x40;
                DAT_WindowAndDirectDraw::instance.unknownSpecificPointer = puVar14;
                do {
                    uVar5 = *(ushort*)((int)pvVar4 + *local_8 + iVar2);
                    uVar5 = uVar5 & 0xffe0 | *(ushort*)(iVar9 + 0xd812d8 + (uVar5 & 0xffff001f) * 8);
                    uVar6 = uVar5 & 0xfc1f | *(ushort*)(iVar9 + 0xd812da + (uVar5 >> 5 & 0xffff001f) * 8);
                    uVar5 = *(ushort*)(iVar9 + 0xd812dc + (uVar6 >> 10 & 0xffff001f) * 8);
                    uVar7 = *(ushort*)(puVar14 + local_8[1]) & 0xffe0
                        | DAT_BlendFilterArrays::instance[param_1][*(ushort*)(puVar14 + local_8[1]) & 0xffff001f][0];
                    uVar7 = uVar7 & 0xfc1f | *(ushort*)(iVar10 + 0xd7d2da + (uVar7 >> 5 & 0xffff001f) * 8);
                    iVar3 = local_8[1];
                    *(ushort*)(puVar14 + iVar3)
                        = uVar7 & 0x83ff | *(ushort*)(iVar10 + 0xd7d2dc + (uVar7 >> 10 & 0xffff001f) * 8);
                    *(ushort*)(puVar14 + iVar3) = *(short*)(puVar14 + iVar3) + (uVar6 & 0x3ff | uVar5);
                    local_8 = local_8 + 2;
                    sVar11 = sVar11 + -1;
                } while (sVar11);
            }
            puVar14 = (undefined*)((int)DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
                + (uVar12 >> 1) * 0x1fb0 + (DAT_RenderMap_DrawSomeX::instance & 0xfffffffe));
            if (!(uVar12 & 1)) {
                local_8 = DAT_BlendingDefinedData::instance.field165_0x2bfc;
            }
            sVar11 = 0x40;
            DAT_WindowAndDirectDraw::instance.unknownSpecificPointer = puVar14;
            do {
                uVar5 = *(ushort*)((int)pvVar4 + *local_8 + iVar2);
                uVar5 = uVar5 & 0xffe0 | *(ushort*)(iVar9 + 0xd812d8 + (uVar5 & 0xffff001f) * 8);
                uVar6 = uVar5 & 0xf81f | *(ushort*)(iVar9 + 0xd812da + (uVar5 >> 5 & 0xffff003f) * 8);
                uVar5 = *(ushort*)(iVar9 + 0xd812dc + (uint)(uVar6 >> 0xb) * 8);
                uVar7 = *(ushort*)(puVar14 + local_8[1]) & 0xffe0
                    | DAT_BlendFilterArrays::instance[param_1][*(ushort*)(puVar14 + local_8[1]) & 0xffff001f][0];
                uVar7 = uVar7 & 0xf81f | *(ushort*)(iVar10 + 0xd7d2da + (uVar7 >> 5 & 0xffff003f) * 8);
                iVar3 = local_8[1];
                *(ushort*)(puVar14 + iVar3) = uVar7 & 0x7ff | *(ushort*)(iVar10 + 0xd7d2dc + (uint)(uVar7 >> 0xb) * 8);
                *(ushort*)(puVar14 + iVar3) = *(short*)(puVar14 + iVar3) + (uVar6 & 0x7ff | uVar5);
                local_8 = local_8 + 2;
                sVar11 = sVar11 + -1;
            } while (sVar11);
        }
    }
}

}
