/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIV/AIV.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIVBuildingStep.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIV {

        using OpenSHC::AI::AIVBuildingStep;

#pragma pack(push, 1)
        // SIZE: 0x00006D98
        typedef struct AIV {

            int playerID; // 0x00000000 length: 4
            int aiType; // 0x00000004 length: 4
            int keepOrientation; // 0x00000008 length: 4
            int castleID; // 0x0000000C length: 4
            int aivSubType; // 0x00000010 length: 4
            int currentStepGoal; // 0x00000014 length: 4
            int aivPoorCounter; // 0x00000018 length: 4
            int aivPoorLimit_OR_AIC_buildInterval; // 0x0000001C length: 4
            int totalSteps; // 0x00000020 length: 4
            int keepXOffset; // 0x00000024 length: 4
            int keepYOffset; // 0x00000028 length: 4
            int keepX; // 0x0000002C length: 4
            int keepY; // 0x00000030 length: 4
            AIVBuildingStep aivBuildingSteps[1000]; // 0x00000034 length: 12000
            int locationsArray[4000]; // 0x00002F14 length: 16000
            int wallLocationsArrayIndex; // 0x00006D94 length: 4

        } AIV;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIV) == 28056, AIV);
    } // namespace AIV
} // namespace AI
} // namespace OpenSHC
