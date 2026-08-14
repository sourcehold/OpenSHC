#include "../FilePackager.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SkirmishLobbySetupStructureLongMapName.hpp"
#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00474A20
    void FilePackager::readMapOrSavFile(MapSectionAddress* mapSectionAddrArray)
    {
        RenderLoadAndSaveBar* _loadAndSaveBarFunc = this->loadAndSaveBarFunc;
        this->loadAndSaveBarFunc = NULL;

        this->tempMem = MACRO_CALL(OS_Func::_malloc)(6000000);
        if (!this->tempMem) {
            return;
        }

        void* _previewOrDescriptionUnk = MACRO_CALL(OS_Func::_malloc)(100000);
        if (!_previewOrDescriptionUnk) {
            return;
        }

        char* _mapName
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        int _fileDescriptor = MACRO_CALL(OS_Func::_ucrt_open)(_mapName, _O_BINARY, 0);
        if (_fileDescriptor == -1) {
            MACRO_CALL(OS_Func::_free_base)(_previewOrDescriptionUnk);
            MACRO_CALL(OS_Func::_free_base)(this->tempMem);
            this->tempMem = NULL;
            return;
        }

        if (DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 == 5) {
            DAT_SoundEffectsHelperData1::instance.SEC_Section1079.field0_0x0 = 1;
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
        }

        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::mapLoadingAndLaunchGameRelated1, DAT_SoundSystemState::ptr)();

        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
            sizeof(DAT_GameState::instance.mapAndTime), 0, &DAT_GameState::instance.mapAndTime);

        DAT_GameCore::instance.temporaryTextBufferOfSize1000[0] = '\0';
        DAT_GameCore::instance.mapU4Int0 = 0;
        DAT_GameCore::instance.mapU4Int1 = 0;

        for (int i = 0; i < 9; ++i) {
            DAT_BlendingDefinedData::instance.SEC_PlayerSlotUnitColor[i]
                = DAT_BlendingDefinedData::instance.DAT_DefaultPlayerSlotUnitColor[i];
        }

        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::fillWith0xFF, DAT_GameState::ptr)();

        DAT_GameCore::instance.mapU4Int3_balanced = 0;
        DAT_GameState::instance.mapAndTime.field3186_0x27e4 = 0;
        DAT_GameState::instance.mapAndTime.field3187_0x27e8 = 0;
        DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
        DAT_GameCore::instance.altRToggleMinimapHideWildlife = 0;

        for (int i = 0; i < 8; ++i) {
            DAT_MinimapViewState::instance.DAT_MapU4B64.keepPositions[i].x = -1;
            DAT_MinimapViewState::instance.DAT_MapU4B64.keepPositions[i].y = -1;
        }
        for (int i = 0; i < 9; ++i) {
            DAT_GameState::instance.mapAndTime.playerGroupArray[i] = 0;
        }
        for (int i = 0; i < 1000; ++i) {
            DAT_AICState::instance.tribeIDArray[i] = 0;
            DAT_AICState::instance.tribeUIDArray[i] = 0;
        }

        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->directorySize, sizeof(this->directorySize));
        if (this->directorySize < 0) {
            int _size;

            // preview size
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
            if (_size) {
                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, _previewOrDescriptionUnk, _size);

                // description size
                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                if (_size) {
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &DAT_GameCore::instance.descriptionUseStringTable,
                        sizeof(DAT_GameCore::instance.descriptionUseStringTable));
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                        &DAT_GameCore::instance.descriptionStringTableIndex,
                        sizeof(DAT_GameCore::instance.descriptionStringTableIndex));
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, _previewOrDescriptionUnk, _size - 8);
                    MACRO_CALL_MEMBER(DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                        _previewOrDescriptionUnk, DAT_GameCore::instance.temporaryTextBufferOfSize1000);

                    // Map.u1 size
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                    if (_size) {
                        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                            &DAT_GameSynchronyState::instance.savedMapTimeInTicks,
                            sizeof(DAT_GameSynchronyState::instance.savedMapTimeInTicks));
                        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                            &DAT_GameSynchronyState::instance.savedUnitsCRC32Hash,
                            sizeof(DAT_GameSynchronyState::instance.savedUnitsCRC32Hash));

                        // Map.u2 size
                        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                        if (_size != 0) {
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                &DAT_GameCore::instance.U2_mapType_singleOrMulti,
                                sizeof(DAT_GameCore::instance.U2_mapType_singleOrMulti));
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &DAT_GameCore::instance.mapU2MiddleBytes,
                                sizeof(DAT_GameCore::instance.mapU2MiddleBytes));
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &DAT_GameCore::instance.mapU2PlayersCount,
                                sizeof(DAT_GameCore::instance.mapU2PlayersCount));

                            // Map.u3 size
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                            if (_size) {
                                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                    &DAT_MapPropertiesState::instance.scenarionMissionType,
                                    sizeof(DAT_MapPropertiesState::instance.scenarionMissionType));

                                if (_size > 4) {
                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                        &DAT_MapPropertiesState::instance.SEC_U3_MapType2_1,
                                        sizeof(DAT_MapPropertiesState::instance.SEC_U3_MapType2_1));

                                    if (_size > 8) {
                                        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                            &DAT_GameCore::instance.U3_mapLockedState,
                                            sizeof(DAT_GameCore::instance.U3_mapLockedState));

                                        if (_size > 12) {
                                            MACRO_CALL(OS_Func::_ucrt_read)(
                                                _fileDescriptor, DAT_GameCore::instance.standaloneFilename, _size - 16);

                                            if (_size >= 93) {
                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                                    &DAT_GameCore::instance.mapU3EndInt,
                                                    sizeof(DAT_GameCore::instance.mapU3EndInt));
                                            }
                                        }
                                    }
                                }

                                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                                if (_size) {
                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &DAT_GameCore::instance.mapU4Int0,
                                        sizeof(DAT_GameCore::instance.mapU4Int0));

                                    if (_size > 4) {
                                        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                            &DAT_GameCore::instance.mapU4Int1,
                                            sizeof(DAT_GameCore::instance.mapU4Int1));

                                        if (_size > 8) {
                                            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                                &DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes,
                                                sizeof(DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes));

                                            if (_size > 12) {
                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                                    &DAT_GameCore::instance.mapU4Int3_balanced,
                                                    sizeof(DAT_GameCore::instance.mapU4Int3_balanced));
                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor,
                                                    &DAT_MinimapViewState::instance.DAT_MapU4B64,
                                                    sizeof(DAT_MinimapViewState::instance.DAT_MapU4B64));
                                            }
                                        }
                                    }
                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &_size, sizeof(_size));
                                }
                            }
                        }
                    }
                }
            }
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->directorySize, sizeof(this->directorySize));
        }

        if (this->directorySize == 2036) {
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->oldDirectory, sizeof(this->oldDirectory));
            MACRO_CALL_MEMBER(FilePackager_Func::copyFromOldToNewMapDirectory, this)();
        } else {
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, &this->directory, this->directorySize - 4);
        }

        MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, this->tempMem, this->directory.filePayloadSize);
        MACRO_CALL(OS_Func::_ucrt_close)(_fileDescriptor);

        DAT_GameCore::instance.descriptionUseStringTable = 0;

        // Block needed to remove referenced variable from global stack. Otherwise it would contribute to stack size.
        {
            int _hardcodedMapTextAddressUnk;
            MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::getCurrentResourceCoreNameUnk, DAT_ResourceManager::ptr)(),
                &_hardcodedMapTextAddressUnk);
            if (_hardcodedMapTextAddressUnk) {
                DAT_GameCore::instance.descriptionUseStringTable = 1;
                DAT_GameCore::instance.descriptionStringTableIndex = _hardcodedMapTextAddressUnk;
            }
        }

        this->versionNumOfCurrentFileTypeUnk = this->directory.magicNumOfFileType;
        if (_loadAndSaveBarFunc) {
            (*_loadAndSaveBarFunc)(50);
        }
        this->currentlyReadFileSectionIndex = 0;
        this->directory.filePayloadSize = 0;

        MapSectionAddress* _sectionAddressListStart = mapSectionAddrArray;
        while (this->currentlyReadFileSectionIndex < this->directory.sectionCount) {
            mapSectionAddrArray = _sectionAddressListStart;

            if (this->directory.id[this->currentlyReadFileSectionIndex] == 1095
                && this->directory.uncompressedSize[this->currentlyReadFileSectionIndex] > 4) {
                ++this->currentlyReadFileSectionIndex;
                continue;
            }

            while (this->currentlyReadFileSectionIndex < 150) {
                this->currentlyReadFileSectionMemory = mapSectionAddrArray->address;
                this->currentlyReadFileSectionSize = mapSectionAddrArray->size;
                if (this->currentlyReadFileSectionMemory <= NULL
                    || this->directory.id[this->currentlyReadFileSectionIndex] == mapSectionAddrArray->sectionId) {
                    break;
                }
                ++mapSectionAddrArray;
            }

            if (this->currentlyReadFileSectionMemory > NULL && !mapSectionAddrArray->unknown) {
                if (!this->directory.isCompressed[this->currentlyReadFileSectionIndex]
                    || this->CRASHES_saveUncompressedUnk) {

                    if (mapSectionAddrArray->sectionId == 1124
                        && this->directory.uncompressedSize[this->currentlyReadFileSectionIndex]
                            == sizeof(SkirmishLobbySetupStructureLongName)) {
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                            sizeof(SkirmishLobbySetupStructureLongName),
                            (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                            DAT_SkirmishLobbySetupStructureLongMapName::ptr);
                        MACRO_CALL(Map::Version_Func::UpgradeOldSection1124)();
                    } else {
                        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                            this->directory.uncompressedSize[this->currentlyReadFileSectionIndex],
                            (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                            this->currentlyReadFileSectionMemory);
                    }

                } else {
                    MACRO_CALL_MEMBER(DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                        (void*)((int)this->tempMem + this->directory.offset[this->currentlyReadFileSectionIndex]),
                        this->currentlyReadFileSectionMemory);
                }
            }

            if (_loadAndSaveBarFunc) {
                (*_loadAndSaveBarFunc)(
                    (this->currentlyReadFileSectionIndex * 950) / (this->directory.sectionCount + -1) + 50);
            }
            ++this->currentlyReadFileSectionIndex;
        }

        MACRO_CALL(OS_Func::_free_base)(this->tempMem);
        MACRO_CALL(OS_Func::_free_base)(_previewOrDescriptionUnk);

        this->tempMem = NULL;
        DAT_SoundEffectsHelperData1::instance.DAT_NegativeCountdownMin1ToMin4Becomes0 = 0;
        DAT_SoundEffectsHelperData1::instance.field13_0x50 = 0;
        DAT_SoundSystemState::instance.currentSoundID_0x3278 = -1;
        DAT_GameCore::instance.field40_0xa0 = DAT_GameCore::instance.mapTimeInTicks;
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
            DAT_GameCore::instance.historicCampaignNumber = 4;

            if (DAT_GameCore::instance.missionNumber1to20 <= 15) {
                DAT_GameCore::instance.historicCampaignNumber = 3;
            }

            if (DAT_GameCore::instance.missionNumber1to20 <= 10) {
                DAT_GameCore::instance.historicCampaignNumber = 2;
            }

            if (DAT_GameCore::instance.missionNumber1to20 <= 5) {
                DAT_GameCore::instance.historicCampaignNumber = 1;
            }
        }

        DAT_GameCore::instance.timeSum_2 = timeGetTime() - DAT_GameCore::instance.gameDuration;
        TIME_ReceivedMessage_2::instance = 0;
    }

} // namespace IO
} // namespace OpenSHC
