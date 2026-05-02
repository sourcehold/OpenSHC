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

        uint __cdecl ReadBufferAndComputeHash(char* buf, uint* size, BufferHelper* param);

        void __cdecl WriteBufferAndComputeHash(char* buf, uint* size, BufferHelper* param);

    } // namespace DecoderBuffer
} // namespace IO
} // namespace OpenSHC
