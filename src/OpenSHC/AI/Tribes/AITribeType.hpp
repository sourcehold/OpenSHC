/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/Tribes/AITribeType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    namespace Tribes {
        typedef enum AITribeType {

            AITT_TUNNELERS = 2, // 0x00000002
            AITT_ARCHERS = 3, // 0x00000003
            AITT_LADDERMEN = 4, // 0x00000004
            AITT_SPEARMEN = 5, // 0x00000005
            AITT_PIKEMEN = 6, // 0x00000006
            AITT_CROSSBOWMEN = 7, // 0x00000007
            AITT_SWORDSMEN = 8, // 0x00000008
            AITT_MACEMEN = 9, // 0x00000009
            AITT_KNIGHTS = 10, // 0x0000000A
            AITT_ENGINEERS = 11, // 0x0000000B
            AITT_HOPS_FARMER_UNK = 12, // 0x0000000C
            AITT_FIRE_BALLISTA = 24, // 0x00000018
            AITT_ARAB_ARCHER = 25, // 0x00000019
            AITT_ARAB_SLAVE = 26, // 0x0000001A
            AITT_ARAB_SLINGER = 27, // 0x0000001B
            AITT_ARAB_ASSASSIN = 28, // 0x0000001C
            AITT_ARAB_HORSE_ARCHER = 29, // 0x0000001D
            AITT_ARAB_SWORDSMAN = 30, // 0x0000001E
            AITT_ARAB_FIRETHROWER = 31 // 0x0000001F

        } AITribeType;

        static_assert_cpp98_obj(sizeof(AITribeType) == 4, AITribeType);
    } // namespace Tribes
} // namespace AI
} // namespace OpenSHC
