/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Synchrony/Networking/ChatEvent.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct ChatEvent {

            int subjectPlayer; // 0x00000000 length: 4
            int time; // 0x00000004 length: 4
            int flag; // 0x00000008 length: 4
            int objectPlayer; // 0x0000000C length: 4

        } ChatEvent;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ChatEvent) == 16, ChatEvent);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
