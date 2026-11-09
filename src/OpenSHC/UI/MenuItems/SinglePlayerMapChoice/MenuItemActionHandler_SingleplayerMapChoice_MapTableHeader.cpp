#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449290
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader(int column, ...)
        {
            // A click on a column header sorts the map list by that column, and a second click reverses the order
            switch (column) {
            case 0: {
                // Name: the order kept in DAT_ArrayOfMapIndices2 (read with - 1, as its other users do), backwards
                // after the first click
                if (DAT_MenuTextInputState::instance.fileListSortOrder == 0) {
                    for (int i = 0; i < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber; ++i) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                            = DAT_MenuTextInputState::instance
                                  .DAT_ArrayOfMapIndices2[DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber
                                      - 2 - i];
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                    break;
                }
                int i = 0;
                if (i < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                    // A guarded do-while: as a for loop MSVC turns the copy into rep movsd
                    do {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                            = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices2[i - 1];
                        ++i;
                    } while (i < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber);
                }
                DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                break;
            }
            case 1: {
                // Date: a bubble sort on the file times, newest first after the first click
                int const last = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_MenuTextInputState::instance.fileListSortOrder == 2) {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const nextMapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const mapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (DAT_ResourceManager::instance.mapFileTimes[mapIndex]
                                > DAT_ResourceManager::instance.mapFileTimes[nextMapIndex]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = nextMapIndex;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = mapIndex;
                                ++swaps;
                            }
                        }
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                    break;
                }
                for (int swaps = 1; swaps != 0;) {
                    swaps = 0;
                    for (int i = 0; i < last; ++i) {
                        int const nextMapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                        int const mapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                        if (DAT_ResourceManager::instance.mapFileTimes[mapIndex]
                            < DAT_ResourceManager::instance.mapFileTimes[nextMapIndex]) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = nextMapIndex;
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = mapIndex;
                            ++swaps;
                        }
                    }
                }
                DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                break;
            }
            case 2: {
                // The third column: a bubble sort on arrayOfMapEndInt2, with its own order flag
                int const last = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 5) {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const nextMapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const mapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (DAT_MenuTextInputState::instance.arrayOfMapEndInt2[mapIndex]
                                < DAT_MenuTextInputState::instance.arrayOfMapEndInt2[nextMapIndex]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = nextMapIndex;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = mapIndex;
                                ++swaps;
                            }
                        }
                    }
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 6;
                    break;
                }
                for (int swaps = 1; swaps != 0;) {
                    swaps = 0;
                    for (int i = 0; i < last; ++i) {
                        int const nextMapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                        int const mapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                        if (DAT_MenuTextInputState::instance.arrayOfMapEndInt2[mapIndex]
                            > DAT_MenuTextInputState::instance.arrayOfMapEndInt2[nextMapIndex]) {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = nextMapIndex;
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = mapIndex;
                            ++swaps;
                        }
                    }
                }
                DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                break;
            }
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                    MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
            DAT_MenuTextInputState::instance.lastClickedListIndex = -1;
        }

    }
}
}
