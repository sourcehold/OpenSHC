#include "../Credits.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004262B0
        void Credits::MenuView_Credits_DoInitial()
        {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0, 0,
                DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                COL_BLACK::instance.shortValue);
            MACRO_CALL(UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface, DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            int const borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = borderWidth;
            menu->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
        }

    }
}
}
