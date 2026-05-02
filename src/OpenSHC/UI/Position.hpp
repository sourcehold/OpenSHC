/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Position.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct Position {

        int x; // 0x00000000 length: 4
        int y; // 0x00000004 length: 4

    } Position;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(Position) == 8, Position);
} // namespace UI
} // namespace OpenSHC
