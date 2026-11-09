#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
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

        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042DEB0
        void Unused::MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton(int param_1, ...)
        {
            // the original jumps out of line on `== FALSE`, so the interacting
            // arm is the one the source wrote first
            if (DAT_ButtonCurrentlyInteracting::instance) {
                DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_0000FF;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
            } else {
                DAT_TextManagerObject::instance.textColor = 0;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                (int)(DAT_ButtonY::instance + DAT_ButtonH::instance), DAT_PencilRenderCore::instance.otherColorUnk_0x0);
            // "Continue"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Continue_005a22d8, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                (TextAlignment)((int)(DAT_ButtonW::instance)),
                (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 17, FALSE, 0);
        }

    }
}
}
