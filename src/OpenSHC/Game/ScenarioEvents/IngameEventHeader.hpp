/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct IngameEventHeader {

            int month; // 0x00000000 length: 4
            int year; // 0x00000004 length: 4
            int tl_type; // 0x00000008 length: 4
            short done; // 0x0000000C length: 2
            short pre_done; // 0x0000000E length: 2

        } IngameEventHeader;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameEventHeader) == 16, IngameEventHeader);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
