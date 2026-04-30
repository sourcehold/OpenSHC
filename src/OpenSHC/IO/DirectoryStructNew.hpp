/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/DirectoryStructNew.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::IO::PackagedFileMagicNumInt;

#pragma pack(push, 1)
    // SIZE: 0x00000BD8
    typedef struct DirectoryStructNew {

        dword filePayloadSize; // 0x00000000 length: 4
        int sectionCount; // 0x00000004 length: 4
        PackagedFileMagicNumInt magicNumOfFileType; // 0x00000008 length: 4
        dword emptyConst0; // 0x0000000C length: 4
        dword emptyConst1; // 0x00000010 length: 4
        dword emptyConst2; // 0x00000014 length: 4
        dword emptyConst3; // 0x00000018 length: 4
        int uncompressedSize[150]; // 0x0000001C length: 600
        int compressedSize[150]; // 0x00000274 length: 600
        int id[150]; // 0x000004CC length: 600
        int isCompressed[150]; // 0x00000724 length: 600
        int offset[150]; // 0x0000097C length: 600
        dword emptyConst4; // 0x00000BD4 length: 4

    } DirectoryStructNew;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DirectoryStructNew) == 3032, DirectoryStructNew);
} // namespace IO
} // namespace OpenSHC
