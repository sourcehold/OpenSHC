#include "../DebugDataAivStateUnk.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVPlacementFit.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF4C0
        void DebugDataAivStateUnk::MenuModalRenderFunction_DebugDataAivStateUnk(int x, int y, int width, int height)
        {
            x = x + 0x14;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Village Placement Success", x, y + 10, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, FALSE, 0);
            y = y + 0x14;
            int aivIndex = 1;
            do {
                y = y + 0x14;
                if (DAT_AIVPlacementFit::instance[aivIndex] != -10) {
                    uint color = DAT_AIVPlacementFit::instance[aivIndex] != 100 ? 0xff : 0xc2f0eb;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        aivIndex, x, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    int integer = DAT_AIVPlacementFit::instance[aivIndex];
                    if (integer == -3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "File missing", x + 0x14, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else if (integer == -2) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "Can\'t place keep", x + 0x14, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else if (integer == 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "Total Success", x + 0x14, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            integer, x + 0x14, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "% Success", x + 0x14, y, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, TRUE, 0);
                    }
                }
                aivIndex = aivIndex + 1;
            } while (aivIndex < 9);
        }

    }
}
}
