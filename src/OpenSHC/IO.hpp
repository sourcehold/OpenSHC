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

    byte __stdcall Base64EncodeCharacterLookup(char param_1);

    int __cdecl Base64Encode(byte* input, int length, undefined* output, Base64State* state);

    BOOLEnum __cdecl FileExists(char* param_1);

} // namespace IO
} // namespace OpenSHC
