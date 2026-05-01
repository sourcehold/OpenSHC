/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Synchrony/Networking/PacketUnion.hpp'
*/

#pragma once

#include "OpenSHC/Synchrony/Networking/Packet.hpp"
#include "OpenSHC/Synchrony/Networking/PrefixedPacket.hpp"

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

        using OpenSHC::Synchrony::Networking::Packet;
        using OpenSHC::Synchrony::Networking::PrefixedPacket;

#pragma pack(push, 1)
        // SIZE: 0x0000EE48
        typedef union PacketUnion {

            Packet packet; // 0x00000000 length: 60999
            PrefixedPacket prefixedPacket; // 0x00000000 length: 61000

        } PacketUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PacketUnion) == 61000, PacketUnion);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
