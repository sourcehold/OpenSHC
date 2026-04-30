/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/InvasionEventItem.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameEventHeader;

#pragma pack(push, 1)
        // SIZE: 0x000000E4
        typedef struct InvasionEventItem {

            IngameEventHeader header; // 0x00000000 length: 16
            int intensity; // 0x00000010 length: 4
            int units[24]; // 0x00000014 length: 96
            int magic; // 0x00000074 length: 4
            int messageMonth; // 0x00000078 length: 4
            int messageYear; // 0x0000007C length: 4
            int repeatMonths; // 0x00000080 length: 4
            int crusaderArabian; // 0x00000084 length: 4
            undefined1 padding_0x88[92]; // 0x00000088 length: 92

        } InvasionEventItem;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(InvasionEventItem) == 228, InvasionEventItem);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
