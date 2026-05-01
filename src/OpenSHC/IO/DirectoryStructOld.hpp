/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/DirectoryStructOld.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::IO::PackagedFileMagicNumInt;

#pragma pack(push, 1)
    // SIZE: 0x000007F0
    typedef struct DirectoryStructOld {

        int fileSizeWithoutDirectory; // 0x00000000 length: 4
        int sectionCount; // 0x00000004 length: 4
        PackagedFileMagicNumInt magicNumOfFileType; // 0x00000008 length: 4
        dword emptyConst0; // 0x0000000C length: 4
        dword emptyConst1; // 0x00000010 length: 4
        dword emptyConst2; // 0x00000014 length: 4
        dword emptyConst3; // 0x00000018 length: 4
        int uncompressedSize[100]; // 0x0000001C length: 400
        int compressedSize[100]; // 0x000001AC length: 400
        int id[100]; // 0x0000033C length: 400
        int isCompressed[100]; // 0x000004CC length: 400
        int offset[100]; // 0x0000065C length: 400
        dword emptyConst4; // 0x000007EC length: 4

    } DirectoryStructOld;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DirectoryStructOld) == 2032, DirectoryStructOld);
} // namespace IO
} // namespace OpenSHC
