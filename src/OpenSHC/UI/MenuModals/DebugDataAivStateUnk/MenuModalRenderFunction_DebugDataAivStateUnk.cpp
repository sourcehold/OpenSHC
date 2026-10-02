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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AF4C0
        void DebugDataAivStateUnk::MenuModalRenderFunction_DebugDataAivStateUnk(int x, int y, int width, int height)
        {
            int integer;
            uint color;
            int _x2;
            int yPosition;
            int _x1;
            _x1 = x;
            _x2 = x + 0x14;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Village Placement Success", _x2, y + 10, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0, 0x12, FALSE, 0);
            yPosition = y + 0x14;
            x = 1;
            do {
                yPosition = yPosition + 0x14;
                if (DAT_AIVPlacementFit::instance[x] != -10) {
                    color = (-(uint)(DAT_AIVPlacementFit::instance[x] != 100) & 0xff3d1014) + 0xc2f0eb;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        x, _x2, yPosition, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    integer = DAT_AIVPlacementFit::instance[x];
                    if (integer == -3) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "File missing", _x1 + 0x28, yPosition, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else if (integer == -2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                            DAT_TextManagerObject::ptr)("Can\'t place keep", _x1 + 0x28, yPosition,
                            OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else if (integer == 100) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "Total Success", _x1 + 0x28, yPosition, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            integer, _x1 + 0x28, yPosition, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            "% Success", _x1 + 0x28, yPosition, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, TRUE, 0);
                    }
                }
                x = x + 1;
            } while (x < 9);
        }

    }
}
}
