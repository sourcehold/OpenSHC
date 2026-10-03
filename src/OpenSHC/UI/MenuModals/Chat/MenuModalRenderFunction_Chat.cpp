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

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004ABD20
        void Chat::MenuModalRenderFunction_Chat(int x, int y, int width, int height)
        {
            char* pcVar1;
            uint _fontSize_2;
            int xParam;
            TextAlignment TVar2;
            BGR24 BVar3;
            BOOLEnum BVar4;
            int iVar5;
            int blendStrength;
            int _yOff;
            int _xOff;
            uint _fontSize;
            undefined* _color;
            iVar5 = 0;
            BVar4 = FALSE;
            _fontSize = 0xf;
            BVar3 = 0xccfaff;
            TVar2 = OpenSHC::Text::TTA_LEFT;
            _yOff = y + 0x19;
            _xOff = x + 0x14;
            /*
              "Chat"   added by script: "Chat"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x1e),
                _xOff, _yOff, TVar2, BVar3, (int)((int)(_fontSize)), BVar4, iVar5);
            iVar5 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                x + 0x14, y + 0xbf, x + -0x14a + width, y + 0xd8, OpenSHC::UI::Enums::RBERL_SLIGHT);
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(x + 0x19 + iVar5, y + 0xc1, x + 0x1a + iVar5, y + 0xd5,
                    (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
            }
            if (DAT_UserTextHandlerState::instance.textArrayIndex != ((TextArrayIndexType)4)) {
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    4);
            }
            if (DAT_GameSynchronyState::instance.DAT_InsultTextIndex == 0) {
                _fontSize_2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                pcVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                blendStrength = 0;
                BVar4 = FALSE;
                BVar3 = 0xccfaff;
                TVar2 = OpenSHC::Text::TTA_LEFT;
                iVar5 = y + 199;
                xParam = x + 0x19;
            } else {
                _fontSize_2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getCurrentFontSize, DAT_UserTextHandlerState::ptr)();
                blendStrength = 0;
                BVar4 = FALSE;
                BVar3 = 0xccfaff;
                TVar2 = OpenSHC::Text::TTA_LEFT;
                iVar5 = y + 199;
                xParam = x + 0x19;
                pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_INSULTS,
                    (int)((int)(DAT_GameSynchronyState::instance.DAT_InsultTextIndex)));
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar1, xParam, iVar5, TVar2, BVar3, (int)((int)(_fontSize_2)), BVar4, blendStrength);
            DAT_GameSynchronyState::instance.DAT_InsultTextIndex = 0;
        }

    }
}
}
