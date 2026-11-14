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
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            uint uVar5;
            uint uVar6;
            int iVar7;
            int iVar8;
            int iVar9;
            iVar8 = param_1;
            iVar2 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber;
            DAT_GameSynchronyState::instance.mapExistenceAckCountdown = 0;
            if (param_1 < 0) {
                iVar1 = -param_1;
                if (param_1 == -1) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 2;
                    iVar1 = 0;
                } else if (param_1 == -2) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 1;
                    iVar1 = 0;
                } else if (param_1 == -3) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 4;
                    iVar1 = 2;
                } else if (param_1 == -4) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 3;
                    iVar1 = 2;
                } else if (4 < iVar1) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = iVar1 - 1;
                    if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 4) {
                        DAT_GameSynchronyState::instance.lobbyMapSortOrder = 11;
                    }
                    iVar1 = 1;
                }
            } else {
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
                iVar1 = param_1;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                    return;
                }
            }
            // the original dispatches the sort column with a `sub eax, K; je` chain
            // (0x440a9e), MSVC's sparse switch, and the arm bodies sit in the order
            // 2, 1, 0
            switch (iVar1) {
            case 2:
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 3) {
                    do {
                        iVar7 = 0;
                        for (iVar3 = 0; iVar3 < iVar1; ++iVar3) {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            if (DAT_GameSynchronyState::instance.mapBalanceArray[iVar4]
                                < DAT_GameSynchronyState::instance.mapBalanceArray[DAT_MenuTextInputState::instance
                                        .DAT_ArrayOfMapIndices[iVar3 + 1]]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1] = iVar4;
                                ++iVar7;
                            }
                        }
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 4;
                } else {
                    do {
                        iVar7 = 0;
                        for (iVar3 = 0; iVar3 < iVar1; ++iVar3) {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            if (DAT_GameSynchronyState::instance
                                    .mapBalanceArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1]]
                                < DAT_GameSynchronyState::instance.mapBalanceArray[iVar4]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1] = iVar4;
                                ++iVar7;
                            }
                        }
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 3;
                }
                break;
            case 1:
                if ((int)DAT_GameSynchronyState::instance.lobbyMapSortOrder < 5) {
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                }
                param_1 = 7;
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                do {
                    iVar3 = DAT_GameSynchronyState::instance.lobbyMapSortOrder - 5;
                    do {
                        iVar9 = 0;
                        iVar7 = DAT_GameSynchronyState::instance.lobbyMapSortOrder;
                        for (iVar4 = 0; iVar4 < iVar1; ++iVar4) {
                            iVar2 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4];
                            uVar5 = (DAT_GameSynchronyState::instance.mapPlayerCountArray[iVar2] + iVar3) % 8;
                            uVar6
                                = (DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                                           .DAT_ArrayOfMapIndices[iVar4 + 1]]
                                      + iVar3)
                                % 8;
                            if ((int)uVar6 < (int)uVar5) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4 + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4 + 1] = iVar2;
                                ++iVar9;
                            }
                            iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                        }
                        iVar7 = DAT_GameSynchronyState::instance.lobbyMapSortOrder;
                        iVar2 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber;
                    } while (iVar9 != 0);
                    --param_1;
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = iVar7 + 1;
                    if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 12) {
                        DAT_GameSynchronyState::instance.lobbyMapSortOrder = 5;
                    }
                } while ((DAT_GameSynchronyState::instance
                                 .mapPlayerCountArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[0]]
                             != 13 - iVar7)
                    && (0 < param_1));
                break;
            case 0:
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 1;
                if (DAT_GameSynchronyState::instance.lobbyMapSortOrder == 1) {
                    do {
                        iVar7 = 0;
                        for (iVar3 = 0; iVar3 < iVar1; ++iVar3) {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            if (iVar4 < (int)DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1] = iVar4;
                                ++iVar7;
                            }
                        }
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 2;
                } else {
                    do {
                        iVar7 = 0;
                        for (iVar3 = 0; iVar3 < iVar1; ++iVar3) {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                            if ((int)DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1] < iVar4) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + 1] = iVar4;
                                ++iVar7;
                            }
                        }
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 1;
                }
                break;
            }
            if (0 <= iVar8) {
                INT_00b95ab8::instance = 1;
                MACRO_CALL(OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectTable)(
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                return;
            }
            iVar8 = 0;
            if (0 < iVar2) {
                while (MACRO_CALL(OpenSHC::OS_Func::__stricmp)(DAT_MapNameCache::instance,
                           MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                               DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar8]))
                    != 0) {
                    ++iVar8;
                    if (iVar8 >= (int)DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                        return;
                    }
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                if (iVar8 < 0) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar8;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = iVar8;
                if (7 < iVar8) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar8 - 7;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 7;
                }
            }
        }

    }
}
}
