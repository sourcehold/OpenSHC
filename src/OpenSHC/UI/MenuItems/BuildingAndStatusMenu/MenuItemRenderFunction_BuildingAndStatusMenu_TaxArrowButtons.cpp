#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004657B0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_TaxArrowButtons(int param_1, ...)
        {
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            if (-1 < param_1) {
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                color = 0;
                alignment = OpenSHC::Text::TTA_CENTER;
                yParam = DAT_ButtonY::instance + 4;
                int xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_KEEP, param_1),
                    xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
