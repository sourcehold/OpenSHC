/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/InGameEventUnion.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/IngameInvasionEventItemContent.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameMessageEventItemContent.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameScenarioEventItemContent.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameInvasionEventItemContent;
        using OpenSHC::Game::ScenarioEvents::IngameMessageEventItemContent;
        using OpenSHC::Game::ScenarioEvents::IngameScenarioEventItemContent;

#pragma pack(push, 1)
        // SIZE: 0x000000D4
        typedef union InGameEventUnion {

            IngameScenarioEventItemContent scenario; // 0x00000000 length: 212
            IngameInvasionEventItemContent invasion; // 0x00000000 length: 176
            IngameMessageEventItemContent message; // 0x00000000 length: 8

        } InGameEventUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(InGameEventUnion) == 212, InGameEventUnion);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
