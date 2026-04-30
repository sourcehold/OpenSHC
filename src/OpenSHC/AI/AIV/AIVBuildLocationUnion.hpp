/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIV/AIVBuildLocationUnion.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVBuildLocationOffset.hpp"
#include "OpenSHC/AI/AIV/AIVBuildLocationTile.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIV {

        using OpenSHC::AI::AIV::AIVBuildLocationOffset;
        using OpenSHC::AI::AIV::AIVBuildLocationTile;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union AIVBuildLocationUnion {

            AIVBuildLocationOffset offset; // 0x00000000 length: 4
            AIVBuildLocationTile tile; // 0x00000000 length: 4

        } AIVBuildLocationUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIVBuildLocationUnion) == 4, AIVBuildLocationUnion);
    } // namespace AIV
} // namespace AI
} // namespace OpenSHC
