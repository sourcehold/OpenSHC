#include "../OnlineVoteQuitAndQuitGame.func.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00493850
        void OnlineVoteQuitAndQuitGame::MenuItemRenderFunction_OnlineVoteQuitAndQuitGame_Main(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            eTextSections offsetIndex;
            int numInGroup;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            offsetIndex = ((eTextSections)0);
            numInGroup = 0;
            switch (param_1) {
            case 1:
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS;
                numInGroup = 8;
                goto switchD_00493862_caseD_5;
            case 2:
            case 4:
                numInGroup = 0x3b;
                break;
            case 3:
            case 5:
                numInGroup = 3;
                break;
            default:
                goto switchD_00493862_caseD_5;
            }
            offsetIndex = OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION;
        switchD_00493862_caseD_5:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            yParam = DAT_ButtonY::instance + 7;
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                blendStrength = 4;
                color = 0xc2f0eb;
            } else {
                blendStrength = 2;
                color = 0xccfaff;
            }
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(offsetIndex, numInGroup),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
