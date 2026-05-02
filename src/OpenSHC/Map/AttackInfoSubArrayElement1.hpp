/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/AttackInfoSubArrayElement1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct AttackInfoSubArrayElement1 {

        int tile; // 0x00000000 length: 4
        int tile2; // 0x00000004 length: 4
        int buildingID; // 0x00000008 length: 4
        int unitID; // 0x0000000C length: 4

    } AttackInfoSubArrayElement1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AttackInfoSubArrayElement1) == 16, AttackInfoSubArrayElement1);
} // namespace Map
} // namespace OpenSHC
