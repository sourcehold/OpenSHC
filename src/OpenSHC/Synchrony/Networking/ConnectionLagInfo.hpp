/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Networking/ConnectionLagInfo.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace Synchrony {
    namespace Networking {

#pragma pack(push, 1)
        // SIZE: 0x00000024
        typedef struct ConnectionLagInfo {

            int mapTimeInTicks; // 0x00000000 length: 4
            int subtractedMapTicks; // 0x00000004 length: 4
            int counter; // 0x00000008 length: 4
            int average1; // 0x0000000C length: 4
            int now; // 0x00000010 length: 4
            DWORD subtractedTime; // 0x00000014 length: 4
            int average2; // 0x00000018 length: 4
            int checkFor0; // 0x0000001C length: 4
            DWORD time; // 0x00000020 length: 4

        } ConnectionLagInfo;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ConnectionLagInfo) == 36, ConnectionLagInfo);
    } // namespace Networking
} // namespace Synchrony
} // namespace OpenSHC
