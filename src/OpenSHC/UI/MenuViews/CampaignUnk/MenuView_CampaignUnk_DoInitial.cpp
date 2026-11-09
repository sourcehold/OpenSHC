#include "../CampaignUnk.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD0C0
        void CampaignUnk::MenuView_CampaignUnk_DoInitial()
        {
            Menu* pMVar1;
            int borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = borderWidth;
            pMVar1->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            MACRO_CALL(UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
            MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
        }

    }
}
}
