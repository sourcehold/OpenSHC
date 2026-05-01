/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Buildings/BuildingCostStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {

#pragma pack(push, 1)
        // SIZE: 0x00000014
        typedef struct BuildingCostStruct {

            int requiredWood; // 0x00000000 length: 4
            int requiredStone_0x4; // 0x00000004 length: 4
            int requiredIron_0x8; // 0x00000008 length: 4
            int requiredPitch_0xc; // 0x0000000C length: 4
            int requiredGold; // 0x00000010 length: 4

        } BuildingCostStruct;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuildingCostStruct) == 20, BuildingCostStruct);
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
