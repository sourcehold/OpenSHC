#include "../Chat.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::Text::TextArrayIndexType;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABD20
        void Chat::MenuModalRenderFunction_Chat(int x, int y, int width, int height)
        {
            int iVar5 = 0;
            BOOLEnum BVar4 = FALSE;
            BGR24 BVar3 = 0xccfaff;
            TextAlignment TVar2 = OpenSHC::Text::TTA_LEFT;
            int _yOff = y + 0x19;
            int _xOff = x + 0x14;
            /*
              "Chat"   added by script: "Chat"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x1e),
                _xOff, _yOff, TVar2, BVar3, (int)(0xf), BVar4, iVar5);
            iVar5 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                x + 0x14, y + 0xbf, x + -0x14a + width, y + 0xd8, OpenSHC::UI::Enums::RBERL_SLIGHT);
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(x + 0x19 + iVar5, y + 0xc1, x + 0x1a + iVar5, y + 0xd5,
                    (ushort)(COL_DARK_LIME::instance.shortValue));
            }
            if (DAT_UserTextHandlerState::instance.textArrayIndex != (TextArrayIndexType)4) {
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    4);
            }
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex != 0) {
                int fontSize = (int)MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_INSULTS, (int)(DAT_GameSynchronyState::instance.DAT_InsultTextIndex)),
                    x + 0x19, y + 199, OpenSHC::Text::TTA_LEFT, 0xccfaff, fontSize, FALSE, 0);
            } else {
                int fontSize = (int)MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                char* const currentText = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    currentText, x + 0x19, y + 199, OpenSHC::Text::TTA_LEFT, 0xccfaff, fontSize, FALSE, 0);
            }
            DAT_GameSynchronyState::instance.DAT_InsultTextIndex = 0;
        }

    }
}
}
