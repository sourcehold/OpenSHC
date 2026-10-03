#include "../AiLordSelect.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B19E0
        void AiLordSelect::MenuModalRenderFunction_AiLordSelect(int x, int y, int width, int height)
        {
            int _textAddress;
            char* text;
            int yPos;
            int maxWidth;
            BGR24 color;
            int iVar1;
            uint color_00;
            BOOLEnum keepOffsetX;
            int fontSize;
            int iVar2;
            int blendStrength;
            int _xParam;
            int _yParam;
            uint _shift;
            undefined* _color;
            uint _fontSize;
            yPos = y + 0x6e;
            if (DAT_GameCore::instance.numOfAIsWithCastleUnk < 9) {
                iVar1 = 0x13;
            } else {
                iVar1 = 0x14;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(iVar1, x, y);
            if (8 < DAT_GameCore::instance.numOfAIsWithCastleUnk) {
                yPos = yPos + 0x4c;
            }
            if (DAT_MouseState::instance.rightClickStart != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            }
            iVar1 = x + 0x18;
            iVar2 = 0;
            if (DAT_LobbyAddAICurrentlyHoveredAI::instance == 0) {
                maxWidth = 450;
                iVar2 = 401;
            } else {
                keepOffsetX = FALSE;
                _fontSize = 0x11;
                color = 0xccfaff;
                _shift = 0;
                _xParam = iVar1;
                _yParam = yPos;
                _textAddress = (int)MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)((int)(DAT_LobbyAddAICurrentlyHoveredAI::instance * 9 + 0xe6)));
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)_textAddress, _xParam, _yParam, (TextAlignment)((int)(_shift)), color,
                    (int)((int)(_fontSize)), keepOffsetX, iVar2);
                iVar2 = DAT_LobbyAddAICurrentlyHoveredAI::instance + 384;
                maxWidth = 0x236;
                yPos = yPos + 0x1e;
            }
            blendStrength = 0;
            fontSize = 0x12;
            color_00 = 0xccfaff;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar2),
                iVar1, yPos, maxWidth, color_00, fontSize, blendStrength);
        }

    }
}
}
