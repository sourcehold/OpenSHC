/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIType {

        AIT_NULL = 0, // 0x00000000
        AIT_RAT = 2, // 0x00000002
        AIT_SNAKE = 3, // 0x00000003
        AIT_PIG = 4, // 0x00000004
        AIT_WOLF = 5, // 0x00000005
        AIT_SALADIN = 6, // 0x00000006
        AIT_CALIPH = 7, // 0x00000007
        AIT_SULTAN = 8, // 0x00000008
        AIT_RICHARD = 9, // 0x00000009
        AIT_FREDERICK = 10, // 0x0000000A
        AIT_PHILIPP = 11, // 0x0000000B
        AIT_WAZIR = 12, // 0x0000000C
        AIT_EMIR = 13, // 0x0000000D
        AIT_NIZAR = 14, // 0x0000000E
        AIT_SHERIFF = 15, // 0x0000000F
        AIT_MARSHAL = 16, // 0x00000010
        AIT_ABBOT = 17 // 0x00000011

    } AIType;

    static_assert_cpp98_obj(sizeof(AIType) == 4, AIType);
} // namespace AI
} // namespace OpenSHC
