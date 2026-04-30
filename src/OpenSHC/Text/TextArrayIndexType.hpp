/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Text/TextArrayIndexType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {
    typedef enum TextArrayIndexType {

        TAIT_ZERO = 0, // 0x00000000
        TAIT_ONE__FILTER_B = 1, // 0x00000001
        TAIT_TWO__FILTER_A = 2, // 0x00000002
        TAIT_THREE__FILTER_A = 3, // 0x00000003
        TAIT_FIVE__NUMERIC_DOT = 5, // 0x00000005
        TAIT_SIX__NUMERIC_ONLY = 6, // 0x00000006
        TAIT_SEVEN__NUMERIC_ONLY = 7, // 0x00000007
        TAIT_EIGHT__FILTER_B = 8, // 0x00000008
        TAIT_NINE__FILTER_B = 9 // 0x00000009

    } TextArrayIndexType;

    static_assert_cpp98_obj(sizeof(TextArrayIndexType) == 4, TextArrayIndexType);
} // namespace Text
} // namespace OpenSHC
