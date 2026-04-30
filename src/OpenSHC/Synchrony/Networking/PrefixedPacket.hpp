/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Synchrony/Networking/PrefixedPacket.hpp'
*/

#pragma once

#include "OpenSHC/Synchrony/Networking/Packet.hpp"

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

        using OpenSHC::Synchrony::Networking::Packet;

#pragma pack(push, 1)
        // SIZE: 0x0000EE48
        typedef struct PrefixedPacket {

            byte prefix; // 0x00000000 length: 1
            Packet packet; // 0x00000001 length: 60999

        } PrefixedPacket;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PrefixedPacket) == 61000, PrefixedPacket);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
