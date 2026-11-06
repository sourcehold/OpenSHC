/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ScreenResolutionUnion.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/ScreenResolutionArrayStruct.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Rendering::ScreenResolutionArrayStruct;

#pragma pack(push, 1)
    // SIZE: 0x00000040
    typedef union ScreenResolutionUnion {

        ScreenResolutionArrayStruct fields; // 0x00000000 length: 64
        int array[16]; // 0x00000000 length: 64

    } ScreenResolutionUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ScreenResolutionUnion) == 64, ScreenResolutionUnion);
} // namespace Rendering
} // namespace OpenSHC
