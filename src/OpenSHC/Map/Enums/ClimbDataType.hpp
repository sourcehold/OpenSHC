/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Enums/ClimbDataType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Enums {
        typedef enum ClimbDataType {

            CDT_LADDER = 1, // 0x00000001
            CDT_BUILDING_3Unk = 3, // 0x00000003
            CDT_BUILDING_4Unk = 4, // 0x00000004
            CDT_BUILDING_5Unk = 5, // 0x00000005
            CDT_6Unk = 6, // 0x00000006
            CDT_BUILDING_7Unk = 7 // 0x00000007

        } ClimbDataType;

        static_assert_cpp98_obj(sizeof(ClimbDataType) == 4, ClimbDataType);
    } // namespace Enums
} // namespace Map
} // namespace OpenSHC
