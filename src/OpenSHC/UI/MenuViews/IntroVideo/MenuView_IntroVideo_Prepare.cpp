#include "../IntroVideo.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/TIME_IntroVideo_Prepare.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424A50
        void IntroVideo::MenuView_IntroVideo_Prepare()
        {
            Menu* pMVar1;
            int borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = borderWidth;
            pMVar1->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(0,
                "intro.bik", 0, 0, DAT_MenuHandlerState::instance.x + 0x50, DAT_MenuHandlerState::instance.y + 0x3c, 0);
            TIME_IntroVideo_Prepare::instance = timeGetTime();
        }

    }
}
}
