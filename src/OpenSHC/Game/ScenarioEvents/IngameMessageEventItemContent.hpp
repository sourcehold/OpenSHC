/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/ScenarioEvents/IngameMessageEventItemContent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct IngameMessageEventItemContent {

            int messageID; // 0x00000000 length: 4
            int action; // 0x00000004 length: 4

        } IngameMessageEventItemContent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IngameMessageEventItemContent) == 8, IngameMessageEventItemContent);
    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
