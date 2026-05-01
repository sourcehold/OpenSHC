/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Buildings/BuildingLogicalState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        typedef enum BuildingLogicalState {

            BLS_NORMAL = 2, // 0x00000002
            BLS_REMOVE = 3 // 0x00000003

        } BuildingLogicalState;

        static_assert_cpp98_obj(sizeof(BuildingLogicalState) == 4, BuildingLogicalState);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
