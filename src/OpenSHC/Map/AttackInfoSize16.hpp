/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSize16.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct AttackInfoSize16 {

        int field0_0x0; // 0x00000000 length: 4
        int field1_0x4; // 0x00000004 length: 4
        int field2_0x8; // 0x00000008 length: 4
        int field3_0xc; // 0x0000000C length: 4

    } AttackInfoSize16;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSize16) == 16, AttackInfoSize16);
} // namespace Map
} // namespace OpenSHC
