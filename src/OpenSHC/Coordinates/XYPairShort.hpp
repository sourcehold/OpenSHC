/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Coordinates/XYPairShort.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Coordinates {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef struct XYPairShort {

        short x; // 0x00000000 length: 2
        short y; // 0x00000002 length: 2

    } XYPairShort;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(XYPairShort) == 4, XYPairShort);
} // namespace Coordinates
} // namespace OpenSHC
