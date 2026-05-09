/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/enums/AILStatus.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace MSS {
        namespace enums {
            typedef enum AILStatus {

                SND_FREE = 1, // 0x00000001
                SND_DONE = 3, // 0x00000003
                SND_PLAYING = 4, // 0x00000004
                SND_STOPPED = 8, // 0x00000008
                SND_PLAYINGBUTRELEASED = 16 // 0x00000010

            } AILStatus;

            static_assert_cpp98_obj(sizeof(AILStatus) == 4, AILStatus);
        } // namespace enums
    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
