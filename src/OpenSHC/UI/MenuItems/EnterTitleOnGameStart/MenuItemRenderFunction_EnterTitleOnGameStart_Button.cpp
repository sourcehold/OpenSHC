#include "../EnterTitleOnGameStart.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491C50
        void EnterTitleOnGameStart::MenuItemRenderFunction_EnterTitleOnGameStart_Button(int param_1, ...)
        {
            int xParam;
            char* pcVar1;
            int yParam;
            TextAlignment TVar2;
            uint foregroundColor;
            BGR24 color;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            blendStrength = 0;
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            yParam = DAT_ButtonY::instance + 7;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                color = 0xc2f0eb;
                TVar2 = OpenSHC::Text::TTA_CENTER;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, param_1),
                    xParam, yParam, TVar2, color, fontSize, keepOffsetX, blendStrength);
            }
            backgroundColor = 0;
            foregroundColor = 0xccfaff;
            TVar2 = OpenSHC::Text::TTA_CENTER;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, param_1),
                xParam, yParam, TVar2, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
