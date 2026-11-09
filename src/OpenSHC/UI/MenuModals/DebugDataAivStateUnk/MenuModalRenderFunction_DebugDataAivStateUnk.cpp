#include "../DebugDataAivStateUnk.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AIVPlacementFit.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF4C0
        void DebugDataAivStateUnk::MenuModalRenderFunction_DebugDataAivStateUnk(int x, int y, int width, int height)
        {
            x += 20;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_Village_Placement_Success_005a7760, x, y + 10, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 18, FALSE, 0);
            y += 20;
            int aivIndex = 1;
            do {
                y += 20;
                if (DAT_AIVPlacementFit::instance[aivIndex] != -10) {
                    uint color = DAT_AIVPlacementFit::instance[aivIndex] != 100 ? 0xff : 0xc2f0eb;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        aivIndex, x, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
                    int integer = DAT_AIVPlacementFit::instance[aivIndex];
                    if (integer == -3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            s_File_missing_005a7750, x + 20, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
                    } else if (integer == -2) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            s_Can_t_place_keep_005a773c, x + 20, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
                    } else if (integer == 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            s_Total_Success_005a772c, x + 20, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            integer, x + 20, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            s___Success_005a7720, x + 20, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, TRUE, 0);
                    }
                }
                ++aivIndex;
            } while (aivIndex < 9);
        }

    }
}
}
