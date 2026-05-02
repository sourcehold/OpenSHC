/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/WindowsHelper/Enums/GlobalAllocFlag.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Enums {
        typedef enum GlobalAllocFlag {

            GAF_GMEM_FIXED = 0, // 0x00000000
            GAF_GMEM_MOVEABLE = 2, // 0x00000002
            GAF_GMEM_ZEROINIT = 64, // 0x00000040
            GAF_GPTR = 64, // 0x00000040
            GAF_GHND = 66 // 0x00000042

        } GlobalAllocFlag;

        static_assert_cpp98_obj(sizeof(GlobalAllocFlag) == 4, GlobalAllocFlag);
    } // namespace Enums
} // namespace WindowsHelper
} // namespace OpenSHC
