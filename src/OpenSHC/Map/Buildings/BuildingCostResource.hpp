/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingCostResource.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        typedef enum BuildingCostResource {

            BCR_WOOD = 0, // 0x00000000
            BCR_STONE = 1, // 0x00000001
            BCR_IRON = 2, // 0x00000002
            BCR_PITCH = 3, // 0x00000003
            BCR_GOLD = 4 // 0x00000004

        } BuildingCostResource;

        static_assert_cpp98_obj(sizeof(BuildingCostResource) == 4, BuildingCostResource);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
