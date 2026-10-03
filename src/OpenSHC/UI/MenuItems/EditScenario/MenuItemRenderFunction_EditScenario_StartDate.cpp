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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
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
                    if (param_1 == 0) {}
                    iVar1 = DAT_ButtonX::instance;
                    if (DAT_ButtonW::instance != 0) {
                        iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1, iVar1, (int)((int)(DAT_ButtonY::instance + 6)),
                        (TextAlignment)((int)((uint)(DAT_ButtonW::instance != 0))), 0xccfaff, 0x12, FALSE);
                }
                iVar1 = 0x20;
            }
            yParam = DAT_ButtonY::instance + 6;
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            color = 0xccfaff;
            alignment = OpenSHC::Text::TTA_CENTER;
            /*
              added by script: "Start Date"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar1),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
