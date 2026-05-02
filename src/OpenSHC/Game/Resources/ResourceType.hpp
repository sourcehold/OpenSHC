/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Resources/ResourceType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Resources {
        typedef enum ResourceType {

            RT_LOGS = 1, // 0x00000001
            RT_WOOD = 2, // 0x00000002
            RT_HOPS = 3, // 0x00000003
            RT_STONE = 4, // 0x00000004
            RT_PARTIALSTONE = 5, // 0x00000005
            RT_IRON = 6, // 0x00000006
            RT_PITCH = 7, // 0x00000007
            RT_PARTIALPITCH = 8, // 0x00000008
            RT_WHEAT = 9, // 0x00000009
            RT_BREAD = 10, // 0x0000000A
            RT_CHEESE = 11, // 0x0000000B
            RT_MEAT = 12, // 0x0000000C
            RT_APPLE = 13, // 0x0000000D
            RT_ALE = 14, // 0x0000000E
            RT_GOLD = 15, // 0x0000000F
            RT_FLOUR = 16, // 0x00000010
            RT_BOW = 17, // 0x00000011
            RT_CROSSBOW = 18, // 0x00000012
            RT_SPEAR = 19, // 0x00000013
            RT_PIKE = 20, // 0x00000014
            RT_MACE = 21, // 0x00000015
            RT_SWORD = 22, // 0x00000016
            RT_LEATHERARMOR = 23, // 0x00000017
            RT_IRONARMOR = 24 // 0x00000018

        } ResourceType;

        static_assert_cpp98_obj(sizeof(ResourceType) == 4, ResourceType);
    } // namespace Resources
} // namespace Game
} // namespace OpenSHC
