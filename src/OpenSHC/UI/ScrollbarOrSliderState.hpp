/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/ScrollbarOrSliderState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct ScrollbarOrSliderState {

        int minValue; // 0x00000000 length: 4
        int maxValue; // 0x00000004 length: 4
        int currentValue; // 0x00000008 length: 4
        int dragTiming; // 0x0000000C length: 4

    } ScrollbarOrSliderState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ScrollbarOrSliderState) == 16, ScrollbarOrSliderState);
} // namespace UI
} // namespace OpenSHC
