#include "../UnusedSetName.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004266E0
        void UnusedSetName::MenuModalRenderFunction_UnusedSetName(int x, int y, int width, int height)
        {
            // a 400 pixel wide title box in the middle of the dialog
            int const margin = (width - 400) / 2;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                margin + x, y + 10, x - margin + width, y + 60, OpenSHC::UI::Enums::RBERL_STRONG);
            // "Enter Your Title"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 6),
                width / 2 + x, y + 15, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 15, FALSE, 0);
        }

    }
}
}
