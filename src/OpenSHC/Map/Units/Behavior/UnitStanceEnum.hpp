/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Behavior {
            typedef enum UnitStanceEnum {

                USE_STAND_GROUND = 0, // 0x00000000
                USE_DEFENSIVE = 1, // 0x00000001
                USE_AGGRESSIVE = 2 // 0x00000002

            } UnitStanceEnum;

            static_assert_cpp98_obj(sizeof(UnitStanceEnum) == 4, UnitStanceEnum);
        } // namespace Behavior
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
