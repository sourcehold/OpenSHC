#include "../CampaignUnk.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ec02f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00eb9b44.hpp"
#include "OpenSHC/Globals/INT_00eb9b4c.hpp"
#include "OpenSHC/Globals/INT_00ec0838.hpp"
#include "OpenSHC/Globals/INT_00ed2778.hpp"
#include "OpenSHC/Globals/INT_00ed277c.hpp"
#include "OpenSHC/Globals/INT_00ed27b0.hpp"
#include "OpenSHC/Globals/INT_00ed3068.hpp"
#include "OpenSHC/Globals/INT_00ed3110.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb9afc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DCC90
        void CampaignUnk::MenuView_CampaignUnk_Prepare()
        {
            int iVar1;
            int* piVar2;
            int iVar3;
            int iVar4;
            int* piVar5;
            int iVar6;
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            if (!INT_00ed3110::instance) {
                MACRO_CALL(UI::Helpers_Func::ParseCampaignMapHotspotBitmap)();
            }
            iVar3 = 0;
            INT_00ed27b0::instance = 0;
            INT_00eb9b4c::instance = 0;
            INT_00eb9b44::instance = 0;
            if (1 < DAT_GameCore::instance.missionNumber1to20) {
                iVar6 = (DAT_GameCore::instance.missionNumber1to20 + -2) * 0x58;
                piVar2 = (int*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x28);
                iVar4 = 3;
                piVar5 = piVar2;
                do {
                    if (piVar5[0x16] != *piVar5) {
                        /*
                          fixme:this doesn't make sense, clashes with floats
                         */
                        INT_ARRAY_00eb9afc::instance[iVar3] = iVar4 + -2;
                        iVar3 = iVar3 + 1;
                    }
                    if (piVar5[0x17] != piVar5[1]) {
                        INT_ARRAY_00eb9afc::instance[iVar3] = iVar4 + -1;
                        iVar3 = iVar3 + 1;
                    }
                    if (piVar5[0x18] != piVar5[2]) {
                        INT_ARRAY_00eb9afc::instance[iVar3] = iVar4;
                        iVar3 = iVar3 + 1;
                    }
                    if (piVar5[0x19] != piVar5[3]) {
                        INT_ARRAY_00eb9afc::instance[iVar3] = iVar4 + 1;
                        iVar3 = iVar3 + 1;
                    }
                    if (piVar5[26] != piVar5[4]) {
                        INT_ARRAY_00eb9afc::instance[iVar3] = iVar4 + 2;
                        iVar3 = iVar3 + 1;
                    }
                    iVar1 = iVar4 + 3;
                    piVar5 = piVar5 + 5;
                    iVar4 = iVar4 + 5;
                } while (iVar1 < 21);
                DAT_00ec02f4::instance.field0_0x0 = *piVar2;
                DAT_00ec02f4::instance.field1_0x4 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x2c);
                DAT_00ec02f4::instance.field2_0x8 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x30);
                DAT_00ec02f4::instance.field3_0xc = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x34);
                DAT_00ec02f4::instance.field4_0x10 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x38);
                DAT_00ec02f4::instance.field5_0x14 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x3c);
                DAT_00ec02f4::instance.field6_0x18 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x40);
                DAT_00ec02f4::instance.field7_0x1c = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x44);
                DAT_00ec02f4::instance.field8_0x20 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x48);
                DAT_00ec02f4::instance.field9_0x24 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x4c);
                DAT_00ec02f4::instance.field10_0x28 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x50);
                DAT_00ec02f4::instance.field11_0x2c = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x54);
                DAT_00ec02f4::instance.field12_0x30 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x58);
                DAT_00ec02f4::instance.field13_0x34 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x5c);
                DAT_00ec02f4::instance.field14_0x38 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x60);
                DAT_00ec02f4::instance.field15_0x3c = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 100);
                DAT_00ec02f4::instance.field16_0x40 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x68);
                DAT_00ec02f4::instance.field17_0x44 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x6c);
                DAT_00ec02f4::instance.field18_0x48 = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x70);
                DAT_00ec02f4::instance.field19_0x4c = *(undefined4*)((int)DAT_MissionDefinedData::ptr + iVar6 + 0x74);
                INT_00ed27b0::instance = iVar3;
            } else {
                DAT_00ec02f4::instance.field0_0x0 = DAT_MissionDefinedData::instance.field13_0x28.sub.field0_0x0;
                DAT_00ec02f4::instance.field1_0x4 = DAT_MissionDefinedData::instance.field13_0x28.sub.field1_0x4;
                DAT_00ec02f4::instance.field2_0x8 = DAT_MissionDefinedData::instance.field13_0x28.sub.field2_0x8;
                DAT_00ec02f4::instance.field3_0xc = DAT_MissionDefinedData::instance.field13_0x28.sub.field3_0xc;
                DAT_00ec02f4::instance.field4_0x10 = DAT_MissionDefinedData::instance.field13_0x28.sub.field4_0x10;
                DAT_00ec02f4::instance.field5_0x14 = DAT_MissionDefinedData::instance.field13_0x28.sub.field5_0x14;
                DAT_00ec02f4::instance.field6_0x18 = DAT_MissionDefinedData::instance.field13_0x28.sub.field6_0x18;
                DAT_00ec02f4::instance.field7_0x1c = DAT_MissionDefinedData::instance.field13_0x28.sub.field7_0x1c;
                DAT_00ec02f4::instance.field8_0x20 = DAT_MissionDefinedData::instance.field13_0x28.sub.field8_0x20;
                DAT_00ec02f4::instance.field9_0x24 = DAT_MissionDefinedData::instance.field13_0x28.sub.field9_0x24;
                DAT_00ec02f4::instance.field10_0x28 = DAT_MissionDefinedData::instance.field13_0x28.sub.field10_0x28;
                DAT_00ec02f4::instance.field11_0x2c = DAT_MissionDefinedData::instance.field13_0x28.sub.field11_0x2c;
                DAT_00ec02f4::instance.field12_0x30 = DAT_MissionDefinedData::instance.field13_0x28.sub.field12_0x30;
                DAT_00ec02f4::instance.field13_0x34 = DAT_MissionDefinedData::instance.field13_0x28.sub.field13_0x34;
                DAT_00ec02f4::instance.field14_0x38 = DAT_MissionDefinedData::instance.field13_0x28.sub.field14_0x38;
                DAT_00ec02f4::instance.field15_0x3c = DAT_MissionDefinedData::instance.field13_0x28.sub.field15_0x3c;
                DAT_00ec02f4::instance.field16_0x40 = DAT_MissionDefinedData::instance.field13_0x28.sub.field16_0x40;
                DAT_00ec02f4::instance.field17_0x44 = DAT_MissionDefinedData::instance.field13_0x28.sub.field17_0x44;
                DAT_00ec02f4::instance.field18_0x48 = DAT_MissionDefinedData::instance.field13_0x28.sub.field18_0x48;
                DAT_00ec02f4::instance.field19_0x4c = DAT_MissionDefinedData::instance.field13_0x28.sub.field19_0x4c;
            }
            INT_00ed2778::instance = 0;
            if (!INT_00ed27b0::instance) {
                INT_00eb9b4c::instance = 100;
                INT_00eb9b44::instance = timeGetTime();
            }
            INT_00ed277c::instance = 0;
            INT_00ed3068::instance = 0;
            INT_00ec0838::instance = 0;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_01.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_02.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_03.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_04.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_05.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_06.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_07.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_08.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_09.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_10.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_11.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_12.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_13.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_14.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_15.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_16.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_17.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_18.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_19.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGFX8,
                DAT_TextureRenderCoreObject::ptr)("campaign_map_england_20.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("map_pig.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("map_rat.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("map_snake.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("map_wolf.tgx");
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            return;
        }

    }
}
}
