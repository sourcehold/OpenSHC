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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043CB90
    void BuildingMenus::RenderBuildingMenu_Cathedral()
    {
        int blendStrengthOrFontSize = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSizeOrWidth = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int y = DAT_MenuHandlerState::instance.y + 467;
        int x = DAT_MenuHandlerState::instance.x + 25;
        // "Cathedral"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CATHEDRAL, 0),
            x, y, alignment, color, fontSizeOrWidth, keepOffsetX, blendStrengthOrFontSize);
        MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForMonk)();
        if (DAT_EnoughGoldForRequestedUnit::instance == FALSE) {
            int blendStrength = 0;
            blendStrengthOrFontSize = 17;
            uint color2 = 0;
            fontSizeOrWidth = 340;
            y = DAT_MenuHandlerState::instance.y + 508;
            x = DAT_MenuHandlerState::instance.x + 150;
            // "You do not have enough gold for monks"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CATHEDRAL, 1),
                x, y, fontSizeOrWidth, color2, blendStrengthOrFontSize, blendStrength);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
            DAT_BuildingsState::ptr)();
    }

}
}
