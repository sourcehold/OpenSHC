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
        int xOrFontSize;
        int titleIndexOrY;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrBlendStrength;
        BOOLEnum keepOffsetX;
        int blendStrength;
        titleIndexOrY = 0;
        if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
            == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
            titleIndexOrY = 9;
        }
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int yOrX = DAT_MenuHandlerState::instance.y + 0x1cf;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0x19;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, titleIndexOrY),
            xOrFontSize, yOrX, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x205;
        yOrX = DAT_MenuHandlerState::instance.x + 0x19;
        // "Size"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x12),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x1e9;
        yOrX = DAT_MenuHandlerState::instance.x + 0x73;
        // "Small"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x13),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x1e9;
        yOrX = DAT_MenuHandlerState::instance.x + 0xcb;
        // "Large"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x14),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x23f;
        yOrX = DAT_MenuHandlerState::instance.x + 0x19;
        alignment = OpenSHC::Text::TTA_LEFT;
        // "Start Delay"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x15),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x223;
        yOrX = DAT_MenuHandlerState::instance.x + 0x73;
        // "None"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x16),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        titleIndexOrY = DAT_MenuHandlerState::instance.y + 0x223;
        yOrX = DAT_MenuHandlerState::instance.x + 0xcb;
        // "10 Mins"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x17),
            yOrX, titleIndexOrY, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
    }

}
}
