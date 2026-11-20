/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/ScenarioEventConditionsCopy.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
    using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)
    // SIZE: 0x000000BC
    typedef struct ScenarioEventConditionsCopy {

        IngameEventHeader header; // 0x00000000 length: 16
        int actionData; // 0x00000010 length: 4
        int scenarioEventType; // 0x00000014 length: 4
        byte allOrAnyCondition; // 0x00000018 length: 1
        byte magic; // 0x00000019 length: 1
        byte repeat; // 0x0000001A length: 1
        byte repeatMonths; // 0x0000001B length: 1
        ScenarioEventCondition conditions[40]; // 0x0000001C length: 160

    } ScenarioEventConditionsCopy;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ScenarioEventConditionsCopy) == 188, ScenarioEventConditionsCopy);
} // namespace Map
} // namespace OpenSHC
