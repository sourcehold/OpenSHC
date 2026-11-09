#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042DF40
        void Unused::MenuItemRenderFunction_UnusedOldTitleMenu_TestMapButton(int param_1, ...)
        {
            /*
              the original jumps out of line on `== FALSE`, so the interacting
              arm is the one the source wrote first
             */
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                DAT_TextManagerObject::instance.textColor = 0xff;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
            } else {
                DAT_TextManagerObject::instance.textColor = 0;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                (int)(DAT_ButtonY::instance + DAT_ButtonH::instance), DAT_PencilRenderCore::instance.otherColorUnk_0x0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Test map", (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                (TextAlignment)((int)(DAT_ButtonW::instance)),
                (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x11, FALSE, 0);
        }

    }
}
}
