/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/TextInputDefinedData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000734
    typedef struct TextInputDefinedData {

        int field0_0x0[11]; // 0x00000000 length: 44
        int field1_0x2c[22]; // 0x0000002C length: 88
        byte DAT_UserTextHandler_CharacterFilter_B_1_8_9[256]; // 0x00000084 length: 256
        byte DAT_UserTextHandler_CharacterFilter_A_2_3[256]; // 0x00000184 length: 256
        short field4_0x284[2][256]; // 0x00000284 length: 1024
        int field5_0x684[8][2]; // 0x00000684 length: 64
        int field6_0x6c4[10]; // 0x000006C4 length: 40
        string field7_0x6ec; // 0x000006EC length: 4
        string field8_0x6f0; // 0x000006F0 length: 6
        undefined1 padding_0x6f6[2]; // 0x000006F6 length: 2
        string field11_0x6f8; // 0x000006F8 length: 4
        string field12_0x6fc; // 0x000006FC length: 6
        undefined1 padding_0x702[2]; // 0x00000702 length: 2
        string field15_0x704; // 0x00000704 length: 4
        string field16_0x708; // 0x00000708 length: 6
        undefined1 padding_0x70e[2]; // 0x0000070E length: 2
        string field19_0x710; // 0x00000710 length: 4
        string field20_0x714; // 0x00000714 length: 6
        undefined1 padding_0x71a[2]; // 0x0000071A length: 2
        string field23_0x71c; // 0x0000071C length: 4
        string field24_0x720; // 0x00000720 length: 6
        undefined1 padding_0x726[2]; // 0x00000726 length: 2
        string field27_0x728; // 0x00000728 length: 4
        string field28_0x72c; // 0x0000072C length: 6
        undefined1 padding_0x732[2]; // 0x00000732 length: 2

    } TextInputDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TextInputDefinedData) == 1844, TextInputDefinedData);
} // namespace UI
} // namespace OpenSHC
