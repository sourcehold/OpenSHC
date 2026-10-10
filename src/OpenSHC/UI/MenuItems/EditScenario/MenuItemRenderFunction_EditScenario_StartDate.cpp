#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eTextSections;
        using Rendering::Colors::BGR24;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BAC90
        void EditScenario::MenuItemRenderFunction_EditScenario_StartDate(int param_1, ...)
        {
            char* textAddress;
            int iVar1;
            int xParam;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == -5) {
                iVar1 = 0x27;
            } else {
                if (param_1 != -1) {
                    if (!param_1) {}
                    iVar1 = DAT_ButtonX::instance;
                    if (DAT_ButtonW::instance) {
                        iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_SCENARIO, param_1, iVar1, (int)(DAT_ButtonY::instance + 6),
                        (TextAlignment)((int)(DAT_ButtonW::instance)), 0xccfaff, 0x12, FALSE);
                }
                iVar1 = 0x20;
            }
            yParam = DAT_ButtonY::instance + 6;
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            color = 0xccfaff;
            alignment = Text::TTA_CENTER;
            /*
              added by script: "Start Date"
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, iVar1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
