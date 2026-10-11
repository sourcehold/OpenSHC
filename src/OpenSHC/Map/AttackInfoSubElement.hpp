/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSubElement.hpp'
*/

#pragma once

#include "OpenSHC/Map/AttackInfoSomeArrayElement.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::AttackInfoSomeArrayElement;

#pragma pack(push, 1)
    // SIZE: 0x000177BC
    typedef struct AttackInfoSubElement {

        int currentPlayerID_OR_attackedPlayerID_OR_one; // 0x00000000 length: 4
        int hack1; // 0x00000004 length: 4
        int hack2; // 0x00000008 length: 4
        int hack3; // 0x0000000C length: 4
        int field4_0x10[4000]; // 0x00000010 length: 16000
        undefined1 padding_0x3e90[16]; // 0x00003E90 length: 16
        int someMinimumDistance; // 0x00003EA0 length: 4
        int field22_0x3ea4; // 0x00003EA4 length: 4
        int field_0x3ea8; // 0x00003EA8 length: 4
        int stone1; // 0x00003EAC length: 4
        int scale1; // 0x00003EB0 length: 4
        int scale2; // 0x00003EB4 length: 4
        int scale3; // 0x00003EB8 length: 4
        int field31_0x3ebc[1000][4]; // 0x00003EBC length: 16000
        undefined1 padding_0x7d3c[16]; // 0x00007D3C length: 16
        int town1; // 0x00007D4C length: 4
        int some1000ArrayIndex; // 0x00007D50 length: 4
        int town2; // 0x00007D54 length: 4
        AttackInfoSomeArrayElement some1000Array[1000]; // 0x00007D58 length: 16000
        undefined1 padding_0xbbd8[16]; // 0x0000BBD8 length: 16
        int gate1; // 0x0000BBE8 length: 4
        int some1000ArrayIndex_2; // 0x0000BBEC length: 4
        int gate2; // 0x0000BBF0 length: 4
        int field71_0xbbf4[1000][4]; // 0x0000BBF4 length: 16000
        undefined1 padding_0xfa74[16]; // 0x0000FA74 length: 16
        int moat1; // 0x0000FA84 length: 4
        int field89_0xfa88; // 0x0000FA88 length: 4
        int moat2; // 0x0000FA8C length: 4
        undefined1 padding_0xfa90[8]; // 0x0000FA90 length: 8
        uint field99_0xfa98; // 0x0000FA98 length: 4
        undefined1 padding_0xfa9c[8980]; // 0x0000FA9C length: 8980
        undefined1 padding_0x11db0[4]; // 0x00011DB0 length: 4
        undefined1 padding_0x11db4[2000]; // 0x00011DB4 length: 2000
        undefined1 padding_0x12584[4]; // 0x00012584 length: 4
        int field11088_0x12588; // 0x00012588 length: 4
        int field11089_0x1258c; // 0x0001258C length: 4
        int field11090_0x12590; // 0x00012590 length: 4
        undefined1 padding_0x12594[4992]; // 0x00012594 length: 4992
        undefined1 padding_0x13914[12]; // 0x00013914 length: 12
        int wide1; // 0x00013920 length: 4
        int wide2; // 0x00013924 length: 4
        int wide3; // 0x00013928 length: 4
        undefined1 padding_0x1392c[10992]; // 0x0001392C length: 10992
        undefined1 padding_0x1641c[8]; // 0x0001641C length: 8
        undefined1 padding_0x16424[4]; // 0x00016424 length: 4
        undefined1 padding_0x16428[4]; // 0x00016428 length: 4
        undefined1 padding_0x1642c[200]; // 0x0001642C length: 200
        undefined1 padding_0x164f4[200]; // 0x000164F4 length: 200
        undefined1 padding_0x165bc[200]; // 0x000165BC length: 200
        undefined1 padding_0x16684[200]; // 0x00016684 length: 200
        int field27906_0x1674c; // 0x0001674C length: 4
        undefined1 padding_0x16750[196]; // 0x00016750 length: 196
        undefined1 padding_0x16814[4]; // 0x00016814 length: 4
        undefined1 padding_0x16818[4]; // 0x00016818 length: 4
        undefined1 padding_0x1681c[4]; // 0x0001681C length: 4
        undefined1 padding_0x16820[4]; // 0x00016820 length: 4
        undefined1 padding_0x16824[4]; // 0x00016824 length: 4
        undefined1 padding_0x16828[4]; // 0x00016828 length: 4
        undefined1 padding_0x1682c[8]; // 0x0001682C length: 8
        undefined1 padding_0x16834[4]; // 0x00016834 length: 4
        undefined1 padding_0x16838[3972]; // 0x00016838 length: 3972

    } AttackInfoSubElement;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubElement) == 96188, AttackInfoSubElement);
} // namespace Map
} // namespace OpenSHC
