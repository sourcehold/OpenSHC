/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/ButtonState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct ButtonState {

        int someTimestamp_1_0x0; // 0x00000000 length: 4
        int clickTimestamp_0x4; // 0x00000004 length: 4
        int countTo100; // 0x00000008 length: 4
        int currentButtonPictureInGm_0xc; // 0x0000000C length: 4

    } ButtonState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ButtonState) == 16, ButtonState);
} // namespace UI
} // namespace OpenSHC
