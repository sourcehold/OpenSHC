/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/lobby/IDirectPlayLobby3.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/lobby/CreateCompoundAddress.hpp"
#include "OpenSHC/DirectPlay/lobby/EnumAddress.hpp"
#include "ddraw.h"

namespace OpenSHC {
namespace DirectPlay {
    namespace lobby {

        using OpenSHC::DirectPlay::lobby::CreateCompoundAddress;
        using OpenSHC::DirectPlay::lobby::EnumAddress;

#pragma pack(push, 1)
        // SIZE: 0x0000004C
        typedef struct IDirectPlayLobby3 {

            undefined1 padding_0x0[8]; // 0x00000000 length: 8
            Release* Release; // 0x00000008 length: 4
            undefined1 padding_0xc[8]; // 0x0000000C length: 8
            EnumAddress* EnumAddress; // 0x00000014 length: 4
            undefined1 padding_0x18[32]; // 0x00000018 length: 32
            CreateCompoundAddress* CreateCompoundAddress; // 0x00000038 length: 4
            undefined1 padding_0x3c[16]; // 0x0000003C length: 16

        } IDirectPlayLobby3;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IDirectPlayLobby3) == 76, IDirectPlayLobby3);
    } // namespace lobby
} // namespace DirectPlay
} // namespace OpenSHC
