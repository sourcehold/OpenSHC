#include "../EditScenario.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8080
        void EditScenario::MenuView_EditScenario_DoEveryFrame()
        {
            // the background, centred
            DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8
                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                // "Scenario Editor"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 2, DAT_MenuHandlerState::instance.x,
                    DAT_MenuHandlerState::instance.y, 800, 60);
                // the map surface, set before the corners are worked out (after them: quick_diff 0.9920 -> 0.9840)
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                // the list box: dimmed and framed in yellow, with a 20 pixel strip on its right for the scroll buttons
                int const left = DAT_MenuHandlerState::instance.x + 270;
                int const top = DAT_MenuHandlerState::instance.y + 90;
                int const right = DAT_MenuHandlerState::instance.x + 770;
                int const bottom = DAT_MenuHandlerState::instance.y + 489;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom);
                int const frameRight = right + 1;
                int const frameLeft = left - 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, top - 1, frameRight, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, bottom + 1, frameRight, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top + 20, frameRight, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameLeft, top, frameLeft, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    frameRight, top, frameRight, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 19, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }
        }

    }
}
}
