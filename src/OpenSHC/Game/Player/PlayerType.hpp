/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
