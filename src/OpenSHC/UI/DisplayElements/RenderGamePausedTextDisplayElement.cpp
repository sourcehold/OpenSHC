#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B1E60
    void DisplayElements::RenderGamePausedTextDisplayElement(int posX, int posY, DWORD elementState)
    {
        char* textAddress;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        blendStrength = 0;
        if (DAT_GameCore::instance.gamePausedLogical == 0) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_GAME_PAUSED_TEXT, 0);
            return;
        }
        keepOffsetX = FALSE;
        fontSize = 0x10;
        backgroundColor = 0;
        foregroundColor = 0xc2f0eb;
        alignment = OpenSHC::Text::TTA_CENTER;
        /*
          added by script: "Game Paused"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, 0x16),
            posX, posY, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
    }

}
}
