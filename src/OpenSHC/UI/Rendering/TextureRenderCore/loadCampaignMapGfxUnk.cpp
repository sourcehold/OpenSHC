#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::ColorMode;

        /*
          The four pixel conversions are written out rather than looped: MSVC1400 does not unroll,
          so the body repeated four times in the original means the source repeats it four times.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00454CB0
        void TextureRenderCore::loadCampaignMapGfxUnk()
        {
            ushort _red;
            ushort _green;
            ushort _blue;
            ushort uVar3;
            byte* pbVar4;
            int iVar5;
            ushort* _campaignMapPtrUnk;
            undefined** _campaignActGfx8Ptr;
            byte local_304[768];
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
                    _green = pbVar4[1];
                    _red = pbVar4[0];
                    _blue = pbVar4[2] >> 3;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfffc)) * 8);
                    } else {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfff8)) * 4 | 0x8000);
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    _campaignMapPtrUnk[-1] = uVar3;
                    _green = pbVar4[4];
                    _red = pbVar4[3];
                    _blue = pbVar4[5] >> 3;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfffc)) * 8);
                    } else {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfff8)) * 4 | 0x8000);
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    *_campaignMapPtrUnk = uVar3;
                    _green = pbVar4[7];
                    _red = pbVar4[6];
                    _blue = pbVar4[8] >> 3;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfffc)) * 8);
                    } else {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfff8)) * 4 | 0x8000);
                    }
                    if (uVar3 == 0xfc1f) {
                        uVar3 = 0xf81f;
                    }
                    _campaignMapPtrUnk[1] = uVar3;
                    _green = pbVar4[10];
                    _red = pbVar4[9];
                    _blue = pbVar4[11] >> 3;
                    if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfffc)) * 8);
                    } else {
                        uVar3 = (ushort)(_blue + (((_red & 0xfff8) * 0x20) + (_green & 0xfff8)) * 4 | 0x8000);
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
            } while (_campaignActGfx8Ptr < (undefined**)(DAT_BlendingDefinedData::instance.campaign_map_england) + 6);
        }

    }
}
}
