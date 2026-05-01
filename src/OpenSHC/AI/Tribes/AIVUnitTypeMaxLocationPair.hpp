/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeTribeArrayOffsetInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace Tribes {

        using OpenSHC::AI::AIVUnitTypeInt;
        using OpenSHC::AI::Tribes::AIVUnitTypeTribeArrayOffsetInt;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct AIVUnitTypeMaxLocationPair {

            AIVUnitTypeTribeArrayOffsetInt tribeArrayOffset; // 0x00000000 length: 4
            AIVUnitTypeInt aivUnitType; // 0x00000004 length: 4

        } AIVUnitTypeMaxLocationPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AIVUnitTypeMaxLocationPair) == 8, AIVUnitTypeMaxLocationPair);
    } // namespace Tribes
} // namespace AI
} // namespace OpenSHC
