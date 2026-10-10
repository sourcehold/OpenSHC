#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449290
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_MapTableHeader(int param_1, ...)
        {
            int iVar1;
            int* puVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            iVar5 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber;
            if (!param_1) {
                iVar3 = 0;
                if (!DAT_MenuTextInputState::instance.fileListSortOrder) {
                    if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                        puVar2 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + 0x1f2;
                        do {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1] = *puVar2;
                            iVar3 = iVar3 + 1;
                            puVar2 = puVar2 + -1;
                        } while (iVar3 < iVar5);
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 1;
                } else {
                    if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                        do {
                            DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 499];
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar5);
                    }
                    DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                }
            } else if (param_1 == 1) {
                iVar5 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                if (DAT_MenuTextInputState::instance.fileListSortOrder == 2) {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar5 <= 0)
                            break;
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if ((int)DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]
                                < DAT_ResourceManager::instance.mapFileTimes[iVar1]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar5);
                    } while (iVar4);
                    DAT_MenuTextInputState::instance.fileListSortOrder = 3;
                } else {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar5 <= 0)
                            break;
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_ResourceManager::instance.mapFileTimes[iVar1] < (int)DAT_ResourceManager::instance
                                    .mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar5);
                    } while (iVar4);
                    DAT_MenuTextInputState::instance.fileListSortOrder = 2;
                }
            } else if (param_1 == 2) {
                iVar5 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 5) {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar5 <= 0)
                            break;
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2[iVar1]
                                < DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2
                                    [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar5);
                    } while (iVar4);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 6;
                } else {
                    do {
                        iVar4 = 0;
                        iVar3 = 0;
                        if (iVar5 <= 0)
                            break;
                        do {
                            iVar1 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2
                                    [DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]
                                < DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2[iVar1]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar1;
                                iVar4 = iVar4 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar5);
                    } while (iVar4);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                }
            }
            MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                    MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
            DAT_MenuTextInputState::instance.lastClickedListIndex = 0xffffffff;
        }

    }
}
}
