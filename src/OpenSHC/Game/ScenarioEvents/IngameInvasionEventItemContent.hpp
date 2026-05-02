/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/IngameInvasionEventItemContent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x000000B0
        typedef struct IngameInvasionEventItemContent {

            int totalUnitCount; // 0x00000000 length: 4
            int unitCountsPerUnitType[24]; // 0x00000004 length: 96
            int invasionPoint; // 0x00000064 length: 4
            int messageMonth; // 0x00000068 length: 4
            int messageYear; // 0x0000006C length: 4
            int repeatMonths; // 0x00000070 length: 4
            int crusaderArabian; // 0x00000074 length: 4
            int markerIDUnk; // 0x00000078 length: 4
            undefined1 padding_0x7c[52]; // 0x0000007C length: 52

        } IngameInvasionEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameInvasionEventItemContent) == 176, IngameInvasionEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
