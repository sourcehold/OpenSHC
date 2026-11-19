#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492DE0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_TableHeader(int button, ...)
        {
            // the header's arrows, -1 to -4, choose the column and the order the sort below turns round
            if (button < 0) {
                button = -1 - button;
                switch (button) {
                case 0:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                    break;
                case 1:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                    button = 0;
                    break;
                case 2:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                    button = 1;
                    break;
                case 3:
                    DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                    button = 1;
                    break;
                }
            }
            switch (button) {
            case 1:
                // by the file's time: a bubble sort, one way or the other
                if (DAT_MenuTextInputState::instance.fileListSortOrder == 2) {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount - 1; ++i) {
                            if (DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]]
                                > DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1]]) {
                                int const moved = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = moved;
                                ++swaps;
                            }
                        }
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                } else {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount - 1; ++i) {
                            if (DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]]
                                < DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1]]) {
                                int const moved = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = moved;
                                ++swaps;
                            }
                        }
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                }
                DAT_MenuTextInputState::instance.previewedListIndex = -1;
                return;
            case 0:
                // by name: the list as it was read, or the other way round
                if (DAT_MenuTextInputState::instance.fileListSortOrder == 0) {
                    for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount; ++i) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                            = DAT_MenuTextInputState::instance.fileListEntryCount - i - 1;
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                } else {
                    for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount; ++i) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = i;
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                }
                DAT_MenuTextInputState::instance.previewedListIndex = -1;
                return;
            }
        }

    }
}
}
