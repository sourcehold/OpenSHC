#include "../ResourceManager.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace IO {

    // helper copied from the std lib
    typedef union {
        unsigned long long ft_scalar;
        FILETIME ft_struct;
    } FILETIME_UNION;

    // FUNCTION: STRONGHOLDCRUSADER 0x00477EE0
    void ResourceManager::discoverMapFiles(char* param_1)
    {
        BOOLEnum _hasSwapped = TRUE;
        int _mapIndex = 0;

        FILETIME_UNION filetimeBias;
        filetimeBias.ft_scalar = 0;

        BOOLEnum _missionMaps = FALSE;
        BOOLEnum _originalMaps = FALSE;
        int local_22c = 0;

        if (!MACRO_CALL(OS_Func::__stricmp)(param_1, s_maps_map_005a64b0)) {
            _missionMaps = TRUE;
            _originalMaps = TRUE;
        }
        if (!MACRO_CALL(OS_Func::__stricmp)(param_1, s_mapsExtreme_map_005a649c)) {
            _missionMaps = TRUE;
            _originalMaps = TRUE;
        }

        // the whole time part appears like something that should be part of the std libray, but I found nothing
        // FIXME?: According to the chatbot I used, this seems to lack proper handling for the general bias

        _TIME_ZONE_INFORMATION timeZoneInformation;
        DWORD timeZoneResult = GetTimeZoneInformation(&timeZoneInformation);
        if (timeZoneResult == TIME_ZONE_ID_STANDARD) {
            filetimeBias.ft_scalar = -timeZoneInformation.StandardBias;
        } else if (timeZoneResult == TIME_ZONE_ID_DAYLIGHT) {
            filetimeBias.ft_scalar = -timeZoneInformation.DaylightBias;
        }
        filetimeBias.ft_scalar *= 600000000; // transform into filetime ticks

        this->mapFileCounter = 0;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            500000, 0, this->loadedMapNames);

        HANDLE _handle;

        WIN32_FIND_DATAA _win32FindData;
        _handle = FindFirstFileA(param_1, &_win32FindData);
        if (_handle == INVALID_HANDLE_VALUE) {
            return;
        }

        while (this->mapFileCounter < 500) {
            MACRO_CALL_MEMBER(LowLevelMemory_Func::copyStringUntilFirstDot, DAT_LowLevelMemory::ptr)(
                _win32FindData.cFileName, this->loadedMapNames[this->mapFileCounter]);

            {
                FILETIME_UNION currentFileTime;
                currentFileTime.ft_struct = _win32FindData.ftLastWriteTime;
                currentFileTime.ft_scalar += filetimeBias.ft_scalar;

                WORD fatDate;
                WORD fatTime;
                FileTimeToDosDateTime(&currentFileTime.ft_struct, &fatDate, &fatTime);

                // this might indicate that they used a struct here to handle the time
                // although other usages use it like a number
                this->mapFileTimes[this->mapFileCounter] = (fatDate << 16) + fatTime;
            }

            // since all strings are of type ptr, I can not get the length of the string during runtime via sizeof
            // "magic numbers" here consider the length of "mission" and in relation to that

            if (_missionMaps
                && !MACRO_CALL(OS_Func::__strnicmp)(this->loadedMapNames[this->mapFileCounter], s_mission_005a6494, 7)
                && this->loadedMapNames[this->mapFileCounter][7] >= '0'
                && this->loadedMapNames[this->mapFileCounter][7] <= '9') {

                if (this->loadedMapNames[this->mapFileCounter][7] == '1') {
                    if (this->loadedMapNames[this->mapFileCounter][8] < '0'
                        || this->loadedMapNames[this->mapFileCounter][8] > '9'
                        || this->loadedMapNames[this->mapFileCounter][9] != '\0') {
                        if (this->loadedMapNames[this->mapFileCounter][8] != '\0') {
                            goto keepMap;
                        }
                    }
                } else if (this->loadedMapNames[this->mapFileCounter][7] == '2') {
                    if (this->loadedMapNames[this->mapFileCounter][8] < '0'
                        || this->loadedMapNames[this->mapFileCounter][8] > '1'
                        || this->loadedMapNames[this->mapFileCounter][9] != '\0') {
                        if (this->loadedMapNames[this->mapFileCounter][8] != '\0') {
                            goto keepMap;
                        }
                    }
                } else if (this->loadedMapNames[this->mapFileCounter][7] == '3') {
                    if (this->loadedMapNames[this->mapFileCounter][8] < '3'
                        || this->loadedMapNames[this->mapFileCounter][8] > '7'
                        || this->loadedMapNames[this->mapFileCounter][9] != '\0') {
                        if (this->loadedMapNames[this->mapFileCounter][8] != '\0') {
                            goto keepMap;
                        }
                    }
                } else {
                    if (this->loadedMapNames[this->mapFileCounter][8] != '\0') {
                        goto keepMap;
                    }
                }

                MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    1000, '\0', this->loadedMapNames[this->mapFileCounter]);
                --this->mapFileCounter;

            keepMap:; // best matching solution so far
            }

            ++this->mapFileCounter;
            if (FindNextFileA(_handle, &_win32FindData)) {
                continue;
            }
            if (!_originalMaps || local_22c) {
                break;
            }
            local_22c = 1;

            // required, otherwise copy elision will not work
            std::string path(this->paths_getDocumentsMapsFolderString(TRUE));
            path.append(s__map_005a648c);

            // does this truly overwrite?
            _handle = FindFirstFileA(path.c_str(), &_win32FindData);
            if (_handle == INVALID_HANDLE_VALUE) {
                break;
            }
        }

        if (_originalMaps) {
            do {
                ++_mapIndex;
                if (!_hasSwapped) {
                    break;
                }
                _hasSwapped = FALSE;
                for (int _currentMapIndex = 0; _currentMapIndex < this->mapFileCounter - _mapIndex;
                    ++_currentMapIndex) {
                    if (this->loadedMapNames[_currentMapIndex][0] == '\0'
                        || this->loadedMapNames[_currentMapIndex + 1][0] == '\0') {
                        break;
                    }

                    int receiver;
                    char* _Str2 = MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                        this->loadedMapNames[_currentMapIndex + 1], &receiver);
                    char* _Str1 = MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                        this->loadedMapNames[_currentMapIndex], &receiver);
                    if (MACRO_CALL(OS_Func::__stricmp)(_Str1, _Str2) > 0) {
                        MACRO_CALL_MEMBER(ResourceManager_Func::swapMapDataWithNextMap, this)(_currentMapIndex);
                        _hasSwapped = TRUE;
                    }
                }
            } while (_mapIndex < 500);
        } else {
            do {
                ++_mapIndex;
                if (!_hasSwapped) {
                    break;
                }
                _hasSwapped = FALSE;

                for (int _currentMapIndex = 0; _currentMapIndex < this->mapFileCounter - _mapIndex;
                    ++_currentMapIndex) {
                    if (this->loadedMapNames[_currentMapIndex][0] == '\0'
                        || this->loadedMapNames[_currentMapIndex + 1][0] == '\0') {
                        break;
                    }

                    if (MACRO_CALL(OS_Func::__stricmp)(
                            this->loadedMapNames[_currentMapIndex], this->loadedMapNames[_currentMapIndex + 1])
                        > 0) {
                        MACRO_CALL_MEMBER(ResourceManager_Func::swapMapDataWithNextMap, this)(_currentMapIndex);
                        _hasSwapped = TRUE;
                    }
                }
            } while (_mapIndex < 500);
        }
        FindClose(_handle);
    }

} // namespace IO
} // namespace OpenSHC
