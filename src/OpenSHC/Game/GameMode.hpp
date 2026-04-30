/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/GameMode.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    typedef enum GameMode {

        GM_SOLITARY = 0, // 0x00000000
        GM_MULTIPLAYER = 1, // 0x00000001
        GM_MULTIPLAYER_END_OF_GAME = 2, // 0x00000002
        GM_SKIRMISH_SINGLE_PLAYER = 99, // 0x00000063
        GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER = 666 // 0x0000029A

    } GameMode;

    static_assert_cpp98_obj(sizeof(GameMode) == 4, GameMode);
} // namespace Game
} // namespace OpenSHC
