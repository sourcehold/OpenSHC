#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed2bdc.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8DF0
        void General::MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == 1000) {
                INT_00ed2bdc::instance = (int)(DAT_ButtonCurrentlyInteracting::instance != FALSE);
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_SkirmishTrailRelated1::instance, (int)((int)(DAT_ButtonX::instance + 0x35)),
                    (int)((int)(DAT_ButtonY::instance + 0x62)), OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0xf, FALSE, 0);
                if (INT_00ed2bdc::instance != 0) {
                    blendStrength = 0;
                    keepOffsetX = FALSE;
                    fontSize = 0x12;
                    color = 0xccfaff;
                    yParam = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x247;
                    alignment = OpenSHC::Text::TTA_CENTER;
                    xParam = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    /*
                      added by script: "Skip Current Mission"
                     */
                    textAddress = MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_CHEATS, (int)((int)((uint)(DAT_SkirmishTrailRelated1::instance < 1))));
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                }
            } else if (((param_1 == 10) || (param_1 == 0xb)) || (param_1 == 99)) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
        }

    }
}
}
