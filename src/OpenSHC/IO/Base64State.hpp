/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Base64State.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {

#pragma pack(push, 1)
    // SIZE: 0x0000000C
    typedef struct Base64State {

        int phase; // 0x00000000 length: 4
        int carryByte; // 0x00000004 length: 4
        int lineCharacterCounter; // 0x00000008 length: 4

    } Base64State;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(Base64State) == 12, Base64State);
} // namespace IO
} // namespace OpenSHC
