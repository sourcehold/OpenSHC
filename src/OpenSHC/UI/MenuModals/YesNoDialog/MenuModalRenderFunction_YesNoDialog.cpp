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

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00493390
        void YesNoDialog::MenuModalRenderFunction_YesNoDialog(int x, int y, int width, int height)
        {
            int xParam;
            int yParam;
            char* textAddress;
            int iVar1;
            int xParam_00;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            iVar1 = -1;
            UI_MissionModeIntent::instance = FALSE;
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter < 0x2d) {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter < 0x2b) {
                    switch (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter) {
                    case 7:
                    case 9:
                    case 0x1e:
                        goto switchD_004933bd_caseD_7;
                    case -7:
                        iVar1 = -DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter;
                    }
                    goto switchD_004933bd_caseD_fffffffa;
                }
            } else if ((DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter != 0x2f)
                && (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter != 0x31)) {
                if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 1000) {
                    iVar1 = 7;
                    UI_MissionModeIntent::instance = TRUE;
                }
                goto switchD_004933bd_caseD_fffffffa;
            }
        switchD_004933bd_caseD_7:
            iVar1 = DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter;
        switchD_004933bd_caseD_fffffffa:
            if (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 2000) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                    DAT_PencilRenderCore::ptr)(x, y, width, height);
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                color = 0xc2f0eb;
                alignment = OpenSHC::Text::TTA_CENTER;
                yParam = y + 0xf;
                xParam = width / 2 + x;
                xParam_00 = xParam;
                /*
                  added by script: "Receiving Map"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x6b),
                    xParam_00, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.unknownMapName_01, xParam, y + 0x2a, OpenSHC::Text::TTA_CENTER,
                    0xc2f0eb, 0x11, FALSE, 0);
                (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
                return;
            }
            if (iVar1 != -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(0x4a, iVar1, x, y, width, height);
                (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
            }
            (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
        }

    }
}
}
