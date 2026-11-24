#include "../CreditsScroll.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AAB50
        void CreditsScroll::MenuModalRenderFunction_CreditsScroll(int x, int y, int width, int height)
        {
            if (!DAT_TextEditorState::instance.pendingCreditsFadeBorder) {
                return;
            }
            DAT_TextEditorState::instance.pendingCreditsFadeBorder = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
            // one row counter for both edges (with a counter of its own in each loop, the match is lost)
            int row;
            // the top edge fades to black over 30 rows of four pixels, and each row over its 20 leftmost columns
            for (row = 0; row < 30; ++row) {
                int const rowY = y + row * 4;
                // every column is its own call, and the first one divides the other way round (a loop over the
                // columns, or the first column in the others' form, loses the match)
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x, rowY, x, rowY + 3, 32 - (30 - row) / 20);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 1, rowY, x + 1, rowY + 3, (row - 30) * 2 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 2, rowY, x + 2, rowY + 3, (row - 30) * 3 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 3, rowY, x + 3, rowY + 3, (row - 30) * 4 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 4, rowY, x + 4, rowY + 3, (row - 30) * 5 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 5, rowY, x + 5, rowY + 3, (row - 30) * 6 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 6, rowY, x + 6, rowY + 3, (row - 30) * 7 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 7, rowY, x + 7, rowY + 3, (row - 30) * 8 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 8, rowY, x + 8, rowY + 3, (row - 30) * 9 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 9, rowY, x + 9, rowY + 3, (row - 30) * 10 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 10, rowY, x + 10, rowY + 3, (row - 30) * 11 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 11, rowY, x + 11, rowY + 3, (row - 30) * 12 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 12, rowY, x + 12, rowY + 3, (row - 30) * 13 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 13, rowY, x + 13, rowY + 3, (row - 30) * 14 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 14, rowY, x + 14, rowY + 3, (row - 30) * 15 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 15, rowY, x + 15, rowY + 3, (row - 30) * 16 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 16, rowY, x + 16, rowY + 3, (row - 30) * 17 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 17, rowY, x + 17, rowY + 3, (row - 30) * 18 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 18, rowY, x + 18, rowY + 3, (row - 30) * 19 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 19, rowY, x + 19, rowY + 3, (row - 30) * 20 / 20 + 32);
                // the rest of the row, one step darker per row
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 20, rowY, x + width - 1, rowY + 3, row + 2);
            }
            // the bottom edge, the same from the bottom up
            for (row = 0; row < 30; ++row) {
                int const rowY = y + height - row * 4;
                // (written out for the same reason as above)
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x, rowY, x, rowY + 3, 32 - (30 - row) / 20);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 1, rowY, x + 1, rowY + 3, (row - 30) * 2 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 2, rowY, x + 2, rowY + 3, (row - 30) * 3 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 3, rowY, x + 3, rowY + 3, (row - 30) * 4 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 4, rowY, x + 4, rowY + 3, (row - 30) * 5 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 5, rowY, x + 5, rowY + 3, (row - 30) * 6 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 6, rowY, x + 6, rowY + 3, (row - 30) * 7 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 7, rowY, x + 7, rowY + 3, (row - 30) * 8 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 8, rowY, x + 8, rowY + 3, (row - 30) * 9 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 9, rowY, x + 9, rowY + 3, (row - 30) * 10 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 10, rowY, x + 10, rowY + 3, (row - 30) * 11 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 11, rowY, x + 11, rowY + 3, (row - 30) * 12 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 12, rowY, x + 12, rowY + 3, (row - 30) * 13 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 13, rowY, x + 13, rowY + 3, (row - 30) * 14 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 14, rowY, x + 14, rowY + 3, (row - 30) * 15 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 15, rowY, x + 15, rowY + 3, (row - 30) * 16 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 16, rowY, x + 16, rowY + 3, (row - 30) * 17 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 17, rowY, x + 17, rowY + 3, (row - 30) * 18 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 18, rowY, x + 18, rowY + 3, (row - 30) * 19 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 19, rowY, x + 19, rowY + 3, (row - 30) * 20 / 20 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 20, rowY, x + width - 1, rowY + 3, row + 2);
            }
        }

    }
}
}
