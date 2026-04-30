/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Commands/GameCommandState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Commands {
    typedef enum GameCommandState {

        GCS_UNPROCESSED = 1, // 0x00000001
        GCS_PROCESSED = 10 // 0x0000000A

    } GameCommandState;

    static_assert_cpp98_obj(sizeof(GameCommandState) == 4, GameCommandState);
} // namespace Commands
} // namespace OpenSHC
