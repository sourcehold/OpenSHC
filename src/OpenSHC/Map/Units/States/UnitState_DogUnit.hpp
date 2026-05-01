/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitState_DogUnit.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_DogUnit {

                USDU_FINDING_TARGET = 0, // 0x00000000
                USDU_WAITING_IN_CAGE = 210, // 0x000000D2
                USDU_ROAMING = 211 // 0x000000D3

            } UnitState_DogUnit;

            static_assert_cpp98_obj(sizeof(UnitState_DogUnit) == 4, UnitState_DogUnit);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
