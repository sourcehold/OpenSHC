/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingSizeIndexMapping.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {

#pragma pack(push, 1)
        // SIZE: 0x00000018
        typedef struct BuildingSizeIndexMapping {

            int x; // 0x00000000 length: 4
            int y; // 0x00000004 length: 4
            int orientedPartIndex[4]; // 0x00000008 length: 16

        } BuildingSizeIndexMapping;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingSizeIndexMapping) == 24, BuildingSizeIndexMapping);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
