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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043E0E0
    void BuildingMenus::RenderBuildingMenu_Siegetent_Siegetower()
    {
        int buildingIDOrY = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int blendStrength = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSizeOrBlendStrength = 17;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrX = DAT_MenuHandlerState::instance.y + 491;
        int xOrFontSize = DAT_MenuHandlerState::instance.x + 180;
        // "Siege Tower"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 3),
            xOrFontSize, yOrX, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (DAT_BuildingsState::instance.buildings[buildingIDOrY].buildingProgress * 100) / 1280,
            DAT_MenuHandlerState::instance.x + 180, DAT_MenuHandlerState::instance.y + 521, OpenSHC::Text::TTA_LEFT, 0,
            17, FALSE, 0);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = TRUE;
        xOrFontSize = 17;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        buildingIDOrY = DAT_MenuHandlerState::instance.y + 521;
        yOrX = DAT_MenuHandlerState::instance.x + 180;
        // "% Complete"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 6),
            yOrX, buildingIDOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
    }

}
}
