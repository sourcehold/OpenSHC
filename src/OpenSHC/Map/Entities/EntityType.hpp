/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/EntityType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Entities {
        typedef enum EntityType {

            ET_UNKNOWN = 0, // 0x00000000
            ET_ARROW_AND_DEFAULT = 1, // 0x00000001
            ET_CATAPULT = 2, // 0x00000002
            ET_TREBUCHET = 3, // 0x00000003
            ET_MANGONEL = 4, // 0x00000004
            ET_CROSSBOWARROW = 7, // 0x00000007
            ET_FIRE = 9, // 0x00000009
            ET_FLAG_1 = 10, // 0x0000000A
            ET_FLAG_4 = 11, // 0x0000000B
            ET_FLAG_2 = 12, // 0x0000000C
            ET_FLAG_3 = 13, // 0x0000000D
            ET_BRAZIER = 14, // 0x0000000E
            ET_HEADS_ON_SPIKES = 15, // 0x0000000F
            ET_BALLISTA = 20, // 0x00000014
            ET_DUST_CLOUD = 21, // 0x00000015
            ET_COW_POISON_CLOUD = 22, // 0x00000016
            ET_COW_FLYING = 23, // 0x00000017
            ET_SEAGULLUnk = 29, // 0x0000001D
            ET_SLINGER = 33, // 0x00000021
            ET_FIRETHROWER = 34, // 0x00000022
            ET_FIRETHROWER_UNTARGETED = 36, // 0x00000024
            ET_FIREBALLISTA = 37, // 0x00000025
            EntityTypeInt__ET_EXPLOSION = 26, // 0x0000001A
            EntityTypeInt__ET_CROW = 28 // 0x0000001C

        } EntityType;

        static_assert_cpp98_obj(sizeof(EntityType) == 4, EntityType);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
