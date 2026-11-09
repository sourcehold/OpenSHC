#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B6530
        void InGameMenu::MenuItemActionHandler_InGameMenu_MapEventIconUnk(int unused, ...)
        {
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate, DAT_ViewportRenderState::ptr)(
                DAT_MinimapViewState::instance.spawnMomentX[0], DAT_MinimapViewState::instance.spawnMomentY[0]);
            for (int eventIndex = 1; eventIndex < DAT_MinimapViewState::instance.spawnMomentCount; ++eventIndex) {
                DAT_MinimapViewState::instance.spawnMomentX[eventIndex - 1]
                    = DAT_MinimapViewState::instance.spawnMomentX[eventIndex];
                DAT_MinimapViewState::instance.spawnMomentY[eventIndex - 1]
                    = DAT_MinimapViewState::instance.spawnMomentY[eventIndex];
                DAT_MinimapViewState::instance.spawnMoment[eventIndex - 1]
                    = DAT_MinimapViewState::instance.spawnMoment[eventIndex];
            }
            --DAT_MinimapViewState::instance.spawnMomentCount;
        }

    }
}
}
