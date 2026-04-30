/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/WindowsHelper/Enums/OpenFlag.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Enums {
        typedef enum OpenFlag {

            _O_RDONLY = 0, // 0x00000000
            _O_WRONLY = 1, // 0x00000001
            _O_RDWR = 2, // 0x00000002
            _O_APPEND = 8, // 0x00000008
            _O_RANDOM = 16, // 0x00000010
            _O_SEQUENTIAL = 32, // 0x00000020
            _O_TEMPORARY = 64, // 0x00000040
            _O_NOINHERIT = 128, // 0x00000080
            _O_CREAT = 256, // 0x00000100
            _O_TRUNC = 512, // 0x00000200
            _O_EXCL = 1024, // 0x00000400
            _O_SHORT_LIVED = 4096, // 0x00001000
            _O_OBTAIN_DIR = 8192, // 0x00002000
            _O_TEXT = 16384, // 0x00004000
            _O_BINARY = 32768, // 0x00008000
            _O_RAW = 32768, // 0x00008000
            _O_WTEXT = 65536, // 0x00010000
            _O_U16TEXT = 131072, // 0x00020000
            _O_U8TEXT = 262144 // 0x00040000

        } OpenFlag;

        static_assert_cpp98_obj(sizeof(OpenFlag) == 4, OpenFlag);
    } // namespace Enums
} // namespace WindowsHelper
} // namespace OpenSHC
