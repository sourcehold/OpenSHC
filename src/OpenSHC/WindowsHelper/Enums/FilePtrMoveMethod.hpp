/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/WindowsHelper/Enums/FilePtrMoveMethod.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Enums {
        typedef enum FilePtrMoveMethod {

            FILE_BEGIN = 0, // 0x00000000
            FILE_CURRENT = 1, // 0x00000001
            FILE_END = 2 // 0x00000002

        } FilePtrMoveMethod;

        static_assert_cpp98_obj(sizeof(FilePtrMoveMethod) == 4, FilePtrMoveMethod);
    } // namespace Enums
} // namespace WindowsHelper
} // namespace OpenSHC
