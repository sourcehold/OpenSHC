#include "../YesNoDialog.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/UI_MissionModeIntent.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00493390
        void YesNoDialog::MenuModalRenderFunction_YesNoDialog(int x, int y, int width, int height)
        {
            int bannerTextIndex = -1;
            UI_MissionModeIntent::instance = FALSE;
            switch (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter) {
            case -7:
                bannerTextIndex = -DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter;
                break;
            case 7:
            case 9:
            case 0x1e:
            case 0x2b:
            case 0x2c:
            case 0x2f:
            case 0x31:
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
                /*
                  added by script: "Receiving Map"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x6b),
                    width / 2 + x, y + 0xf, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x11, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.unknownMapName_01, width / 2 + x, y + 0x2a, OpenSHC::Text::TTA_CENTER,
                    0xc2f0eb, 0x11, FALSE, 0);
                (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
                return;
            }
            if (bannerTextIndex != -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, bannerTextIndex, x, y, width, height);
                (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
                return;
            }
            (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
        }
    }
}
}
