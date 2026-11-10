#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Colors::BGR24;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AA970
        void Unused::MenuItemRenderFunction_UnusedWinCondition_Options(int value, ...)
        {
            // only the dialog's options, as its handler does
            if (value >= (int)DAT_MenuModalComposition1::instance.mbr_0x64) {
                return;
            }
            // set in each branch (a default overridden when hovered: quick_diff 0.9531 -> 0.9449)
            BGR24 color;
            // the black box in each branch, which MSVC merges (one after the if: quick_diff 0.9531 -> 0.8906)
            if (DAT_ButtonCurrentlyInteracting::instance) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    COL_GREYISH_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance, 12);
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance, 12);
            }
            // x as a local, y in the call (both as locals: quick_diff 0.9531 -> 0.8906; neither: 0.8281)
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (OpenSHC::DE::SHCDE::eTextSections)DAT_MenuModalComposition1::instance.textGroup,
                    DAT_MenuModalComposition1::instance.textIndex + value),
                textX, DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, color, 19, FALSE, 0);
        }

    }
}
}
