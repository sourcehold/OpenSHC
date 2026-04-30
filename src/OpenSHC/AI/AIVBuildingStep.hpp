/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIVBuildingStep.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVBuildLocationUnion.hpp"
#include "OpenSHC/AI/AIVBuildingStepStatusByte.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVBuildingStepStatusByte;
    using OpenSHC::AI::AIV::AIVBuildLocationUnion;
    using OpenSHC::Commands::CommandBuildingTypeShort;

#pragma pack(push, 1)
    // SIZE: 0x0000000C
    typedef struct AIVBuildingStep {

        AIVBuildingStepStatusByte buildStatus; // 0x00000000 length: 1
        byte wait; // 0x00000001 length: 1
        CommandBuildingTypeShort buildingType; // 0x00000002 length: 2
        short quantity; // 0x00000004 length: 2
        short flag3; // 0x00000006 length: 2
        AIVBuildLocationUnion location; // 0x00000008 length: 4

    } AIVBuildingStep;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(AIVBuildingStep) == 12, AIVBuildingStep);
} // namespace AI
} // namespace OpenSHC
