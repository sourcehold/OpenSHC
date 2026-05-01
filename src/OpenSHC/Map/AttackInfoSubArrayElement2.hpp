/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/AttackInfoSubArrayElement2.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct AttackInfoSubArrayElement2 {

        int tile; // 0x00000000 length: 4
        int tile2; // 0x00000004 length: 4
        int size; // 0x00000008 length: 4
        int unitID; // 0x0000000C length: 4

    } AttackInfoSubArrayElement2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubArrayElement2) == 16, AttackInfoSubArrayElement2);
} // namespace Map
} // namespace OpenSHC
