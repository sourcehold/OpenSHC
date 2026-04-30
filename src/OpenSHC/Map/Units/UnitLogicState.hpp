/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/UnitLogicState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum UnitLogicState {

            ULS_INVISIBLE = 0, // 0x00000000
            ULS_NORMAL = 2, // 0x00000002
            ULS_REMOVE = 3, // 0x00000003
            ULS_TRANSITIONING = 4 // 0x00000004

        } UnitLogicState;

        static_assert_cpp98_obj(sizeof(UnitLogicState) == 4, UnitLogicState);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
