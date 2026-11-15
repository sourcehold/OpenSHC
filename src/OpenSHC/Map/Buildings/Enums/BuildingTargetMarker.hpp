/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/Enums/BuildingTargetMarker.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace Enums {
            typedef enum BuildingTargetMarker {

                BTM_NONE = 0, // 0x00000000
                BTM_UNIT_TARGET = 1, // 0x00000001
                BTM_ENGINEER_TARGET = 2 // 0x00000002

            } BuildingTargetMarker;

            static_assert_cpp98_obj(sizeof(BuildingTargetMarker) == 4, BuildingTargetMarker);
        } // namespace Enums
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
