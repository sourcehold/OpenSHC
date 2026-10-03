#include "../LobbyMenu.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuItems/LobbyMenu.func.hpp"
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

        using OpenSHC::UI::Enums::MenuModalType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00440A50
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectHeader(int param_1, ...)
        {
            int iVar1;
            char* _Str2;
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
            DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
            if (param_1 < 0) {
                iVar1 = -param_1;
                if (param_1 == -1) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = 2;
                    iVar1 = 0;
                } else if (param_1 == -2) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = 1;
                    iVar1 = 0;
                } else if (param_1 == -3) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = 4;
                    iVar1 = 2;
                } else if (param_1 == -4) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = 3;
                    iVar1 = 2;
                } else if (4 < iVar1) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = iVar1 + -1;
                    if (DAT_GameSynchronyState::instance.field248_0x109250 == 4) {
                        DAT_GameSynchronyState::instance.field248_0x109250 = 0xb;
                    }
                    iVar1 = 1;
                }
            } else {
                if (DAT_00b960dc::instance != 0) {
                    DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                    DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                    DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
                }
                iVar1 = param_1;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                    DAT_GameSynchronyState::instance.field239_0x1072f8 = 0;
                }
            }
            if (iVar1 == 0) {
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                if (DAT_GameSynchronyState::instance.field248_0x109250 == 1) {
                    do {
                        iVar7 = 0;
                        iVar3 = 0;
                        if (iVar1 < 1)
                            break;
                        do {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (iVar4 < (int)DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar4;
                                iVar7 = iVar7 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar1);
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.field248_0x109250 = 2;
                } else {
                    do {
                        iVar7 = 0;
                        iVar3 = 0;
                        if (iVar1 < 1)
                            break;
                        do {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if ((int)DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] < iVar4) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar4;
                                iVar7 = iVar7 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar1);
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.field248_0x109250 = 1;
                }
            } else if (iVar1 == 1) {
                if (DAT_GameSynchronyState::instance.field248_0x109250 < 5) {
                    DAT_GameSynchronyState::instance.field248_0x109250 = 5;
                }
                param_1 = 7;
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                do {
                    iVar3 = DAT_GameSynchronyState::instance.field248_0x109250 + -5;
                    do {
                        iVar9 = 0;
                        iVar4 = 0;
                        iVar7 = DAT_GameSynchronyState::instance.field248_0x109250;
                        if (iVar1 < 1)
                            break;
                        do {
                            iVar2 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4 + -1];
                            uVar5 = DAT_GameSynchronyState::instance.mapPlayerCountArray[iVar2] + iVar3 & 0x80000007;
                            if ((int)uVar5 < 0) {
                                uVar5 = (uVar5 - 1 | 0xfffffff8) + 1;
                            }
                            uVar6
                                = DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                                          .DAT_ArrayOfMapIndices[iVar4]]
                                    + iVar3
                                & 0x80000007;
                            if ((int)uVar6 < 0) {
                                uVar6 = (uVar6 - 1 | 0xfffffff8) + 1;
                            }
                            if ((int)uVar6 < (int)uVar5) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar4] = iVar2;
                                iVar9 = iVar9 + 1;
                            }
                            iVar4 = iVar4 + 1;
                            iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                        } while (iVar4 < iVar1);
                        iVar7 = DAT_GameSynchronyState::instance.field248_0x109250;
                        iVar2 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber;
                    } while (iVar9 != 0);
                    param_1 = param_1 + -1;
                    DAT_GameSynchronyState::instance.field248_0x109250 = iVar7 + 1;
                    if (DAT_GameSynchronyState::instance.field248_0x109250 == 0xc) {
                        DAT_GameSynchronyState::instance.field248_0x109250 = 5;
                    }
                } while ((DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                                  .DAT_MapSelectionPreloadMapIndexMapping]
                             != 0xd - iVar7)
                    && (0 < param_1));
            } else if (iVar1 == 2) {
                iVar1 = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -1;
                if (DAT_GameSynchronyState::instance.field248_0x109250 == 3) {
                    do {
                        iVar7 = 0;
                        iVar3 = 0;
                        if (iVar1 < 1)
                            break;
                        do {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_GameSynchronyState::instance.mapBalanceArray[iVar4]
                                < DAT_GameSynchronyState::instance
                                    .mapBalanceArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar4;
                                iVar7 = iVar7 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar1);
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.field248_0x109250 = 4;
                } else {
                    do {
                        iVar7 = 0;
                        iVar3 = 0;
                        if (iVar1 < 1)
                            break;
                        do {
                            iVar4 = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1];
                            if (DAT_GameSynchronyState::instance
                                    .mapBalanceArray[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3]]
                                < DAT_GameSynchronyState::instance.mapBalanceArray[iVar4]) {
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3 + -1]
                                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3];
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar3] = iVar4;
                                iVar7 = iVar7 + 1;
                            }
                            iVar3 = iVar3 + 1;
                        } while (iVar3 < iVar1);
                    } while (iVar7 != 0);
                    DAT_GameSynchronyState::instance.field248_0x109250 = 3;
                }
            }
            if (-1 < iVar8) {
                INT_00b95ab8::instance = 1;
                MACRO_CALL(OpenSHC::UI::MenuItems::LobbyMenu_Func::MenuItemActionHandler_LobbyMenu_MapSelectTable)(
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
            }
            iVar8 = 0;
            if (0 < iVar2) {
                while (true) {
                    _Str2 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[iVar8 + -1]);
                    iVar2 = MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                        DAT_MapNameCache::instance, (char const*)((int)(_Str2)));
                    if (iVar2 == 0)
                        break;
                    iVar8 = iVar8 + 1;
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber <= iVar8) {}
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = 0;
                if (iVar8 < 0) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar8;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 0;
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = iVar8;
                if (7 < iVar8) {
                    DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = iVar8 + -7;
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = 7;
                }
            }
        }

    }
}
}
