#include "../LobbyMenu.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapNameCache.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/INT_00b95ab8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00440A50
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectHeader(int param_1, ...)
        {
            // 0, 1 or 2 for a click on the name, players or balance column; negative to sort by a stored order again
            int const request = param_1;
            DAT_GameSynchronyState::instance.mapExistenceAckCountdown = 0;
            int column = param_1;
            if (param_1 >= 0) {
                if (DAT_00b960dc::instance != 0) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                    return;
                }
            } else {
                // each stored order sets the one its column's click turns into it (the column first, then the
                // order: the other way round loses the match)
                column = -param_1;
                if (column == 1) {
                    column = 0;
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 2;
                } else if (column == 2) {
                    column = 0;
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 1;
                } else if (column == 3) {
                    column = 2;
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 4;
                } else if (column == 4) {
                    column = 2;
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 3;
                } else if (column >= 5) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = column - 1;
                    if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 4) {
                        DAT_GameSynchronyState::instance.lobbyMapSortOrder = 11;
                    }
                    column = 1;
                }
            }
            switch (column) {
            case 0: {
                // by name, which is the maps' own order, the other way round on the next click
                int const last = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 1) {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const second = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const first = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (first < second) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = second;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = first;
                                ++swaps;
                            }
                        }
                    }
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 2;
                } else {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const second = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const first = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (first > second) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = second;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = first;
                                ++swaps;
                            }
                        }
                    }
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 1;
                }
                break;
            }
            case 1: {
                // by players, each click starting one player count further on; the parameter's slot counts the
                // seven tries (a local for them loses the match)
                if ((int)DAT_GameSynchronyState::instance.lobbyMapSortOrder < 5) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                }
                for (param_1 = 7; param_1 > 0;) {
                    int const shift = DAT_GameSynchronyState::instance.lobbyMapSortOrder - 5;
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1; ++i) {
                            int const second = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const first = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if ((DAT_GameSynchronyState::instance.mapPlayerCountArray[first] + shift) % 8
                                > (DAT_GameSynchronyState::instance.mapPlayerCountArray[second] + shift) % 8) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = second;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = first;
                                ++swaps;
                            }
                        }
                    }
                    --param_1;
                    int const order = DAT_GameSynchronyState::instance.lobbyMapSortOrder;
                    ++DAT_GameSynchronyState::instance.lobbyMapSortOrder;
                    if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 12) {
                        DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                    }
                    if (DAT_GameSynchronyState::instance
                            .mapPlayerCountArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[0]]
                        == 13 - order) {
                        break;
                    }
                }
                break;
            }
            case 2: {
                // by balance, the other way round on the next click; every pass takes the second index first
                // (the first one first loses the match)
                int const last = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 3) {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const second = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const first = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (DAT_GameSynchronyState::instance.mapBalanceArray[first]
                                < DAT_GameSynchronyState::instance.mapBalanceArray[second]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = second;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = first;
                                ++swaps;
                            }
                        }
                    }
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 4;
                } else {
                    for (int swaps = 1; swaps != 0;) {
                        swaps = 0;
                        for (int i = 0; i < last; ++i) {
                            int const second = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1];
                            int const first = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i];
                            if (DAT_GameSynchronyState::instance.mapBalanceArray[first]
                                > DAT_GameSynchronyState::instance.mapBalanceArray[second]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i] = second;
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[i + 1] = first;
                                ++swaps;
                            }
                        }
                    }
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 3;
                }
                break;
            }
            }
            if (request >= 0) {
                INT_00b95ab8::instance = 1;
                MACRO_CALL(OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectTable)(
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                return;
            }
            // a stored order: find the chosen map again and scroll the table to it
            for (int found = 0; found < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber; ++found) {
                if (MACRO_CALL(OpenSHC::OS_Func::__stricmp)(DAT_MapNameCache::instance,
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[found]))
                    != 0) {
                    continue;
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = found;
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                if (found < 0) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = found;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                } else if (found > 7) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = found - 7;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 7;
                }
                return;
            }
        }

    }
}
}
