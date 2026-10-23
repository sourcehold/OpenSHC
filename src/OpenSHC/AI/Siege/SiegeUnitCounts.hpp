/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/Siege/SiegeUnitCounts.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    namespace Siege {

#pragma pack(push, 1)
        // SIZE: 0x00000050
        typedef struct SiegeUnitCounts {

            int archers; // 0x00000000 length: 4
            int crossbowmen; // 0x00000004 length: 4
            int spearmen; // 0x00000008 length: 4
            int pikemen; // 0x0000000C length: 4
            int macemen; // 0x00000010 length: 4
            int swordsmen; // 0x00000014 length: 4
            int knights; // 0x00000018 length: 4
            int laddermen; // 0x0000001C length: 4
            int engineers; // 0x00000020 length: 4
            int monks; // 0x00000024 length: 4
            int arabianArchers; // 0x00000028 length: 4
            int slaves; // 0x0000002C length: 4
            int slingers; // 0x00000030 length: 4
            int assassins; // 0x00000034 length: 4
            int horseArchers; // 0x00000038 length: 4
            int arabianSwordsmen; // 0x0000003C length: 4
            int fireThrowers; // 0x00000040 length: 4
            int fireBallistas; // 0x00000044 length: 4
            int field18_0x48; // 0x00000048 length: 4
            int field19_0x4c; // 0x0000004C length: 4

        } SiegeUnitCounts;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SiegeUnitCounts) == 80, SiegeUnitCounts);
    } // namespace Siege
} // namespace AI
} // namespace OpenSHC
