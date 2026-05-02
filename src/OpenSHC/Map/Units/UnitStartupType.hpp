/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/UnitStartupType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum UnitStartupType {

            UST_NULL = 0, // 0x00000000
            UST_E_ARCHER = 1, // 0x00000001
            UST_E_XBOW = 2, // 0x00000002
            UST_E_SPEAR = 3, // 0x00000003
            UST_E_PIKE = 4, // 0x00000004
            UST_E_MACE = 5, // 0x00000005
            UST_E_SWORD = 6, // 0x00000006
            UST_E_KNIGHT = 7, // 0x00000007
            UST_UNUSED1 = 8, // 0x00000008
            UST_E_ENGINEER = 9, // 0x00000009
            UST_E_MONK = 10, // 0x0000000A
            UST_A_ARCHER = 11, // 0x0000000B
            UST_A_SLAVE = 12, // 0x0000000C
            UST_A_SLINGER = 13, // 0x0000000D
            UST_A_ASSASSIN = 14, // 0x0000000E
            UST_A_HARCHER = 15, // 0x0000000F
            UST_A_SWORD = 16, // 0x00000010
            UST_A_FIRETHROWER = 17, // 0x00000011
            UST_S_FBALLISTAUNMANNED = 18, // 0x00000012
            UST_BUGGED = 19 // 0x00000013

        } UnitStartupType;

        static_assert_cpp98_obj(sizeof(UnitStartupType) == 4, UnitStartupType);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
