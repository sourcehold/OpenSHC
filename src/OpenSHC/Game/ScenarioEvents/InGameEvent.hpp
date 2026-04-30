/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/InGameEvent.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameEventHeader;

#pragma pack(push, 1)
        // SIZE: 0x000000E4
        typedef struct InGameEvent {

            IngameEventHeader header; // 0x00000000 length: 16
            int intensity; // 0x00000010 length: 4
            undefined eventData[208]; // 0x00000014 length: 208

        } InGameEvent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(InGameEvent) == 228, InGameEvent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
