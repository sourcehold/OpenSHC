/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
            ScenarioEventCondition conditions[40]; // 0x0000000C length: 160
            undefined1 padding_0xac[40]; // 0x000000AC length: 40

        } IngameScenarioEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameScenarioEventItemContent) == 212, IngameScenarioEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
