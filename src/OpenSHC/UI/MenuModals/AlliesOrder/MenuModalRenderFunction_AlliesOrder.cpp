#include "../AlliesOrder.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using DE::SHCDE::eTextSections;
        using Rendering::Colors::BGR24;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD2B0
        void AlliesOrder::MenuModalRenderFunction_AlliesOrder(int x, int y, int width, int height)
        {
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            MACRO_CALL(UI::Helpers_Func::BuildEnemyPlayerList)();
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0xf;
            color = 0xccfaff;
            alignment = Text::TTA_LEFT;
            int yParam = y + 0x19;
            xParam = x + 0x1e;
            /*
              added by script: "Set Orders"
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES, 5);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
