/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/PitchDitch.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {

#pragma pack(push, 1)
    // SIZE: 0x00000014
    typedef struct PitchDitch {

        int tile; // 0x00000000 length: 4
        int uid; // 0x00000004 length: 4
        short owner; // 0x00000008 length: 2
        short x; // 0x0000000A length: 2
        short y; // 0x0000000C length: 2
        short rng; // 0x0000000E length: 2
        short state; // 0x00000010 length: 2
        short field7_0x12; // 0x00000012 length: 2

    } PitchDitch;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(PitchDitch) == 20, PitchDitch);
} // namespace Map
} // namespace OpenSHC
