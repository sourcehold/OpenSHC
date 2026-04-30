/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/UnitIDMovementDistancePair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct UnitIDMovementDistancePair {

            short unitID; // 0x00000000 length: 2
            short movementDistance; // 0x00000002 length: 2

        } UnitIDMovementDistancePair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitIDMovementDistancePair) == 4, UnitIDMovementDistancePair);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
