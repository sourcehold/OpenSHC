#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BBB0
    void BuildingMenus::RenderBuildingMenu_Outpost()
    {
        int titleIndexOrY = 0;
        if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
            == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
            titleIndexOrY = 9;
        }
        int blendStrength = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSizeOrBlendStrength = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrX = DAT_MenuHandlerState::instance.y + 463;
        int xOrFontSize = DAT_MenuHandlerState::instance.x + 25;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, titleIndexOrY),
            xOrFontSize, yOrX, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 517;
        yOrX = DAT_MenuHandlerState::instance.x + 25;
        // "Size"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 18),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 489;
        yOrX = DAT_MenuHandlerState::instance.x + 115;
        // "Small"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 19),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 489;
        yOrX = DAT_MenuHandlerState::instance.x + 203;
        // "Large"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 20),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 575;
        yOrX = DAT_MenuHandlerState::instance.x + 25;
        alignment = OpenSHC::Text::TTA_LEFT;
        // "Start Delay"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 21),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 547;
        yOrX = DAT_MenuHandlerState::instance.x + 115;
        // "None"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 22),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 547;
        yOrX = DAT_MenuHandlerState::instance.x + 203;
        // "10 Mins"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 23),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
    }

}
}
