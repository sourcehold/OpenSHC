#include "../UnusedOldTitleMenu.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042DCB0
        void UnusedOldTitleMenu::MenuView_UnusedOldTitleMenu_Prepare()
        {
            int borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            pMVar1->yPosition = borderHeight;
            pMVar1->xPosition = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("gm_fly.tgx");
        }

    }
}
}
