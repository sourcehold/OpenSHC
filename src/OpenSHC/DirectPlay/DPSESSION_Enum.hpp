/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/DPSESSION_Enum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectPlay {
    typedef enum DPSESSION_Enum {

        DPSESSION_NEWPLAYERSDISABLED = 1, // 0x00000001
        DPSESSION_MIGRATEHOST = 4, // 0x00000004
        DPSESSION_NOMESSAGEID = 8, // 0x00000008
        DPSESSION_JOINDISABLED = 32, // 0x00000020
        DPSESSION_KEEPALIVE = 64, // 0x00000040
        DPSESSION_NODATAMESSAGES = 128, // 0x00000080
        DPSESSION_SECURESERVER = 256, // 0x00000100
        DPSESSION_PRIVATE = 512, // 0x00000200
        DPSESSION_PASSWORDREQUIRED = 1024, // 0x00000400
        DPSESSION_MULTICASTSERVER = 2048, // 0x00000800
        DPSESSION_CLIENTSERVER = 4096, // 0x00001000
        DPSESSION_DIRECTPLAYPROTOCOL = 8192, // 0x00002000
        DPSESSION_NOPRESERVEORDER = 16384, // 0x00004000
        DPSESSION_OPTIMIZELATENCY = 32768 // 0x00008000

    } DPSESSION_Enum;

    static_assert_cpp98_obj(sizeof(DPSESSION_Enum) == 4, DPSESSION_Enum);
} // namespace DirectPlay
} // namespace OpenSHC
