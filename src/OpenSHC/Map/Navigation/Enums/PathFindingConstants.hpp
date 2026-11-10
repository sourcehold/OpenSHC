/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/Enums/PathFindingConstants.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        namespace Enums {
            typedef enum PathFindingConstants {

                PFC_DIRECTIONS = 8, // 0x00000008
                PFC_SEARCH_GENERATION_LIMIT = 32000 // 0x00007D00

            } PathFindingConstants;

            static_assert_cpp98_obj(sizeof(PathFindingConstants) == 4, PathFindingConstants);
        } // namespace Enums
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
