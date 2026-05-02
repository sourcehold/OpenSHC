/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/DecoderBuffer.func.hpp'
*/

#pragma once

#include "OpenSHC/IO/DecoderBuffer.hpp"
#include "OpenSHC/IO/Helpers/BufferHelper.hpp"
namespace OpenSHC {
namespace IO {
    namespace DecoderBuffer_Func {

        using OpenSHC::IO::Helpers::BufferHelper;

        MACRO_FUNCTION_RESOLVER(uint(__cdecl*)(char* buf, uint* size, BufferHelper* param), false,
            Address::SHC_3BB0A8C1_0x0046D270, &OpenSHC::IO::DecoderBuffer::ReadBufferAndComputeHash)
        ReadBufferAndComputeHash;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* buf, uint* size, BufferHelper* param), false,
            Address::SHC_3BB0A8C1_0x0046D300, &OpenSHC::IO::DecoderBuffer::WriteBufferAndComputeHash)
        WriteBufferAndComputeHash;

    } // namespace DecoderBuffer_Func
} // namespace IO
} // namespace OpenSHC
