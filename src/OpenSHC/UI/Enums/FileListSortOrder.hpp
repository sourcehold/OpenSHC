/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Enums/FileListSortOrder.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum FileListSortOrder {

            FLSO_BY_NAME = 0, // 0x00000000
            FLSO_BY_NAME_REVERSED = 1, // 0x00000001
            FLSO_BY_TIME_NEWEST_FIRST = 2, // 0x00000002
            FLSO_BY_TIME_OLDEST_FIRST = 3 // 0x00000003

        } FileListSortOrder;

        static_assert_cpp98_obj(sizeof(FileListSortOrder) == 4, FileListSortOrder);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
