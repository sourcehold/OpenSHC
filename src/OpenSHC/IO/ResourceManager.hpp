/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/ResourceManager.hpp'
*/

#pragma once

#include "HoldStrong_lib/StringObject.hpp"
#include "OpenSHC/IO/FileResourceTypeInt.hpp"
#include "OpenSHC/IO/Helpers/OPENFILENAMEA_Truncated.hpp"
#include "OpenSHC/Map/MapMetaInfo.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "crtdefs.h"

namespace OpenSHC {
namespace IO {

    using HoldStrong_lib::StringObject;
    using OpenSHC::IO::FileResourceTypeInt;
    using OpenSHC::IO::Helpers::OPENFILENAMEA_Truncated;
    using OpenSHC::Map::MapMetaInfo;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000FC794
    class ResourceManager {
    public:
        dword mapFileCounter; // 0x00000000 length: 4
        int loadPositionInCurrentResource; // 0x00000004 length: 4
        char strFile[4]; // 0x00000008 length: 4
        dword currentSectionIndex; // 0x0000000C length: 4
        dword mbr_0x10; // 0x00000010 length: 4
        int mapHeaderMagicByte; // 0x00000014 length: 4
        byte unused_0x18[985]; // 0x00000018 length: 985
        char strFileTitle[1001]; // 0x000003F1 length: 1001
        bool configPathLoadedUnk_0x7da; // 0x000007DA length: 1
        char configPathUnk_0x7db[1001]; // 0x000007DB length: 1001
        FileResourceTypeInt currentActiveResourceType; // 0x00000BC4 length: 4
        char loadedMapNames[500][1001]; // 0x00000BC8 length: 500500
        undefined1 padding_0x7aedc[4]; // 0x0007AEDC length: 4
        char resourceFileNameArray[20][1001]; // 0x0007AEE0 length: 20020
        dword mapFileTimes[500]; // 0x0007FD14 length: 2000
        byte unused_0x804e4[2006]; // 0x000804E4 length: 2006
        OPENFILENAMEA_Truncated openFileNameA; // 0x00080CBA length: 76
        undefined1 padding_0x80d06[2]; // 0x00080D06 length: 2
        int fileHandle; // 0x00080D08 length: 4
        MapMetaInfo mapMetaInfoArray[500]; // 0x00080D0C length: 6000
        byte mapNames[500][1001]; // 0x0008247C length: 500500
        uint loadedMapsCount; // 0x000FC790 length: 4

    private:
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);

        ResourceManager();
        ~ResourceManager();

    public:
        // Constructor
        ResourceManager* Constructor_ResourceManager();

        void loadMapMetaByID(dword id);

        dword getChecksumOfMapByName(char* mapNameAddress);

        char* getLoadedMapNameForIndex(int mapIndex);

        char* getFileNameOfCurrentActiveResource();

        void loadConfigPathTxt();

        BOOLEnum doesFileExist(char* filename);

        void meth_0x46c450();

        void meth_0x46c480();

        void meth_0x46c4b0();

        int getSimpleFirst1024ByteSumOfFile(char* filename);

        void syncLoadedMapNames();

        void swapMapDataWithNextMap(int _mapFileIndex);

        void replaceMapNameWith(dword id1, dword id2);

        char* getCurrentResourceCoreNameUnk();

        BOOLEnum doesFileOfActiveResourceExist();

        void meth_0x471df0();

        BOOLEnum readCurrentResourceIntoDestination(void* destination, size_t size);

        int getCurrentResourceSize();

        BOOLEnum readFirstPartOfCurrentResourceIntoMemory(void* destination, int partSize, char* fileExtension);

        BOOLEnum readNextPartOfCurrentResourceIntoMemory(void* destination, int partSize, char* fileExtension);

        BOOLEnum meth_0x472080();

        BOOLEnum meth_0x4720c0(undefined4 param_1);

        BOOLEnum meth_0x472100();

        BOOLEnum meth_0x472140();

        int fileHashFunctionByteByByte();

        StringObject* getDocumentsFolderString(StringObject* param_1, char param_2);

        void getSavesPath(StringObject* param_1, char param_2);

        void getDocumentsMapsFolderString(StringObject* param_1, BOOLEnum prependUserPath);

        void discoverMapFiles(char* param_1);

        void resolveResourceFileName(FileResourceTypeInt resourceType, char* shortFileName);

        void loadMapHeaders(BOOLEnum drawLoadingBar);

        void filterMapsIfMapLock();
    };

    static_assert_cpp98_obj(sizeof(ResourceManager) == 1034132, ResourceManager);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(ResourceManager, false, Address::SHC_3BB0A8C1_0x011BF130) pDAT_ResourceManager;

} // namespace IO
} // namespace OpenSHC
