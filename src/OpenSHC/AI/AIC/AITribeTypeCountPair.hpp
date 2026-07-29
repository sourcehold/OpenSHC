/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIC/AITribeTypeCountPair.hpp'
*/

#pragma once

#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace AIC {

        using OpenSHC::AI::Tribes::AITribeTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct AITribeTypeCountPair {

            AITribeTypeInt tribeType; // 0x00000000 length: 4
            int tribeCount; // 0x00000004 length: 4

        } AITribeTypeCountPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AITribeTypeCountPair) == 8, AITribeTypeCountPair);
    } // namespace AIC
} // namespace AI
} // namespace OpenSHC
