/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Instructions {
            typedef enum UnitMatchSpeedEnum {

                UMSE_FREE_UNIT_SPEEDS = -255, // 0x-00000FF
                UMSE_MATCH_UNIT_SPEEDS = 1 // 0x00000001

            } UnitMatchSpeedEnum;

            static_assert_cpp98_obj(sizeof(UnitMatchSpeedEnum) == 4, UnitMatchSpeedEnum);
        } // namespace Instructions
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
