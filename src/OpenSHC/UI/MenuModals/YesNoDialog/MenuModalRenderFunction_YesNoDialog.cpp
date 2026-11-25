#include "../YesNoDialog.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/UI_MissionModeIntent.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x00493390
        void YesNoDialog::MenuModalRenderFunction_YesNoDialog(int x, int y, int width, int height)
        {
            int bannerTextIndex = -1;
            UI_MissionModeIntent::instance = FALSE;
            switch ((int)DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter) {
            case -7:
                bannerTextIndex = -DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter;
                break;
            // the asking button's TEXT_GAME_OPTIONS text: 7 "Quit Mission", 9 "Exit Crusader", 44 "Restart Mission"
            case 7:
            case 9:
            case 30:
            case 43:
            case 44:
            case 47:
            case 49:
                bannerTextIndex = DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter;
                break;
            case 1000:
                bannerTextIndex = 7;
                UI_MissionModeIntent::instance = TRUE;
                break;
            }
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                    DAT_PencilRenderCore::ptr)(x, y, width, height);
                // "Receiving Map"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 107),
                    width / 2 + x, y + 15, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.unknownMapName_01, width / 2 + x, y + 42,
                    OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
            } else if (bannerTextIndex != -1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, bannerTextIndex, x, y, width, height);
            }
            DAT_MenuHandlerState::instance.currentMenu->zero = 0;
        }

    }
}
}
