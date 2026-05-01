/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO.func.hpp'
*/

#pragma once

#include "OpenSHC/IO.hpp"
#include "OpenSHC/IO/Base64State.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace IO_Func {

    using OpenSHC::IO::Base64State;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4* param_1, undefined4* param_2), false,
        Address::SHC_3BB0A8C1_0x0041A740, &OpenSHC::IO::SwapInts)
    SwapInts;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(Base64State* state), false, Address::SHC_3BB0A8C1_0x00487080, &OpenSHC::IO::Base64EncodeInit)
    Base64EncodeInit;

    MACRO_FUNCTION_RESOLVER(byte(__stdcall*)(char param_1), false, Address::SHC_3BB0A8C1_0x00487090,
        &OpenSHC::IO::Base64EncodeCharacterLookup)
    Base64EncodeCharacterLookup;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(byte* input, int length, undefined* output, Base64State* state), false,
        Address::SHC_3BB0A8C1_0x004870B0, &OpenSHC::IO::Base64Encode)
    Base64Encode;

    MACRO_FUNCTION_RESOLVER(
        BOOLEnum(__cdecl*)(char* param_1), false, Address::SHC_3BB0A8C1_0x004BC5B0, &OpenSHC::IO::FileExists)
    FileExists;

} // namespace IO_Func
} // namespace OpenSHC
