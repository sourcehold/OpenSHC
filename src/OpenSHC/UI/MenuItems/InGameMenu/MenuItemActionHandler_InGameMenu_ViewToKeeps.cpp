#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b9840c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DWORD_00b98410.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004335A0
        void InGameMenu::MenuItemActionHandler_InGameMenu_ViewToKeeps(int param_1, ...)
        {
            int iVar1;
            DWORD DVar2;
            int iVar3;
            int* piVar5;
            int iVar4;
            dword dVar5;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                DVar2 = timeGetTime();
                if (1000 < DVar2 - DWORD_00b98410::instance) {
                    DAT_00b9840c::instance = 0;
                    DWORD_00b98410::instance = DVar2;
                }
                if (DAT_MouseState::instance.scrollEventData == 7) {
                    if (DAT_00b9840c::instance < 0) {
                        DAT_00b9840c::instance = 0;
                    }
                    if (DAT_00b9840c::instance + 1 != 2) {
                        DAT_00b9840c::instance = DAT_00b9840c::instance + 1;
                    }
                    DAT_00b9840c::instance = 0;
                    dVar5 = 1;
                    iVar4 = -1;
                    piVar5 = DAT_GameState::instance.mapAndTime.field22_0x58[0] + 1;
                    iVar3 = 2;
                    do {
                        if (-1 < piVar5[-1]) {
                            if (dVar5 == DAT_GameCore::instance.field29_0x80) {
                                iVar4 = iVar3 + -2;
                            }
                            dVar5 = dVar5 + 1;
                        }
                        if (-1 < *piVar5) {
                            if (dVar5 == DAT_GameCore::instance.field29_0x80) {
                                iVar4 = iVar3 + -1;
                            }
                            dVar5 = dVar5 + 1;
                        }
                        if (-1 < piVar5[1]) {
                            if (dVar5 == DAT_GameCore::instance.field29_0x80) {
                                iVar4 = iVar3;
                            }
                            dVar5 = dVar5 + 1;
                        }
                        if (-1 < piVar5[2]) {
                            if (dVar5 == DAT_GameCore::instance.field29_0x80) {
                                iVar4 = iVar3 + 1;
                            }
                            dVar5 = dVar5 + 1;
                        }
                        if (-1 < piVar5[3]) {
                            if (dVar5 == DAT_GameCore::instance.field29_0x80) {
                                iVar4 = iVar3 + 2;
                            }
                            dVar5 = dVar5 + 1;
                        }
                        iVar1 = iVar3 + 3;
                        piVar5 = piVar5 + 5;
                        iVar3 = iVar3 + 5;
                    } while (iVar1 < 10);
                    if (iVar4 == -1) {
                        iVar4 = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .keep.id;
                        DWORD_00b98410::instance = DVar2;
                        if (iVar4 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(
                                (short)DAT_BuildingsState::instance.buildings[iVar4].x + 2,
                                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar4].y + 2)));
                        }
                    } else {
                        DWORD_00b98410::instance = DVar2;
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnTile,
                            DAT_ViewportRenderState::ptr)(DAT_GameState::instance.mapAndTime.field22_0x58[0][iVar4]);
                    }
                    DAT_GameCore::instance.field29_0x80 = DAT_GameCore::instance.field29_0x80 + 1;
                    if ((int)dVar5 <= (int)DAT_GameCore::instance.field29_0x80) {
                        DAT_GameCore::instance.field29_0x80 = 0;
                    }
                }
                if (DAT_MouseState::instance.scrollEventData == 8) {
                    if (0 < DAT_00b9840c::instance) {
                        DAT_00b9840c::instance = 0;
                    }
                    DAT_00b9840c::instance = DAT_00b9840c::instance + -1;
                    if (DAT_00b9840c::instance == -2) {
                        iVar4 = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .keep.id;
                        DAT_00b9840c::instance = 0;
                        DWORD_00b98410::instance = DVar2;
                        if (iVar4 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(
                                (short)DAT_BuildingsState::instance.buildings[iVar4].x + 2,
                                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar4].y + 2)));
                        }
                    }
                }
            }
        }

    }
}
}
