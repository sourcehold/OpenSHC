/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/GameMode2.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    typedef enum GameMode2 {

        GM_CAMPAIGN_MISSION = 0, // 0x00000000
        GM_EDITOR = 1, // 0x00000001
        GM_BUILDERUnk = 2, // 0x00000002
        GM_SKIRMISH_AND_MULTIPLAYER = 3, // 0x00000003
        GM_CRUSADER_TUTORIAL = 4, // 0x00000004
        GM_ECONOMIC_CAMPAIGN_SH1 = 5, // 0x00000005
        GM_SIEGE_THAT = 6, // 0x00000006
        GM_SHCDE_MAP_TRAIL = 11, // 0x0000000B
        GM_SHCDE_MAP_TRAIL2 = 13 // 0x0000000D

    } GameMode2;

    static_assert_cpp98_obj(sizeof(GameMode2) == 4, GameMode2);
} // namespace Game
} // namespace OpenSHC
