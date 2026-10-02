#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B6530
        void InGameMenu::MenuItemActionHandler_InGameMenu_MapEventIconUnk(int param_1, ...)
        {
            int iVar1;
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                DAT_ViewportRenderState::ptr)(DAT_MinimapViewState::instance.spawnMomentX[0],
                (int)((int)(DAT_MinimapViewState::instance.spawnMomentY[0])));
            iVar1 = 1;
            if (1 < DAT_MinimapViewState::instance.spawnMomentCount) {
                do {
                    DAT_MinimapViewState::instance.spawnMomentX[iVar1 + -1]
                        = DAT_MinimapViewState::instance.spawnMomentX[iVar1];
                    DAT_MinimapViewState::instance.spawnMomentX[iVar1 + 0x13]
                        = DAT_MinimapViewState::instance.spawnMomentY[iVar1];
                    DAT_MinimapViewState::instance.spawnMomentY[iVar1 + 0x13]
                        = DAT_MinimapViewState::instance.spawnMoment[iVar1];
                    iVar1 = iVar1 + 1;
                } while (iVar1 < DAT_MinimapViewState::instance.spawnMomentCount);
            }
            DAT_MinimapViewState::instance.spawnMomentCount = DAT_MinimapViewState::instance.spawnMomentCount + -1;
        }

    }
}
}
