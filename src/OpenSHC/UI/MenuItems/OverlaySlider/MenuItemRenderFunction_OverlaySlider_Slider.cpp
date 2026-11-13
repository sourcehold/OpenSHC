#include "../OverlaySlider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AA800
        void OverlaySlider::MenuItemRenderFunction_OverlaySlider_Slider(
            int slider, int thumbYPos, int value, int thumbHeight, BOOL isDragged)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                DAT_ButtonX::instance + DAT_ButtonW::instance, DAT_ButtonY::instance + DAT_ButtonH::instance, 12);
            // the slider's title, drawn under the thumb
            if (DAT_MenuModalComposition2::instance.textGroup >= 0) {
                // the title's position in locals, y first, as the original reads it
                int const textY = DAT_ButtonY::instance + 4;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition2::instance.textGroup,
                        DAT_MenuModalComposition2::instance.textIndex),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE, 0);
            }
            if (!isDragged) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + thumbYPos, DAT_ButtonY::instance,
                    DAT_ButtonX::instance + thumbYPos + thumbHeight, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    COL_GREYISH_YELLOW::instance.shortValue);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + thumbYPos, DAT_ButtonY::instance,
                    DAT_ButtonX::instance + thumbYPos + thumbHeight, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    COL_DARK_LIME::instance.shortValue);
            }
            // a thumb as wide as the slider covers the title, so it is drawn again over it
            if (thumbHeight == DAT_ButtonW::instance && DAT_MenuModalComposition2::instance.textGroup >= 0) {
                // the title's position in locals, y first, as the original reads it
                int const textY = DAT_ButtonY::instance + 4;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition2::instance.textGroup,
                        DAT_MenuModalComposition2::instance.textIndex),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
            }
        }

    }
}
}
