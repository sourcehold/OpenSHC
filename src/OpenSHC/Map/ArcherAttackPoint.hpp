/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/ArcherAttackPoint.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct ArcherAttackPoint {

        int field0_0x0; // 0x00000000 length: 4
        int field1_0x4; // 0x00000004 length: 4
        int tile; // 0x00000008 length: 4
        int lastSeenCounter; // 0x0000000C length: 4
        int tribeID; // 0x00000010 length: 4
        uint tribeUID; // 0x00000014 length: 4
        int claimCooldown; // 0x00000018 length: 4
        int field7_0x1c; // 0x0000001C length: 4

    } ArcherAttackPoint;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ArcherAttackPoint) == 32, ArcherAttackPoint);
} // namespace Map
} // namespace OpenSHC
