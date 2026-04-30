/**
  path: 'OpenSHC/IO/ResourceManager.func.hpp'
*/

#include "HoldStrong_lib/StringObject.hpp"
#include "OpenSHC/IO/FileResourceTypeInt.hpp"
#include "OpenSHC/IO/ResourceManager.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "crtdefs.h"
namespace OpenSHC {
namespace IO {
    namespace ResourceManager_Func {

        using HoldStrong_lib::StringObject;
        using OpenSHC::IO::FileResourceTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(dword), false, Address::SHC_3BB0A8C1_0x0046C200,
            &ResourceManager::loadMapMetaByID)
        loadMapMetaByID;

        MACRO_FUNCTION_RESOLVER(dword (ResourceManager::*)(char*), false, Address::SHC_3BB0A8C1_0x0046C280,
            &ResourceManager::getChecksumOfMapByName)
        getChecksumOfMapByName;

        MACRO_FUNCTION_RESOLVER(char* (ResourceManager::*)(int), false, Address::SHC_3BB0A8C1_0x0046C2E0,
            &ResourceManager::getLoadedMapNameForIndex)
        getLoadedMapNameForIndex;

        MACRO_FUNCTION_RESOLVER(char* (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x0046C300,
            &ResourceManager::getFileNameOfCurrentActiveResource)
        getFileNameOfCurrentActiveResource;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x0046C320, &ResourceManager::loadConfigPathTxt)
        loadConfigPathTxt;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(char*), false, Address::SHC_3BB0A8C1_0x0046C420,
            &ResourceManager::doesFileExist)
        doesFileExist;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x0046C450, &ResourceManager::meth_0x46c450)
        meth_0x46c450;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x0046C480, &ResourceManager::meth_0x46c480)
        meth_0x46c480;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x0046C4B0, &ResourceManager::meth_0x46c4b0)
        meth_0x46c4b0;

        MACRO_FUNCTION_RESOLVER(int (ResourceManager::*)(char*), false, Address::SHC_3BB0A8C1_0x0046C4E0,
            &ResourceManager::getSimpleFirst1024ByteSumOfFile)
        getSimpleFirst1024ByteSumOfFile;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00471C10, &ResourceManager::syncLoadedMapNames)
        syncLoadedMapNames;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(int), false, Address::SHC_3BB0A8C1_0x00471C50,
            &ResourceManager::swapMapDataWithNextMap)
        swapMapDataWithNextMap;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(dword, dword), false, Address::SHC_3BB0A8C1_0x00471CD0,
            &ResourceManager::replaceMapNameWith)
        replaceMapNameWith;

        MACRO_FUNCTION_RESOLVER(char* (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00471D30,
            &ResourceManager::getCurrentResourceCoreNameUnk)
        getCurrentResourceCoreNameUnk;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00471DC0,
            &ResourceManager::doesFileOfActiveResourceExist)
        doesFileOfActiveResourceExist;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00471DF0, &ResourceManager::meth_0x471df0)
        meth_0x471df0;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(void*, size_t), false, Address::SHC_3BB0A8C1_0x00471E50,
            &ResourceManager::readCurrentResourceIntoDestination)
        readCurrentResourceIntoDestination;

        MACRO_FUNCTION_RESOLVER(int (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00471EB0,
            &ResourceManager::getCurrentResourceSize)
        getCurrentResourceSize;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(void*, int, char*), false,
            Address::SHC_3BB0A8C1_0x00471F10, &ResourceManager::readFirstPartOfCurrentResourceIntoMemory)
        readFirstPartOfCurrentResourceIntoMemory;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(void*, int, char*), false,
            Address::SHC_3BB0A8C1_0x00471FC0, &ResourceManager::readNextPartOfCurrentResourceIntoMemory)
        readNextPartOfCurrentResourceIntoMemory;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00472080, &ResourceManager::meth_0x472080)
        meth_0x472080;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ResourceManager::*)(undefined4), false, Address::SHC_3BB0A8C1_0x004720C0,
            &ResourceManager::meth_0x4720c0)
        meth_0x4720c0;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00472100, &ResourceManager::meth_0x472100)
        meth_0x472100;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00472140, &ResourceManager::meth_0x472140)
        meth_0x472140;

        MACRO_FUNCTION_RESOLVER(int (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00472180,
            &ResourceManager::fileHashFunctionByteByByte)
        fileHashFunctionByteByByte;

        MACRO_FUNCTION_RESOLVER(StringObject* (ResourceManager::*)(StringObject*, char), false,
            Address::SHC_3BB0A8C1_0x004778E0, &ResourceManager::getDocumentsFolderString)
        getDocumentsFolderString;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(StringObject*, char), false, Address::SHC_3BB0A8C1_0x004779F0,
            &ResourceManager::getSavesPath)
        getSavesPath;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(StringObject*, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00477B00, &ResourceManager::getDocumentsMapsFolderString)
        getDocumentsMapsFolderString;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(char*), false, Address::SHC_3BB0A8C1_0x00477EE0,
            &ResourceManager::discoverMapFiles)
        discoverMapFiles;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(FileResourceTypeInt, char*), false,
            Address::SHC_3BB0A8C1_0x00478360, &ResourceManager::resolveResourceFileName)
        resolveResourceFileName;

        MACRO_FUNCTION_RESOLVER(void (ResourceManager::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x00478AE0,
            &ResourceManager::loadMapHeaders)
        loadMapHeaders;

        MACRO_FUNCTION_RESOLVER(
            void (ResourceManager::*)(), false, Address::SHC_3BB0A8C1_0x00478C60, &ResourceManager::filterMapsIfMapLock)
        filterMapsIfMapLock;

    } // namespace ResourceManager_Func
} // namespace IO
} // namespace OpenSHC
