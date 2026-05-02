/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Networking/Packet.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

#pragma pack(push, 1)
        // SIZE: 0x0000EE47
        typedef struct Packet {

            byte commandProtocol; // 0x00000000 length: 1
            short time; // 0x00000001 length: 2
            byte unknown; // 0x00000003 length: 1
            byte payload[60995]; // 0x00000004 length: 60995

        } Packet;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Packet) == 60999, Packet);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
