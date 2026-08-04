/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/DecoderBuffer.hpp'
*/

#pragma once

#include "OpenSHC/IO/Helpers/BufferHelper.hpp"
namespace OpenSHC {
namespace IO {
    namespace DecoderBuffer {

        using OpenSHC::IO::Helpers::BufferHelper;

        unsigned int __cdecl ReadBufferAndComputeHash(char* buf, unsigned int* size, void* param);

        void __cdecl WriteBufferAndComputeHash(char* buf, unsigned int* size, void* param);

    } // namespace DecoderBuffer
} // namespace IO
} // namespace OpenSHC
