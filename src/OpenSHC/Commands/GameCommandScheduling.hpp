/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Commands/GameCommandScheduling.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Commands {
    typedef enum GameCommandScheduling {

        GCS_EXECUTE = 0, // 0x00000000
        GCS_SCHEDULE_AND_SEND = 1, // 0x00000001
        GCS_SCHEDULE_RECEIVED_COMMAND = 2 // 0x00000002

    } GameCommandScheduling;

    static_assert_cpp98_obj(sizeof(GameCommandScheduling) == 4, GameCommandScheduling);
} // namespace Commands
} // namespace OpenSHC
