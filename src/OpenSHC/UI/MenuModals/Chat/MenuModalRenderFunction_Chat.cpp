#include "../Chat.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABD20
        void Chat::MenuModalRenderFunction_Chat(int x, int y, int width, int height)
        {
            int const titleY = y + 25;
            int const titleX = x + 20;
            // "Chat"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 30),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 15, FALSE, 0);
            int const cursorX = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(x + 20, y + 191, x - 330 + width, y + 216, OpenSHC::UI::Enums::RBERL_SLIGHT);
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex == 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                    x + 25 + cursorX, y + 193, x + 26 + cursorX, y + 213, COL_DARK_LIME::instance.shortValue);
            }
            if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_UNKNOWN_4) {
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_UNKNOWN_4);
            }
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex != 0) {
                int fontSize = (int)MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_INSULTS, DAT_GameSynchronyState::instance.DAT_InsultTextIndex),
                    x + 25, y + 199, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, fontSize, FALSE,
                    0);
            } else {
                int fontSize = (int)MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                char* const currentText = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    currentText, x + 25, y + 199, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF,
                    fontSize, FALSE, 0);
            }
            DAT_GameSynchronyState::instance.DAT_InsultTextIndex = 0;
        }

    }
}
}
