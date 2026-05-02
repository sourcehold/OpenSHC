/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/DPSEND_Enum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectPlay {
    typedef enum DPSEND_Enum {

        DPSEND_GUARANTEED = 1, // 0x00000001
        DPSEND_HIGHPRIORITY = 2, // 0x00000002
        DPSEND_OPENSTREAM = 8, // 0x00000008
        DPSEND_CLOSESTREAM = 16, // 0x00000010
        DPSEND_SIGNED = 32, // 0x00000020
        DPSEND_ENCRYPTED = 64, // 0x00000040
        DPSEND_LOBBYSYSTEMMESSAGE = 128, // 0x00000080
        DPSEND_ASYNC = 512, // 0x00000200
        DPSEND_NOSENDCOMPLETEMSG = 1024, // 0x00000400
        DPSEND_MAX_PRI = 65535, // 0x0000FFFF
        DPSEND_MAX_PRIORITY = 65535 // 0x0000FFFF

    } DPSEND_Enum;

    static_assert_cpp98_obj(sizeof(DPSEND_Enum) == 4, DPSEND_Enum);
} // namespace DirectPlay
} // namespace OpenSHC
