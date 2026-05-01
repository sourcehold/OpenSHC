/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DE/SHCDE/eOnScreenText.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DE {
    namespace SHCDE {
        typedef enum eOnScreenText {

            OST_CHAT = 0, // 0x00000000
            OST_DATE = 1, // 0x00000001
            OST_MULTI_CHAT = 3, // 0x00000003
            OST_FEEDBACK_1 = 4, // 0x00000004
            OST_FEEDBACK_2 = 5, // 0x00000005
            OST_FRAMERATE = 6, // 0x00000006
            OST_POPULARITY = 11, // 0x0000000B
            OST_STARTING_GOODS = 12, // 0x0000000C
            OST_MP_GAME_OVER = 16, // 0x00000010
            OST_MISSION_FINISHED = 17, // 0x00000011
            OST_SPLIT_MESSAGE = 19, // 0x00000013
            OST_KEEP_MESSAGE = 20, // 0x00000014
            OST_WHO_OWNS = 21, // 0x00000015
            OST_PINGS = 22, // 0x00000016
            OST_GAME_PAUSED = 23, // 0x00000017
            OST_GAME_SPEED = 24, // 0x00000018
            OST_KING_OF_THE_HILL = 25, // 0x00000019
            OST_WIN_TIMER = 26, // 0x0000001A
            OST_TIMETODEFEAT = 27, // 0x0000001B
            OST_PING_ERROR = 28, // 0x0000001C
            OST_PEOPLE_LEFT = 29, // 0x0000001D
            OST_MESSAGE_BAR = 30, // 0x0000001E
            OST_PEACETIMER = 31, // 0x0000001F
            OST_NUM_OST = 32 // 0x00000020

        } eOnScreenText;

        static_assert_cpp98_obj(sizeof(eOnScreenText) == 4, eOnScreenText);
    } // namespace SHCDE
} // namespace DE
} // namespace OpenSHC
