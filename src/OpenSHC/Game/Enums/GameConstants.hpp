/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Enums/GameConstants.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Enums {
        typedef enum GameConstants {

            GC_PLAYER_ONE = 1, // 0x00000001
            GC_N_PLAYERS = 8, // 0x00000008
            GC_N_PLAYERS_LT = 9 // 0x00000009

        } GameConstants;

        static_assert_cpp98_obj(sizeof(GameConstants) == 4, GameConstants);
    } // namespace Enums
} // namespace Game
} // namespace OpenSHC
