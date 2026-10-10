#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_00ec0840.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00ed3110.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D6F60
    void Helpers::ParseCampaignMapHotspotBitmap()
    {
        byte bVar2;
        FILE* _File;
        GFXRelatedBuffer1* pGVar3;
        int* piVar4;
        void* dstBuffer;
        size_t sVar5;
        int iVar6;
        int iVar7;
        short sVar8;
        int iVar9;
        bool bVar10;
        long local_1c;
        int local_18;
        int local_14;
        GFXRelatedBuffer1* local_10;
        void* local_c;
        FILE* local_8;
        void* local_4;
        _File = MACRO_CALL(OS_Func::_fopen)("gfx8\\campaign_map_england_hotspots.bmp", "rb");
        INT_00ed3110::instance = 1;
        pGVar3 = DAT_00ec0840::ptr;
        do {
            pGVar3->field0_0x0 = 0;
            pGVar3 = (GFXRelatedBuffer1*)&pGVar3->field120_0x7a;
        } while ((int)pGVar3 < 0xed2630);
        piVar4 = &DAT_ARRAY_00ed26d0::instance[1].y;
        do {
            ((XYPair*)(piVar4 + -1))->x = 0x40;
            *piVar4 = 0x40;
            piVar4 = piVar4 + 2;
        } while ((int)piVar4 < 0xed277c);
        if (_File != (FILE*)0x0) {
            local_8 = _File;
            dstBuffer = MACRO_CALL(OS_Func::_malloc)(0x428);
            local_4 = dstBuffer;
            if (dstBuffer == (void*)0x0) {
                MACRO_CALL(OS_Func::_fclose)(_File);
                return;
            }
            MACRO_CALL(OS_Func::_fseek)(_File, 0xe, FILE_BEGIN);
            sVar5 = MACRO_CALL(OS_Func::_fread)(dstBuffer, 1, 0x428, _File);
            if (sVar5 != 0x428) {
                MACRO_CALL(OS_Func::_fclose)(_File);
                MACRO_CALL(OS_Func::_free_base)(dstBuffer);
                return;
            }
            iVar6 = *(int*)((int)dstBuffer + 8);
            bVar10 = iVar6 < 0;
            if (bVar10) {
                iVar6 = -iVar6;
            }
            if (*(int*)((int)dstBuffer + 4) == 800 && iVar6 == 600) {
                MACRO_CALL(OS_Func::_fseek)(_File, 10, FILE_BEGIN);
                MACRO_CALL(OS_Func::_fread)(&local_1c, 4, 1, _File);
                MACRO_CALL(OS_Func::_fseek)(_File, (long)((int)(local_1c)), FILE_BEGIN);
                if (bVar10) {
                    iVar6 = 0;
                    do {
                        MACRO_CALL(OS_Func::_fseek)(_File, (long)((int)(iVar6 + local_1c)), FILE_BEGIN);
                        MACRO_CALL(OS_Func::_fread)(
                            (void*)(iVar6 + (int)DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer), 800, 1,
                            _File);
                        iVar6 = iVar6 + 800;
                    } while (iVar6 < 480000);
                } else {
                    iVar9 = 0;
                    iVar6 = 0x74fe0;
                    do {
                        MACRO_CALL(OS_Func::_fseek)(_File, (long)((int)(iVar6 + local_1c)), FILE_BEGIN);
                        MACRO_CALL(OS_Func::_fread)(
                            (void*)(iVar9 + (int)DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer), 800, 1,
                            _File);
                        iVar6 = iVar6 + -800;
                        iVar9 = iVar9 + 800;
                    } while (-800 < iVar6);
                }
                local_18 = 0;
                local_14 = 0;
                local_10 = DAT_00ec0840::ptr;
                local_c = DAT_TextureRenderCoreObject::instance.gmAndGfxImageDataBuffer;
                do {
                    iVar6 = 0;
                    iVar9 = 0;
                    do {
                        byte bVar1 = *(byte*)(iVar6 + (int)local_c);
                        iVar7 = iVar6;
                        if ((bVar1) && (_File = local_8, (byte)(bVar1 - 0x15) < 0x14)) {
                            sVar8 = 1;
                            for (; (iVar7 < 800 && (bVar2 = *(byte*)(iVar7 + (int)local_c), bVar2));
                                iVar7 = iVar7 + 1) {
                                if (bVar2 < 20) {
                                    DAT_ARRAY_00ed26d0::instance[bVar2].y = local_18;
                                    DAT_ARRAY_00ed26d0::instance[bVar2].x = iVar7;
                                } else if (bVar2 != bVar1)
                                    break;
                                sVar8 = sVar8 + 1;
                            }
                            (&local_10->field96_0x62)[iVar9] = '(' - bVar1;
                            (&DAT_00ec0840::instance.field2_0x2)[local_14 + iVar9] = (short)iVar6;
                            (&DAT_00ec0840::instance.field49_0x32)[local_14 + iVar9] = sVar8;
                            iVar9 = iVar9 + 1;
                        }
                        iVar6 = iVar7 + 1;
                    } while ((iVar6 < 800) && (iVar9 < 12));
                    local_18 = local_18 + 1;
                    local_14 = local_14 + 61;
                    local_10->field0_0x0 = (char)iVar9;
                    local_10 = (GFXRelatedBuffer1*)&local_10->field120_0x7a;
                    local_c = (void*)((int)local_c + 800);
                    dstBuffer = local_4;
                } while ((int)local_10 < 0xed2630);
            }
            MACRO_CALL(OS_Func::_free_base)(dstBuffer);
            MACRO_CALL(OS_Func::_fclose)(_File);
        }
        return;
    }

}
}
