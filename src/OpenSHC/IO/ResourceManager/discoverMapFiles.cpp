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
    void ResourceManager::discoverMapFiles(char const* param_1)
    {
        struct ScanState {
            BOOLEnum _missionMaps;
            BOOLEnum _originalMaps;
            HANDLE _handle;
            __declspec(align(4)) WORD fatDate;
            __declspec(align(4)) WORD fatTime;
            BOOLEnum originalMapsScanned;
        } scan;
        ResourceManager* __restrict manager = this;
        BOOLEnum _hasSwapped = TRUE;
        int _mapIndex = 0;

        FILETIME_UNION filetimeBias;
        filetimeBias.ft_scalar = 0;

        scan._missionMaps = FALSE;
        scan._originalMaps = FALSE;
        scan.originalMapsScanned = FALSE;

        if (!MACRO_CALL(OS_Func::__stricmp)(param_1, s_maps_map_005a64b0)) {
            scan._missionMaps = TRUE;
            scan._originalMaps = TRUE;
        }
        if (!MACRO_CALL(OS_Func::__stricmp)(param_1, s_mapsExtreme_map_005a649c)) {
            scan._missionMaps = TRUE;
            scan._originalMaps = TRUE;
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

        manager->mapFileCounter = 0;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            500000, 0, manager->loadedMapNames);

        WIN32_FIND_DATAA _win32FindData;
        scan._handle = FindFirstFileA(param_1, &_win32FindData);
        if (scan._handle == INVALID_HANDLE_VALUE) {
            return;
        }

        for (; manager->mapFileCounter < 500;) {
            MACRO_CALL_MEMBER(LowLevelMemory_Func::copyStringUntilFirstDot, DAT_LowLevelMemory::ptr)(
                _win32FindData.cFileName, manager->loadedMapNames[manager->mapFileCounter]);

            {
                FILETIME_UNION currentFileTime;
                currentFileTime.ft_struct = _win32FindData.ftLastWriteTime;
                currentFileTime.ft_scalar += filetimeBias.ft_scalar;

                FileTimeToDosDateTime(&currentFileTime.ft_struct, &scan.fatDate, &scan.fatTime);

                // this might indicate that they used a struct here to handle the time
                // although other usages use it like a number
                manager->mapFileTimes[manager->mapFileCounter] = (scan.fatDate << 16) + scan.fatTime;
            }

            // since all strings are of type ptr, I can not get the length of the string during runtime via sizeof
            // "magic numbers" here consider the length of "mission" and in relation to that

            if (scan._missionMaps
                && !MACRO_CALL(OS_Func::__strnicmp)(manager->loadedMapNames[manager->mapFileCounter], s_mission_005a6494, 7)
                && manager->loadedMapNames[manager->mapFileCounter][7] >= '0'
                && manager->loadedMapNames[manager->mapFileCounter][7] <= '9') {

                bool removeMap = false;
                if (manager->loadedMapNames[manager->mapFileCounter][7] == '1') {
                    if ((manager->loadedMapNames[manager->mapFileCounter][8] >= '0'
                            && manager->loadedMapNames[manager->mapFileCounter][8] <= '9'
                            && manager->loadedMapNames[manager->mapFileCounter][9] == '\0')
                        || manager->loadedMapNames[manager->mapFileCounter][8] == '\0') {
                        removeMap = true;
                    }
                } else if (manager->loadedMapNames[manager->mapFileCounter][7] == '2') {
                    if ((manager->loadedMapNames[manager->mapFileCounter][8] >= '0'
                            && manager->loadedMapNames[manager->mapFileCounter][8] <= '1'
                            && manager->loadedMapNames[manager->mapFileCounter][9] == '\0')
                        || manager->loadedMapNames[manager->mapFileCounter][8] == '\0') {
                        removeMap = true;
                    }
                } else if (manager->loadedMapNames[manager->mapFileCounter][7] == '3') {
                    if ((manager->loadedMapNames[manager->mapFileCounter][8] >= '3'
                            && manager->loadedMapNames[manager->mapFileCounter][8] <= '7'
                            && manager->loadedMapNames[manager->mapFileCounter][9] == '\0')
                        || manager->loadedMapNames[manager->mapFileCounter][8] == '\0') {
                        removeMap = true;
                    }
                } else if (manager->loadedMapNames[manager->mapFileCounter][8] == '\0') {
                    removeMap = true;
                }

                if (removeMap) {
                    MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        1000, '\0', manager->loadedMapNames[manager->mapFileCounter]);
                    --manager->mapFileCounter;
                }
            }

            ++manager->mapFileCounter;
            if (FindNextFileA(scan._handle, &_win32FindData)) {
                continue;
            }
            if (!scan._originalMaps || scan.originalMapsScanned) {
                break;
            }
            scan.originalMapsScanned = TRUE;

            // required, otherwise copy elision will not work
            std::string path(manager->paths_getDocumentsMapsFolderString(TRUE));
            path.append(s__map_005a648c);

            // The game replaces the first search handle here, even if opening the second search fails.
            // Both paths use this replacement handle for the final FindClose after sorting.
            scan._handle = FindFirstFileA(path.c_str(), &_win32FindData);
            if ((reinterpret_cast<UINT_PTR>(scan._handle) + 1u) == 0) {
                break;
            }
        }

        if (scan._originalMaps) {
            for (; _mapIndex < 500;) {
                ++_mapIndex;
                if (!_hasSwapped) {
                    break;
                }
                _hasSwapped = FALSE;
                for (int _currentMapIndex = 0; _currentMapIndex < manager->mapFileCounter - _mapIndex;
                    ++_currentMapIndex) {
                    if (manager->loadedMapNames[_currentMapIndex][0] == '\0'
                        || manager->loadedMapNames[_currentMapIndex + 1][0] == '\0') {
                        break;
                    }

                    char* _Str2 = MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                        manager->loadedMapNames[_currentMapIndex + 1], &scan.originalMapsScanned);
                    char* _Str1 = MACRO_CALL(Global_Func::GetStringBasedOnHardcodedMaps)(
                        manager->loadedMapNames[_currentMapIndex], &scan._missionMaps);
                    if (MACRO_CALL(OS_Func::__stricmp)(_Str1, _Str2) > 0) {
                        MACRO_CALL_MEMBER(ResourceManager_Func::swapMapDataWithNextMap, this)(_currentMapIndex);
                        _hasSwapped = TRUE;
                    }
                }
            }
        } else {
            for (; _mapIndex < 500;) {
                ++_mapIndex;
                if (!_hasSwapped) {
                    break;
                }
                _hasSwapped = FALSE;

                for (int _currentMapIndex = 0; _currentMapIndex < manager->mapFileCounter - _mapIndex;
                    ++_currentMapIndex) {
                    if (manager->loadedMapNames[_currentMapIndex][0] == '\0'
                        || manager->loadedMapNames[_currentMapIndex + 1][0] == '\0') {
                        break;
                    }

                    if (MACRO_CALL(OS_Func::__stricmp)(
                            manager->loadedMapNames[_currentMapIndex], manager->loadedMapNames[_currentMapIndex + 1])
                        > 0) {
                        MACRO_CALL_MEMBER(ResourceManager_Func::swapMapDataWithNextMap, this)(_currentMapIndex);
                        _hasSwapped = TRUE;
                    }
                }
            }
        }
        FindClose(scan._handle);
    }

} // namespace IO
} // namespace OpenSHC
