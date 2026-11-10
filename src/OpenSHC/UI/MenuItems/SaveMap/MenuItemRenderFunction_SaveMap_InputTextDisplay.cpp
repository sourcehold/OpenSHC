#include "../SaveMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004932E0
        void SaveMap::MenuItemRenderFunction_SaveMap_InputTextDisplay(int unused, ...)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                OpenSHC::UI::Enums::RBERL_SLIGHT);
            // the cursor: a one-pixel line after the text typed so far
            int const cursorOffset = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance + 6 + cursorOffset, DAT_ButtonY::instance + 2,
                DAT_ButtonX::instance + 7 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                COL_DARK_LIME::instance.shortValue);
            // y, x, then the text, all before the call: x first, or all of them in the call, loses the match
            int const textY = DAT_ButtonY::instance + 7;
            int const textX = DAT_ButtonX::instance + 8;
            char* const text = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 18, FALSE, 0);
        }

    }
}
}
