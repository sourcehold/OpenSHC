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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042DEB0
        void Unused::MenuItemRenderFunction_UnusedOldTitleMenu_ContinueButton(int param_1, ...)
        {
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                DAT_TextManagerObject::instance.textColor = 0;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
            } else {
                DAT_TextManagerObject::instance.textColor = 0xff;
                DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                DAT_PencilRenderCore::instance.otherColorUnk_0x0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Continue", (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance + 6)),
                (TextAlignment)((int)(DAT_ButtonW::instance)),
                (BGR24)((int)(DAT_TextManagerObject::instance.textColor)), 0x11, FALSE, 0);
        }

    }
}
}
