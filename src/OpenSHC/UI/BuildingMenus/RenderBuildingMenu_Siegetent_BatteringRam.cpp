#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043E1B0
    void BuildingMenus::RenderBuildingMenu_Siegetent_BatteringRam()
    {
        int buildingIDOrY;
        int xOrFontSize;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrBlendStrength;
        BOOLEnum keepOffsetX;
        int blendStrength;
        buildingIDOrY = DAT_BuildingsState::instance.menuSelectedBuildingID;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 0x11;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int yOrX = DAT_MenuHandlerState::instance.y + 0x1eb;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0xb4;
        // "Battering Ram"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 4),
            xOrFontSize, yOrX, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (DAT_BuildingsState::instance.buildings[buildingIDOrY].buildingProgress * 100) / 0x280,
            DAT_MenuHandlerState::instance.x + 0xb4, DAT_MenuHandlerState::instance.y + 0x209, OpenSHC::Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = TRUE;
        xOrFontSize = 0x11;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        buildingIDOrY = DAT_MenuHandlerState::instance.y + 0x209;
        yOrX = DAT_MenuHandlerState::instance.x + 0xb4;
        // "% Complete"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 6),
            yOrX, buildingIDOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
    }

}
}
