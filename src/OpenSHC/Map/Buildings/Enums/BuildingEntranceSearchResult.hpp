/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/Enums/BuildingEntranceSearchResult.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace Enums {
            typedef enum BuildingEntranceSearchResult {

                BESR_NOT_FOUND = 0, // 0x00000000
                BESR_FOUND = 1, // 0x00000001
                BESR_UNREACHABLE = 2 // 0x00000002

            } BuildingEntranceSearchResult;

            static_assert_cpp98_obj(sizeof(BuildingEntranceSearchResult) == 4, BuildingEntranceSearchResult);
        } // namespace Enums
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
