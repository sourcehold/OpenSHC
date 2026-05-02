/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Helpers/BufferHelper.hpp'
*/

#pragma once

#include "OpenSHC/IO/Helpers/Buffer.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {
    namespace Helpers {

        using OpenSHC::IO::Helpers::Buffer;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000034
        typedef struct BufferHelper {

            Buffer buffer0; // 0x00000000 length: 12
            Buffer buffer1; // 0x0000000C length: 12
            Buffer buffer2; // 0x00000018 length: 12
            int imploding1orexploding2; // 0x00000024 length: 4
            uint hash; // 0x00000028 length: 4
            int compressedSize; // 0x0000002C length: 4
            BOOLEnum underflow; // 0x00000030 length: 4

        } BufferHelper;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BufferHelper) == 52, BufferHelper);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
