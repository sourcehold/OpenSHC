/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/Siege/EngineerBuildingAndCountPair.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace Siege {

        using OpenSHC::Commands::CommandBuildingTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct EngineerBuildingAndCountPair {

            CommandBuildingTypeInt engineerBuildingType; // 0x00000000 length: 4
            int engineerCount; // 0x00000004 length: 4

        } EngineerBuildingAndCountPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(EngineerBuildingAndCountPair) == 8, EngineerBuildingAndCountPair);
    } // namespace Siege
} // namespace AI
} // namespace OpenSHC
