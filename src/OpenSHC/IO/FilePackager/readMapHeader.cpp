#include "../FilePackager.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004752D0
    void FilePackager::readMapHeader(BOOLEnum loadPreviewUnk)
    {
        void* _dynamicHeaderBuffer = NULL;
        if (loadPreviewUnk) {
            _dynamicHeaderBuffer = MACRO_CALL(OS_Func::_malloc)(100000);
            if (!_dynamicHeaderBuffer) {
                return;
            }
            MACRO_CALL(OS_Func::_memset)(
                DAT_MinimapViewState::instance.loadedMiniMap, 0, sizeof(DAT_MinimapViewState::instance.loadedMiniMap));
        }

        DAT_GameCore::instance.mapDescription[0] = '\0';
        DAT_GameCore::instance.mapType = 0;
        DAT_GameCore::instance.savedMapLocked = Map::MLS_EDITABLE;
        DAT_GameCore::instance.mapU4Int0_2 = 0;
        DAT_GameCore::instance.mapU4Int1_2 = 0;
        DAT_GameCore::instance.savedMapBalance = 0;
        DAT_GameCore::instance.savedMapEndInt2 = 0;

        for (int i = 0; i < 8; i++) {
            DAT_GameCore::instance.keepPositions[i].x = -1;
            DAT_GameCore::instance.keepPositions[i].y = -1;
        }

        char* _nameOfActiveResource
            = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        int _fileHandle = MACRO_CALL(OS_Func::_ucrt_open)(_nameOfActiveResource, _O_BINARY, 0);
        if (_fileHandle == -1) {
            if (_dynamicHeaderBuffer) {
                MACRO_CALL(OS_Func::_free_base)(_dynamicHeaderBuffer);
            }
            this->tempMem = NULL;
            return;
        }

        // General logic of this formats seems to be "size of content" -> "content" -> "size of content" -> etc.
        // The last element in this line is a "size of content" == 0, indicating the end of the structure.

        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &this->directorySize, sizeof(this->directorySize));
        if (this->directorySize < 0) {
            int _dataLength;

            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
            if (_dataLength) {

                if (loadPreviewUnk) {
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, _dynamicHeaderBuffer, _dataLength);
                    MACRO_CALL_MEMBER(DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                        _dynamicHeaderBuffer, DAT_MinimapViewState::instance.loadedMiniMap);
                    MACRO_CALL_MEMBER(
                        UI::MinimapViewState_Func::convertLoadedMinimapColors, DAT_MinimapViewState::ptr)();
                } else {
                    MACRO_CALL(OS_Func::_ucrt_lseek)(_fileHandle, _dataLength, FILE_CURRENT);
                }

                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                if (_dataLength) {
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &DAT_GameCore::instance.mapDescUseStringTable,
                        sizeof(DAT_GameCore::instance.mapDescUseStringTable));
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &DAT_GameCore::instance.mapDescUseStringTableIndex,
                        sizeof(DAT_GameCore::instance.mapDescUseStringTableIndex));

                    char _compressedDescriptionBuffer[1100];
                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, _compressedDescriptionBuffer,
                        _dataLength - sizeof(DAT_GameCore::instance.mapDescUseStringTable)
                            - sizeof(DAT_GameCore::instance.mapDescUseStringTableIndex));
                    if (loadPreviewUnk) {
                        MACRO_CALL_MEMBER(DecoderState_Func::decodeData, DAT_DecoderState::ptr)(
                            _compressedDescriptionBuffer, DAT_GameCore::instance.mapDescription);
                    }

                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                    if (_dataLength) {
                        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                            &DAT_GameSynchronyState::instance.savedMapTimeInTicks,
                            sizeof(DAT_GameSynchronyState::instance.savedMapTimeInTicks));
                        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                            &DAT_GameSynchronyState::instance.savedUnitsCRC32Hash,
                            sizeof(DAT_GameSynchronyState::instance.savedUnitsCRC32Hash));

                        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                        if (_dataLength) {
                            MACRO_CALL(OS_Func::_ucrt_read)(
                                _fileHandle, &DAT_GameCore::instance.mapType, sizeof(DAT_GameCore::instance.mapType));
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, DAT_GameCore::instance.sh1MapKeeps,
                                sizeof(DAT_GameCore::instance.sh1MapKeeps));
                            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &DAT_GameCore::instance.mapPlayerCount,
                                sizeof(DAT_GameCore::instance.mapPlayerCount));

                            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                            if (_dataLength) {
                                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                    &DAT_MapPropertiesState::instance.scenarionMissionType,
                                    sizeof(DAT_MapPropertiesState::instance.scenarionMissionType));

                                if (_dataLength > 4) {
                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                        &DAT_MapPropertiesState::instance.scenarioMissionSiegeOrInvasion,
                                        sizeof(DAT_MapPropertiesState::instance.scenarioMissionSiegeOrInvasion));

                                    if (_dataLength > 8) {
                                        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                            &DAT_GameCore::instance.savedMapLocked,
                                            sizeof(DAT_GameCore::instance.savedMapLocked));

                                        if (_dataLength > 12) {
                                            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                                DAT_GameCore::instance.standaloneFilename, _dataLength - 16);

                                            // different then similar structure in readMapOrSavFile (_size >= 93)
                                            if (_dataLength > 93) {
                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                                    &DAT_GameCore::instance.savedMapEndInt2,
                                                    sizeof(DAT_GameCore::instance.savedMapEndInt2));
                                            }
                                        }
                                    }
                                }

                                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                                if (_dataLength) {
                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &DAT_GameCore::instance.mapU4Int0_2,
                                        sizeof(DAT_GameCore::instance.mapU4Int0_2));

                                    if (_dataLength > 4) {
                                        MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                            &DAT_GameCore::instance.mapU4Int1_2,
                                            sizeof(DAT_GameCore::instance.mapU4Int1_2));

                                        if (_dataLength > 8) {
                                            MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                                &DAT_GameSynchronyState::instance.DAT_MapU4Int2_2,
                                                sizeof(DAT_GameSynchronyState::instance.DAT_MapU4Int2_2));

                                            if (_dataLength > 12) {
                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                                    &DAT_GameCore::instance.savedMapBalance,
                                                    sizeof(DAT_GameCore::instance.savedMapBalance));

                                                MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle,
                                                    &DAT_GameCore::instance.keepPositions,
                                                    sizeof(DAT_GameCore::instance.keepPositions));
                                            }
                                        }
                                    }

                                    MACRO_CALL(OS_Func::_ucrt_read)(_fileHandle, &_dataLength, sizeof(_dataLength));
                                }
                            }
                        }
                    }
                }
            }
        }
        MACRO_CALL(OS_Func::_ucrt_close)(_fileHandle);
        DAT_GameCore::instance.mapDescUseStringTable = 0;

        {
            int _hardcodedMapTextAddressUnk;
            MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                MACRO_CALL_MEMBER(ResourceManager_Func::getCurrentResourceCoreNameUnk, DAT_ResourceManager::ptr)(),
                &_hardcodedMapTextAddressUnk);
        }

        if (_dynamicHeaderBuffer) {
            MACRO_CALL(OS_Func::_free_base)(_dynamicHeaderBuffer);
        }
    }

} // namespace IO
} // namespace OpenSHC
