/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/FilePackager.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIV/AIVSectionAddress.hpp"
#include "OpenSHC/IO/DirectoryStructNew.hpp"
#include "OpenSHC/IO/DirectoryStructOld.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/MapSectionAddress.hpp"
#include "OpenSHC/UI/RenderLoadAndSaveBar.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::AI::AIV::AIVSectionAddress;
    using OpenSHC::IO::DirectoryStructNew;
    using OpenSHC::IO::DirectoryStructOld;
    using OpenSHC::IO::PackagedFileMagicNumInt;
    using OpenSHC::Map::MapSectionAddress;
    using OpenSHC::UI::RenderLoadAndSaveBar;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000013EC
    class FilePackager {
    public:
        PackagedFileMagicNumInt packagerMapVersionNumUnk; // 0x00000000 length: 4
        PackagedFileMagicNumInt versionNumOfCurrentFileTypeUnk; // 0x00000004 length: 4
        BOOLEnum CRASHES_saveUncompressedUnk; // 0x00000008 length: 4
        int currentlyReadFileSectionIndex; // 0x0000000C length: 4
        void* tempMem; // 0x00000010 length: 4
        int directorySize; // 0x00000014 length: 4
        void* currentlyReadFileSectionMemory; // 0x00000018 length: 4
        int currentlyReadFileSectionSize; // 0x0000001C length: 4
        RenderLoadAndSaveBar* loadAndSaveBarFunc; // 0x00000020 length: 4
        DirectoryStructNew directory; // 0x00000024 length: 3032
        DirectoryStructOld oldDirectory; // 0x00000BFC length: 2032

    private:
        FilePackager(FilePackager const&);
        void operator=(FilePackager const&);

        FilePackager();
        ~FilePackager();

    public:
        // Constructor
        FilePackager* Constructor_FilePackager();

        void copyFromOldToNewMapDirectory();

        void writeMapOrSaveFile(MapSectionAddress* mapSectionAddressArray);

        void readMapOrSavFile(MapSectionAddress* mapSectionAddrArray);

        void readMapHeaderSiegeInfoUnk(MapSectionAddress* mapSectionAddrArray, int sectionID);

        void readMapHeader(BOOLEnum loadPreviewUnk);

        int unpackAIVFile(AIVSectionAddress* array, char* fileName);
    };

    static_assert_cpp98_obj(sizeof(FilePackager) == 5100, FilePackager);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(FilePackager, false, Address::SHC_3BB0A8C1_0x00F2B3D0) pDAT_FilePackager;

} // namespace IO
} // namespace OpenSHC
