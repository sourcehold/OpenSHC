#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AFDA0
    void DisplayElements::RenderMissionWinDefeatBannerDisplayElement(int posX, int posY, DWORD winDefeatState)
    {
        char* textAddress;
        int numInGroup;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX + -0xf0, posY + -0x13, 0x1e0, 0x48);
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0xf;
        color = 0xc2f0eb;
        alignment = OpenSHC::Text::TTA_CENTER;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (winDefeatState == 1) {
            numInGroup = 0x10;
        } else {
            numInGroup = 0x11;
        }
        /*
          added by script: "Defeat"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, numInGroup),
            posX, posY, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

}
}
