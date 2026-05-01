/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIMapExtraInfo.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {

#pragma pack(push, 1)
    // SIZE: 0x00000330
    typedef struct AIMapExtraInfo {

        int totalWoodAvailable; // 0x00000000 length: 4
        int someSeparateAreaValue; // 0x00000004 length: 4
        int currentSuitableLocationOffsetArrayIndex_fixme; // 0x00000008 length: 4
        int algorithmIterationNumber; // 0x0000000C length: 4
        int playerTotalKillingPits[9]; // 0x00000010 length: 36
        byte unused01[764]; // 0x00000034 length: 764

    } AIMapExtraInfo;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AIMapExtraInfo) == 816, AIMapExtraInfo);
} // namespace AI
} // namespace OpenSHC
