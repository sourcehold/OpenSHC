/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/ScenarioEventItem.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
        using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)
        // SIZE: 0x000000E4
        typedef struct ScenarioEventItem {

            IngameEventHeader header; // 0x00000000 length: 16
            int intensity; // 0x00000010 length: 4
            int ScenarioEventType; // 0x00000014 length: 4
            byte allOrAnyCondition; // 0x00000018 length: 1
            byte magic; // 0x00000019 length: 1
            byte repeat; // 0x0000001A length: 1
            byte repeatMonths; // 0x0000001B length: 1
            ScenarioEventCondition conditions[39]; // 0x0000001C length: 156
            undefined1 padding_0xb8[44]; // 0x000000B8 length: 44

        } ScenarioEventItem;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ScenarioEventItem) == 228, ScenarioEventItem);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
