/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIStrengthType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIStrengthType {

        AIST_DEFAULT = 0, // 0x00000000
        AIST_WEAK = 1, // 0x00000001
        AIST_STRONG = 2 // 0x00000002

    } AIStrengthType;

    static_assert_cpp98_obj(sizeof(AIStrengthType) == 4, AIStrengthType);
} // namespace AI
} // namespace OpenSHC
