/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Rocks/Rock.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Rocks {

#pragma pack(push, 1)
        // SIZE: 0x00000020
        typedef struct Rock {

            int gfx; // 0x00000000 length: 4
            uint tile; // 0x00000004 length: 4
            int uid; // 0x00000008 length: 4
            short one; // 0x0000000C length: 2
            short unknownGMID; // 0x0000000E length: 2
            short type; // 0x00000010 length: 2
            ushort x; // 0x00000012 length: 2
            ushort y; // 0x00000014 length: 2
            short size; // 0x00000016 length: 2
            short orientation; // 0x00000018 length: 2
            undefined1 padding_0x1a[6]; // 0x0000001A length: 6

        } Rock;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Rock) == 32, Rock);
    } // namespace Rocks
} // namespace Map
} // namespace OpenSHC
