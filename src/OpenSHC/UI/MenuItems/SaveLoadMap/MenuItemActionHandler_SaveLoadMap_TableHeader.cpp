#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/UI/Enums/FileListSortOrder.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492DE0
        void SaveLoadMap::MenuItemActionHandler_SaveLoadMap_TableHeader(int button, ...)
        {
            // the arrows, -1 to -4: -1 - button is the order the sort ends in, so its opposite is set first
            if (button < 0) {
                button = -1 - button;
                switch (button) {
                case OpenSHC::UI::Enums::FLSO_BY_NAME:
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_NAME_REVERSED;
                    break;
                case OpenSHC::UI::Enums::FLSO_BY_NAME_REVERSED:
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_NAME;
                    button = 0;
                    break;
                case OpenSHC::UI::Enums::FLSO_BY_TIME_NEWEST_FIRST:
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_TIME_OLDEST_FIRST;
                    button = 1;
                    break;
                case OpenSHC::UI::Enums::FLSO_BY_TIME_OLDEST_FIRST:
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_TIME_NEWEST_FIRST;
                    button = 1;
                    break;
                }
            }
            switch (button) {
            case 1:
                // by the file's time: a bubble sort, one way or the other
                if (DAT_MenuTextInputState::instance.fileListSortOrder
                    == OpenSHC::UI::Enums::FLSO_BY_TIME_NEWEST_FIRST) {
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
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_TIME_OLDEST_FIRST;
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
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_TIME_NEWEST_FIRST;
                }
                DAT_MenuTextInputState::instance.previewedListIndex = -1;
                return;
            case 0:
                // by name: the list as it was read, or the other way round
                if (DAT_MenuTextInputState::instance.fileListSortOrder == OpenSHC::UI::Enums::FLSO_BY_NAME) {
                    for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount; ++i) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i]
                            = DAT_MenuTextInputState::instance.fileListEntryCount - i - 1;
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_NAME_REVERSED;
                } else {
                    for (int i = 0; i < DAT_MenuTextInputState::instance.fileListEntryCount; ++i) {
                        DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = i;
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = OpenSHC::UI::Enums::FLSO_BY_NAME;
                }
                DAT_MenuTextInputState::instance.previewedListIndex = -1;
                return;
            }
        }

    }
}
}
