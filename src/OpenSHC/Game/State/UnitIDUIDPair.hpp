/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/State/UnitIDUIDPair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace State {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct UnitIDUIDPair {

            int id; // 0x00000000 length: 4
            int uid; // 0x00000004 length: 4

        } UnitIDUIDPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitIDUIDPair) == 8, UnitIDUIDPair);
    } // namespace State
} // namespace Game
} // namespace OpenSHC
