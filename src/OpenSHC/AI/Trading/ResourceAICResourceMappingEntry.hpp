/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/Trading/ResourceAICResourceMappingEntry.hpp'
*/

#pragma once

#include "OpenSHC/AI/Trading/AIResourceTradeCategoryInt.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"

namespace OpenSHC {
namespace AI {
    namespace Trading {

        using OpenSHC::AI::Trading::AIResourceTradeCategoryInt;
        using OpenSHC::Game::Resources::ResourceTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct ResourceAICResourceMappingEntry {

            ResourceTypeInt game; // 0x00000000 length: 4
            AIResourceTradeCategoryInt aic; // 0x00000004 length: 4

        } ResourceAICResourceMappingEntry;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ResourceAICResourceMappingEntry) == 8, ResourceAICResourceMappingEntry);
    } // namespace Trading
} // namespace AI
} // namespace OpenSHC
