#include "../AlliesRequestGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD780
        void AlliesRequestGoods::MenuModalRenderFunction_AlliesRequestGoods(int x, int y, int width, int height)
        {
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0xf;
            color = 0xccfaff;
            alignment = Text::TTA_LEFT;
            int yParam = y + 0x19;
            xParam = x + 0x14;
            /*
              added by script: "Request Goods"
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES, 7);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
