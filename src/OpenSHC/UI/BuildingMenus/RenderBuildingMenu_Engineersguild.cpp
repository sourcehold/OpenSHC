#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043CA70
    void BuildingMenus::RenderBuildingMenu_Engineersguild()
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
        // "Engineer's Guild"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_ENGINEERS_GUILD, 0),
            x, y, alignment, color, fontSizeOrWidth, keepOffsetX, blendStrengthOrFontSize);
        MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
        if (DAT_EnoughGoldForRequestedUnit::instance == FALSE) {
            blendStrength = 0;
            blendStrengthOrFontSize = 0x11;
            color2 = 0;
            fontSizeOrWidth = 400;
            y = DAT_MenuHandlerState::instance.y + 0x1fc;
            x = DAT_MenuHandlerState::instance.x + 0x5a;
            // "You do not have enough gold for apprentices"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_ENGINEERS_GUILD, 1),
                x, y, fontSizeOrWidth, color2, blendStrengthOrFontSize, blendStrength);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
            DAT_BuildingsState::ptr)();
    }

}
}
