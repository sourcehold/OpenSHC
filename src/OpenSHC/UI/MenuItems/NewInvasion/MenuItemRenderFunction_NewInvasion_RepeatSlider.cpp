#include "../NewInvasion.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9530
        void NewInvasion::MenuItemRenderFunction_NewInvasion_RepeatSlider(
            int unused, int thumbXPos, int sliderValue, int thumbWidth, BOOLEnum isDragged)
        {
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            // -1: the plain tiled button (the slider's track)
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            // the thumb, in another colour while dragged: x and y before the colour; in the call they lose the match
            int const thumbX = thumbXPos + DAT_ButtonX::instance;
            int const buttonY = DAT_ButtonY::instance;
            ushort color = COL_GREYISH_YELLOW::instance.shortValue;
            if (isDragged) {
                color = COL_DARK_LIME::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                thumbX + 1, buttonY + 2, thumbX + thumbWidth - 2, buttonY + DAT_ButtonH::instance - 4, color);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(sliderValue,
                DAT_ButtonW::instance + DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 6, Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            // y before x: x first, or both written in the call, loses the match
            int const labelY = DAT_ButtonY::instance + 6;
            int const labelX = DAT_ButtonX::instance - 150;
            // "Repeat"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_SCENARIO, 163),
                labelX, labelY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
        }

    }
}
}
