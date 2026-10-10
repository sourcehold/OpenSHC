#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B6530
        void InGameMenu::MenuItemActionHandler_InGameMenu_MapEventIconUnk(int param_1, ...)
        {
            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate, DAT_ViewportRenderState::ptr)(
                DAT_MinimapViewState::instance.spawnMomentX[0], (int)(DAT_MinimapViewState::instance.spawnMomentY[0]));
            int iVar1 = 1;
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
