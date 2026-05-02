/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
