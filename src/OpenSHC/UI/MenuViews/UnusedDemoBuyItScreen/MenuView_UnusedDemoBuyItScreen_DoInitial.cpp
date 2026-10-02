#include "../UnusedDemoBuyItScreen.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960e0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Rendering::ScreenResolutionEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00426600
        void UnusedDemoBuyItScreen::MenuView_UnusedDemoBuyItScreen_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            bool bVar3;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar2 = 0;
            INT_00b960e0::instance = 0;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                iVar2 = 0x18;
                INT_00b960e0::instance = 0x18;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2
                    + iVar2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            bVar3 = DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600;
            (DAT_MenuHandlerState::instance.currentMenu)->yPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            if (bVar3) {
                DAT_MenuHandlerState::instance.x = DAT_MenuHandlerState::instance.x + 0x18;
            }
            pMVar1->xPosition = DAT_MenuHandlerState::instance.x;
            return;
        }

    }
}
}
