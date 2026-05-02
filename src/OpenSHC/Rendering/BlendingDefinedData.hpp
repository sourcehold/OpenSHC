/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/BlendingDefinedData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x000036F4
    typedef struct BlendingDefinedData {

        int field0_0x0; // 0x00000000 length: 4
        char field1_0x4[10][1000]; // 0x00000004 length: 10000
        int DAT_DefaultPlayerSlotUnitColor[9]; // 0x00002714 length: 36
        int SEC_PlayerSlotUnitColor[9]; // 0x00002738 length: 36
        undefined1 padding_0x275c[160]; // 0x0000275C length: 160
        int field164_0x27fc[256]; // 0x000027FC length: 1024
        int field165_0x2bfc[128]; // 0x00002BFC length: 512
        int field166_0x2dfc[128]; // 0x00002DFC length: 512
        pointer PTR_campaign_map_england[6]; // 0x00002FFC length: 24
        int field168_0x3014[55][8]; // 0x00003014 length: 1760

    } BlendingDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(BlendingDefinedData) == 14068, BlendingDefinedData);
} // namespace Rendering
} // namespace OpenSHC
