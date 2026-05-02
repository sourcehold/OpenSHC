/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Instructions/MatchSpeedInstructionEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Instructions {
            typedef enum MatchSpeedInstructionEnum {

                MSIE_FREE_SPEEDS = -127, // 0x-000007F
                MSIE_MATCH_SPEEDS = 1 // 0x00000001

            } MatchSpeedInstructionEnum;

            static_assert_cpp98_obj(sizeof(MatchSpeedInstructionEnum) == 4, MatchSpeedInstructionEnum);
        } // namespace Instructions
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
