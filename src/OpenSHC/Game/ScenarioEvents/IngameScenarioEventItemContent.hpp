/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/IngameScenarioEventItemContent.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)
        // SIZE: 0x000000D4
        typedef struct IngameScenarioEventItemContent {

            int actionData; // 0x00000000 length: 4
            int ScenarioEventType; // 0x00000004 length: 4
            byte allOrAnyCondition; // 0x00000008 length: 1
            byte magic; // 0x00000009 length: 1
            byte repeat; // 0x0000000A length: 1
            byte repeatMonths; // 0x0000000B length: 1
            ScenarioEventCondition conditions[39]; // 0x0000000C length: 156
            undefined1 padding_0xa8[44]; // 0x000000A8 length: 44

        } IngameScenarioEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameScenarioEventItemContent) == 212, IngameScenarioEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
