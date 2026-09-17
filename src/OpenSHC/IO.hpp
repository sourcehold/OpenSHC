/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO.hpp'
*/

#pragma once

#include "OpenSHC/IO/Base64State.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace IO {

    using OpenSHC::IO::Base64State;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    void __cdecl SwapInts(undefined4* param_1, undefined4* param_2);

    void __cdecl Base64EncodeInit(Base64State* state);

    char __cdecl Base64Encode_CharacterLookup(char param_1);

    int __cdecl Base64Encode(char* input, int length, char* output, Base64State* state);

    BOOLEnum __cdecl FileExists(char* param_1);

    void __cdecl ReadSkMasters2();

    void __cdecl WriteSkMasters2();

} // namespace IO
} // namespace OpenSHC
