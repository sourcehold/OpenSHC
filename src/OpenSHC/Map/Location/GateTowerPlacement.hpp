/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Location/GateTowerPlacement.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Location {

#pragma pack(push, 1)
        // SIZE: 0x00000018
        typedef struct GateTowerPlacement {

            int x1; // 0x00000000 length: 4
            int y1; // 0x00000004 length: 4
            int rotationIndex1; // 0x00000008 length: 4
            int x2; // 0x0000000C length: 4
            int y2; // 0x00000010 length: 4
            int rotationIndex2; // 0x00000014 length: 4

        } GateTowerPlacement;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GateTowerPlacement) == 24, GateTowerPlacement);
    } // namespace Location
} // namespace Map
} // namespace OpenSHC
