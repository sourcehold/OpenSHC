/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        typedef enum BuildingFailReasonEnum {

            BFRE_MISSING5 = -5, // 0x-0000005
            BFRE_MISSING4 = -4, // 0x-0000004
            BFRE_MUST_BE_PLACED_ON_OASES = -3, // 0x-0000003
            BFRE_MISSING2 = -2, // 0x-0000002
            BFRE_DEFAULT_CANT_PLACE_THAT_THERE1 = -1, // 0x-0000001
            BFRE_DEFAULT_CANT_PLACE_THAT_THERE = 0, // 0x00000000
            BFRE_NOT_ENOUGH_WORKERS = 1, // 0x00000001
            BFRE_NOT_ADJ_STOCKPILE = 3, // 0x00000003
            BFRE_NOT_ADJ_ARMORY = 4, // 0x00000004
            BFRE_NOT_IRON_ORE = 5, // 0x00000005
            BFRE_NOT_OIL_MARSH = 6, // 0x00000006
            BFRE_NOT_ADJ_GRANARY = 7, // 0x00000007
            BFRE_TOO_FAR = 15 // 0x0000000F

        } BuildingFailReasonEnum;

        static_assert_cpp98_obj(sizeof(BuildingFailReasonEnum) == 4, BuildingFailReasonEnum);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
