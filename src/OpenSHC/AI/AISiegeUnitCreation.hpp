/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AISiegeUnitCreation.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {

#pragma pack(push, 1)
    // SIZE: 0x00000014
    typedef struct AISiegeUnitCreation {

        int unitID; // 0x00000000 length: 4
        int uid; // 0x00000004 length: 4
        int delay; // 0x00000008 length: 4
        int unknown; // 0x0000000C length: 4
        int buildingID; // 0x00000010 length: 4

    } AISiegeUnitCreation;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AISiegeUnitCreation) == 20, AISiegeUnitCreation);
} // namespace AI
} // namespace OpenSHC
