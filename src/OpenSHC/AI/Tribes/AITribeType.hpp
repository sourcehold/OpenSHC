/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
            AITribeTypeInt__AITT_SIEGE_ENGINEERS_SIEGE_EQUIPMENT = 11 // 0x0000000B

        } AITribeType;

        static_assert_cpp98_obj(sizeof(AITribeType) == 4, AITribeType);
    } // namespace Tribes
} // namespace AI
} // namespace OpenSHC
