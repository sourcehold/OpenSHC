#include "../Unknown61ReturnToSkrimishMenuUnk.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004272C0
        void Unknown61ReturnToSkrimishMenuUnk::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame()
        {
            int const borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->yPosition = borderHeight;
            menu->xPosition = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface, DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
        }

    }
}
}
