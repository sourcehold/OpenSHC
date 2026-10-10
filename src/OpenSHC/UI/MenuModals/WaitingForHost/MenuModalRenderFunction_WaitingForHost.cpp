#include "../WaitingForHost.func.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x0047E3A0
        void WaitingForHost::MenuModalRenderFunction_WaitingForHost(int x, int y, int width, int height)
        {
            char* textAddress;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x11;
            color = 0xc2f0eb;
            int yParam = y + 0x17;
            alignment = Text::TTA_CENTER;
            int xParam = width / 2 + x;
            /*
              added by script: "Waiting for host..."
             */
            textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x14);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
