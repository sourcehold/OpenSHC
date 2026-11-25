#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CEE0
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels(
            int textID, ...)
        {
            // the label's height, so that its last line ends 3 pixels above the button's bottom edge
            int const textHeight = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, textID),
                0, 0, 400, 0, 0, 1);
            int const textY = DAT_ButtonY::instance + DAT_ButtonH::instance - textHeight - 3;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, textID),
                DAT_ButtonX::instance, textY, 400, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, 0);
        }

    }
}
}
