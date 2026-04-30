/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Input/Mouse/MouseClickInteraction.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {
    namespace Mouse {
        typedef enum MouseClickInteraction {

            MCI_MOVE = 0, // 0x00000000
            MCI_LEFTDOWN = 1, // 0x00000001
            MCI_LEFTUP = 2, // 0x00000002
            MCI_RIGHTDOWN = 3, // 0x00000003
            MCI_RIGHTUP = 4, // 0x00000004
            MCI_MIDDOWN = 5, // 0x00000005
            MCI_MIDUP = 6 // 0x00000006

        } MouseClickInteraction;

        static_assert_cpp98_obj(sizeof(MouseClickInteraction) == 4, MouseClickInteraction);
    } // namespace Mouse
} // namespace Input
} // namespace OpenSHC
