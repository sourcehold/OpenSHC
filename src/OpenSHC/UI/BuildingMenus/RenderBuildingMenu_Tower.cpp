#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/BuildingMenus.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x00447D30
    void BuildingMenus::RenderBuildingMenu_Tower()
    {
        int selectedType;
        int x;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrWidth;
        uint color2;
        BOOLEnum keepOffsetX;
        int blendStrengthOrFontSize;
        int blendStrength;
        selectedType
            = (short)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                  .buildingType;
        blendStrengthOrFontSize = 0;
        keepOffsetX = FALSE;
        fontSizeOrWidth = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int y = DAT_MenuHandlerState::instance.y + 0x1d3;
        x = DAT_MenuHandlerState::instance.x + 0x19;
        // "Tower"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TOWER, 0),
            x, y, alignment, color, fontSizeOrWidth, keepOffsetX, blendStrengthOrFontSize);
        blendStrength = 0;
        blendStrengthOrFontSize = 0x12;
        color2 = 0;
        fontSizeOrWidth = 0x136;
        y = DAT_MenuHandlerState::instance.y + 0x1fb;
        x = DAT_MenuHandlerState::instance.x + 0xaf;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TOWER, selectedType - 0x49),
            x, y, fontSizeOrWidth, color2, blendStrengthOrFontSize, blendStrength);
        MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_RenderTowerAndGateHealth)();
    }

}
}
