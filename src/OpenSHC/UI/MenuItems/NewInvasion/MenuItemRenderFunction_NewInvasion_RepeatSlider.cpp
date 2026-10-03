#include "../NewInvasion.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004B9530
        void NewInvasion::MenuItemRenderFunction_NewInvasion_RepeatSlider(
            int param_1, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged)
        {
            undefined2 color;
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color_00;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            color = COL_GREYISH_YELLOW::instance.shortValue;
            if (isDragged != FALSE) {
                color = COL_DARK_LIME::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                thumbXPos + DAT_ButtonX::instance + 1, (int)((int)(DAT_ButtonY::instance + 2)),
                thumbXPos + DAT_ButtonX::instance + -2 + thumbWidth,
                (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)), (ushort)((int)(color)));
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                sliderValue, (int)((int)(DAT_ButtonW::instance + 0x14 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            color_00 = 0xccfaff;
            alignment = OpenSHC::Text::TTA_LEFT;
            yParam = DAT_ButtonY::instance + 6;
            xParam = DAT_ButtonX::instance + -0x96;
            /*
              added by script: "Repeat"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xa3),
                xParam, yParam, alignment, color_00, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
