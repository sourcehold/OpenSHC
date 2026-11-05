#include "../OnlineVoteQuitAndQuitGame.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00493850
        void OnlineVoteQuitAndQuitGame::MenuItemRenderFunction_OnlineVoteQuitAndQuitGame_Main(int buttonID, ...)
        {
            eTextSections section = OpenSHC::DE::SHCDE::TEXT_UNKNOWN_0;
            int textIndex = 0;
            switch (buttonID) {
            case 1:
                // "Quit Game"
                section = OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS;
                textIndex = 8;
                break;
            case 2:
            case 4:
                // "End this game?"
                section = OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION;
                textIndex = 59;
                break;
            case 3:
            case 5:
                // "Cancel"
                section = OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION;
                textIndex = 3;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            int const textY = DAT_ButtonY::instance + 7;
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(section, textIndex),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 4);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(section, textIndex),
                textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 2);
        }

    }
}
}
