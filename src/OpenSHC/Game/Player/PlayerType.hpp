/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/PlayerType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Player {
        typedef enum PlayerType {

            PT_HUMAN = 0, // 0x00000000
            PT_AI = 1 // 0x00000001

        } PlayerType;

        static_assert_cpp98_obj(sizeof(PlayerType) == 4, PlayerType);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
