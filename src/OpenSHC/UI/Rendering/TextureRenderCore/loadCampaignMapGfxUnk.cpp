#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::ColorMode;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00454CB0
        void TextureRenderCore::loadCampaignMapGfxUnk()
        {
            byte bVar1;
            short sVar2;
            ushort uVar3;
            byte* pbVar4;
            int iVar5;
            ushort* _campaignMapPtrUnk;
            undefined** _campaignActGfx8Ptr;
            byte local_304[768];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&_campaignActGfx8Ptr;
            _campaignActGfx8Ptr = (undefined**)(DAT_BlendingDefinedData::instance.campaign_map_england);
            _campaignMapPtrUnk = this->campaignMapColorMapsUnk_0x16c886[0] + 1;
            do {
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_GFX8, (char const*)((int)(*_campaignActGfx8Ptr)));
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readFirstPartOfCurrentResourceIntoMemory,
                    DAT_ResourceManager::ptr)(local_304, 0x300, "act");
                pbVar4 = local_304;
                iVar5 = 0x40;
                do {
                    sVar2 = (*pbVar4 & 0xfff8) * 0x20;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(pbVar4[2] >> 3) + (sVar2 + (pbVar4[1] & 0xfffc)) * 8;
                    } else {
                        uVar3 = (ushort)(pbVar4[2] >> 3) + (sVar2 + (pbVar4[1] & 0xfff8)) * 4 | 0x8000;
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    bVar1 = pbVar4[3];
                    _campaignMapPtrUnk[-1] = uVar3;
                    sVar2 = (bVar1 & 0xfff8) * 0x20;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(pbVar4[5] >> 3) + (sVar2 + (pbVar4[4] & 0xfffc)) * 8;
                    } else {
                        uVar3 = (ushort)(pbVar4[5] >> 3) + (sVar2 + (pbVar4[4] & 0xfff8)) * 4 | 0x8000;
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    bVar1 = pbVar4[6];
                    *_campaignMapPtrUnk = uVar3;
                    sVar2 = (bVar1 & 0xfff8) * 0x20;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(pbVar4[8] >> 3) + (sVar2 + (pbVar4[7] & 0xfffc)) * 8;
                    } else {
                        uVar3 = (ushort)(pbVar4[8] >> 3) + (sVar2 + (pbVar4[7] & 0xfff8)) * 4 | 0x8000;
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    bVar1 = pbVar4[9];
                    _campaignMapPtrUnk[1] = uVar3;
                    sVar2 = (bVar1 & 0xfff8) * 0x20;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(pbVar4[0xb] >> 3) + (sVar2 + (pbVar4[10] & 0xfffc)) * 8;
                    } else {
                        uVar3 = (ushort)(pbVar4[0xb] >> 3) + (sVar2 + (pbVar4[10] & 0xfff8)) * 4 | 0x8000;
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    _campaignMapPtrUnk[2] = uVar3;
                    _campaignMapPtrUnk = _campaignMapPtrUnk + 4;
                    pbVar4 = pbVar4 + 0xc;
                    iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
                _campaignActGfx8Ptr = _campaignActGfx8Ptr + 1;
            } while ((int)_campaignActGfx8Ptr < 0xab8730);
            ;
        }

    }
}
}
