#include "../Helpers.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00427180
    void Helpers::MainMenu_Unknown21_Prepare()
    {
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        // "frontend_combat3.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_frontend_combat3_tgx_005a2134);
        MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
        int const top = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        int const left = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
        menu->xPosition = left;
        menu->yPosition = top;
        DAT_MenuHandlerState::instance.x = left;
        DAT_MenuHandlerState::instance.y = top;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_UNKNOWN_20, FALSE);
    }

}
}
