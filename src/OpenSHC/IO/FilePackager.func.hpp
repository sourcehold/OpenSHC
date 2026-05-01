/**
  path: 'OpenSHC/IO/FilePackager.func.hpp'
*/

#include "OpenSHC/AI/AIV/AIVSectionAddress.hpp"
#include "OpenSHC/IO/FilePackager.hpp"
#include "OpenSHC/Map/MapSectionAddress.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace IO {
    namespace FilePackager_Func {

        using OpenSHC::AI::AIV::AIVSectionAddress;
        using OpenSHC::Map::MapSectionAddress;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (FilePackager::*)(), false, Address::SHC_3BB0A8C1_0x0046D090,
            &FilePackager::copyFromOldToNewMapDirectory)
        copyFromOldToNewMapDirectory;

        MACRO_FUNCTION_RESOLVER(void (FilePackager::*)(MapSectionAddress*), false, Address::SHC_3BB0A8C1_0x00474480,
            &FilePackager::writeMapOrSaveFile)
        writeMapOrSaveFile;

        MACRO_FUNCTION_RESOLVER(void (FilePackager::*)(MapSectionAddress*), false, Address::SHC_3BB0A8C1_0x00474A20,
            &FilePackager::readMapOrSavFile)
        readMapOrSavFile;

        MACRO_FUNCTION_RESOLVER(void (FilePackager::*)(MapSectionAddress*, int), false,
            Address::SHC_3BB0A8C1_0x004750E0, &FilePackager::readMapHeaderSiegeInfoUnk)
        readMapHeaderSiegeInfoUnk;

        MACRO_FUNCTION_RESOLVER(
            void (FilePackager::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x004752D0, &FilePackager::readMapHeader)
        readMapHeader;

        MACRO_FUNCTION_RESOLVER(int (FilePackager::*)(AIVSectionAddress*, char*), false,
            Address::SHC_3BB0A8C1_0x00475690, &FilePackager::unpackAIVFile)
        unpackAIVFile;

    } // namespace FilePackager_Func
} // namespace IO
} // namespace OpenSHC
