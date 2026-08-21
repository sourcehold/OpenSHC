#include "../FilePackager.func.hpp"

#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00474480
    void FilePackager::writeMapOrSaveFile(MapSectionAddress* mapSectionAddressArray)
    {
        RenderLoadAndSaveBar* const loadAndSaveBarFunc = this->loadAndSaveBarFunc;
        this->loadAndSaveBarFunc = NULL;

        int _rawSize = 0;
        int _secSizeSumUnk = 0;

        this->currentlyReadFileSectionIndex = 0;
        this->directory.sectionCount = 0;
        this->directory.filePayloadSize = 0;

        // FIXME?: This one can leak memory, but it could also mean that the game is broken in this case anyway.

        this->tempMem = MACRO_CALL(OS_Func::_malloc)(6000000); // 0x5B8D80
        if (!this->tempMem) {
            return;
        }

        void* _tempMem2 = MACRO_CALL(OS_Func::_malloc)(100000); // 0x186A0
        if (!_tempMem2) {
            return;
        }
        MapSectionAddress* tempSectionAddress = mapSectionAddressArray;
        for (; this->currentlyReadFileSectionIndex < 150 && mapSectionAddressArray->address > 0;
            ++mapSectionAddressArray) {
            _rawSize += mapSectionAddressArray->size;
            ++this->currentlyReadFileSectionIndex;
        }
        this->currentlyReadFileSectionIndex = 0;

        DAT_GameCore::instance.gameDuration = timeGetTime() - DAT_GameCore::instance.timeSum_2;

        mapSectionAddressArray = tempSectionAddress;
        for (; this->currentlyReadFileSectionIndex < 150 && mapSectionAddressArray->address > 0;
            ++mapSectionAddressArray) {
            if (mapSectionAddressArray->unknown) {
                continue;
            }

            _secSizeSumUnk += mapSectionAddressArray->size;
            this->directory.uncompressedSize[this->currentlyReadFileSectionIndex] = mapSectionAddressArray->size;
            this->directory.id[this->currentlyReadFileSectionIndex] = mapSectionAddressArray->sectionId;
            this->directory.isCompressed[this->currentlyReadFileSectionIndex] = mapSectionAddressArray->compressed;
            this->directory.compressedSize[this->currentlyReadFileSectionIndex]
                = this->directory.uncompressedSize[this->currentlyReadFileSectionIndex];
            this->directory.offset[this->currentlyReadFileSectionIndex] = this->directory.filePayloadSize;

            if (!this->directory.isCompressed[this->currentlyReadFileSectionIndex]
                || this->CRASHES_saveUncompressedUnk) {
                MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                    this->directory.uncompressedSize[this->currentlyReadFileSectionIndex],
                    mapSectionAddressArray->address, (void*)((int)this->tempMem + this->directory.filePayloadSize));
                this->directory.filePayloadSize
                    += this->directory.uncompressedSize[this->currentlyReadFileSectionIndex];
            } else {
                this->directory.compressedSize[this->currentlyReadFileSectionIndex]
                    = MACRO_CALL_MEMBER(DecoderState_Func::encodeData, DAT_DecoderState::ptr)(
                        this->directory.uncompressedSize[this->currentlyReadFileSectionIndex],
                        (unsigned char*)mapSectionAddressArray->address,
                        (unsigned char*)((int)this->tempMem + this->directory.filePayloadSize));
                this->directory.filePayloadSize += this->directory.compressedSize[this->currentlyReadFileSectionIndex];
            }

            if (loadAndSaveBarFunc) {
                (*loadAndSaveBarFunc)((int)(((long long)_secSizeSumUnk * 1000) / _rawSize));
            }

            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                && this->currentlyReadFileSectionIndex % 10 == 0) {
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::sendPeriodicSyncMessages, DAT_GameSynchronyState::ptr)();
            }
            ++this->directory.sectionCount;
            ++this->currentlyReadFileSectionIndex;
        }

        char* _filename
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();

        int _fileDescriptor = MACRO_CALL(OS_Func::_ucrt_open)(
            _filename, _O_BINARY | _O_TRUNC | _O_CREAT | _O_WRONLY, _S_IREAD | _S_IWRITE);
        if (_fileDescriptor == -1) {
            return;
        }

        // Blocks required to not enlarge stack (maybe they were helper methods?)
        // Size variable names not binding: Only guesses based on usage here
        {
            int magicByteHolder = -1;
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &magicByteHolder, sizeof(magicByteHolder));

            switch (DAT_TileMapState::instance.mapSize) {
            case 100:
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMiniMapForSaving, DAT_MinimapViewState::ptr)(
                    50, 50, DAT_TileMapState::instance.mapSize, DAT_TileMapState::instance.mapSize);
                break;
            case 160:
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMiniMapForSaving, DAT_MinimapViewState::ptr)(
                    20, 20, DAT_TileMapState::instance.mapSize, DAT_TileMapState::instance.mapSize);
                break;
            case 200:
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMiniMapForSaving, DAT_MinimapViewState::ptr)(
                    0, 0, DAT_TileMapState::instance.mapSize, DAT_TileMapState::instance.mapSize);
                break;
            case 300:
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMiniMapForSaving, DAT_MinimapViewState::ptr)(
                    25, 25, 150, 150);
                break;
            default:
                MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMiniMapForSaving, DAT_MinimapViewState::ptr)(
                    0, 0, 200, 200);
                break;
            }
            int mapWriteSize
                = MACRO_CALL_MEMBER(UI::MinimapViewState_Func::generateMinimapImage, DAT_MinimapViewState::ptr)();
            mapWriteSize = MACRO_CALL_MEMBER(DecoderState_Func::encodeData, DAT_DecoderState::ptr)(
                mapWriteSize, (unsigned char*)DAT_MinimapViewState::instance.loadedMiniMap, (unsigned char*)_tempMem2);
            MACRO_CALL(OS_Func::_ucrt_write)(_fileDescriptor, &mapWriteSize, sizeof(mapWriteSize));
            MACRO_CALL(OS_Func::_ucrt_write)(_fileDescriptor, _tempMem2, mapWriteSize);
        }
        {
            int textSize = MACRO_CALL_MEMBER(OpenSHC::IO::DecoderState_Func::encodeData, DAT_DecoderState::ptr)(
                sizeof(DAT_GameCore::instance.temporaryTextBufferOfSize1000),
                (unsigned char*)DAT_GameCore::instance.temporaryTextBufferOfSize1000, (unsigned char*)_tempMem2);
            textSize += sizeof(DAT_GameCore::instance.descriptionUseStringTable)
                + sizeof(DAT_GameCore::instance.descriptionStringTableIndex);
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &textSize, sizeof(textSize));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_GameCore::instance.descriptionUseStringTable,
                sizeof(DAT_GameCore::instance.descriptionUseStringTable));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_GameCore::instance.descriptionStringTableIndex,
                sizeof(DAT_GameCore::instance.descriptionStringTableIndex));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, _tempMem2, textSize - sizeof(int) * 2);
        }
        {
            int ticksAndHashSize = sizeof(DAT_GameSynchronyState::instance.savedMapTimeInTicks)
                + sizeof(DAT_GameSynchronyState::instance.savedUnitsCRC32Hash);
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &ticksAndHashSize, sizeof(ticksAndHashSize));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_GameSynchronyState::instance.savedMapTimeInTicks,
                sizeof(DAT_GameSynchronyState::instance.savedMapTimeInTicks));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_GameSynchronyState::instance.savedUnitsCRC32Hash,
                sizeof(DAT_GameSynchronyState::instance.savedUnitsCRC32Hash));
        }
        {
            int playerDataSize = sizeof(DAT_GameCore::instance.U2_mapType_singleOrMulti)
                + sizeof(DAT_GameCore::instance.mapU2MiddleBytes) + sizeof(DAT_GameCore::instance.mapU2PlayersCount);
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &playerDataSize, sizeof(playerDataSize));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_GameCore::instance.U2_mapType_singleOrMulti,
                sizeof(DAT_GameCore::instance.U2_mapType_singleOrMulti));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_GameCore::instance.mapU2MiddleBytes,
                sizeof(DAT_GameCore::instance.mapU2MiddleBytes));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_GameCore::instance.mapU2PlayersCount,
                sizeof(DAT_GameCore::instance.mapU2PlayersCount));
        }
        {
            int scenarioDataSize = sizeof(DAT_MapPropertiesState::instance.scenarionMissionType)
                + sizeof(DAT_MapPropertiesState::instance.SEC_U3_MapType2_1)
                + sizeof(DAT_GameCore::instance.U3_mapLockedState) + sizeof(DAT_GameCore::instance.standaloneFilename)
                + sizeof(DAT_GameCore::instance.mapU3EndInt);
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &scenarioDataSize, sizeof(scenarioDataSize));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_MapPropertiesState::instance.scenarionMissionType,
                sizeof(DAT_MapPropertiesState::instance.scenarionMissionType));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_MapPropertiesState::instance.SEC_U3_MapType2_1,
                sizeof(DAT_MapPropertiesState::instance.SEC_U3_MapType2_1));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_GameCore::instance.U3_mapLockedState,
                sizeof(DAT_GameCore::instance.U3_mapLockedState));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, DAT_GameCore::instance.standaloneFilename,
                sizeof(DAT_GameCore::instance.standaloneFilename));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(
                _fileDescriptor, &DAT_GameCore::instance.mapU3EndInt, sizeof(DAT_GameCore::instance.mapU3EndInt));
        }
        {
            int skirmishDataSize = sizeof(DAT_GameCore::instance.mapU4Int0) + sizeof(DAT_GameCore::instance.mapU4Int1)
                + sizeof(DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes)
                + sizeof(DAT_GameCore::instance.mapU4Int3_balanced)
                + sizeof(DAT_MinimapViewState::instance.DAT_MapU4B64);
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &skirmishDataSize, sizeof(skirmishDataSize));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(
                _fileDescriptor, &DAT_GameCore::instance.mapU4Int0, sizeof(DAT_GameCore::instance.mapU4Int0));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(
                _fileDescriptor, &DAT_GameCore::instance.mapU4Int1, sizeof(DAT_GameCore::instance.mapU4Int1));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor,
                &DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes,
                sizeof(DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_GameCore::instance.mapU4Int3_balanced,
                sizeof(DAT_GameCore::instance.mapU4Int3_balanced));
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &DAT_MinimapViewState::instance.DAT_MapU4B64,
                sizeof(DAT_MinimapViewState::instance.DAT_MapU4B64));
        }
        {
            int unknownSize = 0;
            MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &unknownSize, sizeof(unknownSize));
        }

        this->directorySize = sizeof(this->directorySize) + sizeof(this->directory);
        this->directory.magicNumOfFileType = 172;
        MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &this->directorySize, sizeof(this->directorySize));
        MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, &this->directory, sizeof(this->directory));

        MACRO_CALL(OpenSHC::OS_Func::_ucrt_write)(_fileDescriptor, this->tempMem, this->directory.filePayloadSize);
        MACRO_CALL(OpenSHC::OS_Func::_ucrt_close)(_fileDescriptor);
        MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->tempMem);
        MACRO_CALL(OpenSHC::OS_Func::_free_base)(_tempMem2);
        this->tempMem = NULL;
    }

} // namespace IO
} // namespace OpenSHC
