/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Player {
        typedef enum PlayerDataBuildingCategoryEnum {

            PDBCE_KEEP = 0, // 0x00000000
            PDBCE_STOCKPILE = 1, // 0x00000001
            PDBCE_GRANARY = 2, // 0x00000002
            PDBCE_ARMORY = 3, // 0x00000003
            PDBCE_UNKNOWN4 = 4, // 0x00000004
            PDBCE_BARRACKS = 5, // 0x00000005
            PDBCE_UNKNOWN6 = 6, // 0x00000006
            PDBCE_MARKETPLACE = 7, // 0x00000007
            PDBCE_CAMPGROUND = 8, // 0x00000008
            PDBCE_ENGINEERSGUILD = 9, // 0x00000009
            PDBCE_TUNNELERSGUILD = 10, // 0x0000000A
            PDBCE_MERCENARYPOST = 11, // 0x0000000B
            PDBCE_OILSMELTER = 12 // 0x0000000C

        } PlayerDataBuildingCategoryEnum;

        static_assert_cpp98_obj(sizeof(PlayerDataBuildingCategoryEnum) == 4, PlayerDataBuildingCategoryEnum);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
