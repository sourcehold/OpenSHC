/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Input/Mouse/ClickTypeBitMaskEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {
    namespace Mouse {
        typedef enum ClickTypeBitMaskEnum {

            CTBME_LEFT_DOWN = 1, // 0x00000001
            CTBME_RIGHT_DOWN = 16, // 0x00000010
            CTBME_MID_DOWN = 64, // 0x00000040
            CTBME_MIDUP = 191, // 0x000000BF
            CTBME_RIGHT_UP = 239, // 0x000000EF
            CTBME_LEFT_UP = 254 // 0x000000FE

        } ClickTypeBitMaskEnum;

        static_assert_cpp98_obj(sizeof(ClickTypeBitMaskEnum) == 4, ClickTypeBitMaskEnum);
    } // namespace Mouse
} // namespace Input
} // namespace OpenSHC
