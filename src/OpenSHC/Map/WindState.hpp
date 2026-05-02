/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/WindState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x0000001C
    typedef struct WindState {

        int value; // 0x00000000 length: 4
        int index; // 0x00000004 length: 4
        int countdown; // 0x00000008 length: 4
        int counter; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4
        int valueIs2; // 0x00000014 length: 4
        int valueIs1; // 0x00000018 length: 4

    } WindState;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(WindState) == 28, WindState);
} // namespace Map
} // namespace OpenSHC
