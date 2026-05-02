/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIVBuildingType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIVBuildingType {

        AIVBT_HIGH_WALL = 25, // 0x00000019
        AIVBT_LOW_CRENEL = 26, // 0x0000001A
        AIVBT_HIGH_CRENEL = 35, // 0x00000023
        AIVBT_LOW_WALL = 46, // 0x0000002E
        AIVBT_GRANARY = 80, // 0x00000050
        AIVBT_TOWER1 = 110, // 0x0000006E
        AIVBT_TOWER2 = 111, // 0x0000006F
        AIVBT_TOWER3 = 112, // 0x00000070
        AIVBT_TOWER4 = 113, // 0x00000071
        AIVBT_TOWER5 = 114 // 0x00000072

    } AIVBuildingType;

    static_assert_cpp98_obj(sizeof(AIVBuildingType) == 4, AIVBuildingType);
} // namespace AI
} // namespace OpenSHC
