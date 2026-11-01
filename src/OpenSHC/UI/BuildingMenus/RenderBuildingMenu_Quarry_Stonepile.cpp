#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C9F0
    void BuildingMenus::RenderBuildingMenu_Quarry_Stonepile()
    {
        int x;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrWidth;
        uint color2;
        BOOLEnum keepOffsetX;
        int blendStrengthOrFontSize;
        int blendStrength;
        blendStrengthOrFontSize = 0;
        keepOffsetX = FALSE;
        fontSizeOrWidth = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int y = DAT_MenuHandlerState::instance.y + 0x1d3;
        x = DAT_MenuHandlerState::instance.x + 0x19;
        // "Quarry Stone Pile"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_QUARRYPILE, 0),
            x, y, alignment, color, fontSizeOrWidth, keepOffsetX, blendStrengthOrFontSize);
        blendStrength = 0;
        blendStrengthOrFontSize = 0x12;
        color2 = 0;
        fontSizeOrWidth = 0x136;
        y = DAT_MenuHandlerState::instance.y + 0x1fb;
        x = DAT_MenuHandlerState::instance.x + 0xaf;
        // "Use an Ox to transport stone placed here."
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_QUARRYPILE, 1),
            x, y, fontSizeOrWidth, color2, blendStrengthOrFontSize, blendStrength);
    }

}
}
