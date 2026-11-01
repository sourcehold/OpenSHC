#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043AF40
    void BuildingMenus::RenderBuildingMenu_Inn()
    {
        int buildingIDOrAleCoverage;
        int xOrFontSize;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrBlendStrength;
        BOOLEnum keepOffsetX;
        int blendStrength;
        buildingIDOrAleCoverage = DAT_BuildingsState::instance.menuSelectedBuildingID;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int yOrBonus = DAT_MenuHandlerState::instance.y + 0x1d3;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0x19;
        // "Inn"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 0),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0xa9, DAT_MenuHandlerState::instance.x + 0xb4,
            DAT_MenuHandlerState::instance.y + 0x1d1);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[buildingIDOrAleCoverage].flagonsOfAleOrCheeseOrReleaseDogs
                / 0xa0,
            DAT_MenuHandlerState::instance.x + 200, (int)(DAT_MenuHandlerState::instance.y + 471),
            OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        blendStrength = 0;
        keepOffsetX = TRUE;
        fontSizeOrBlendStrength = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 0x1d7;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0xdc;
        // "Flagons of ale"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 3),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[buildingIDOrAleCoverage].flagonsOfAleOrCheeseOrReleaseDogs,
            DAT_MenuHandlerState::instance.x + 0xe0, DAT_MenuHandlerState::instance.y + 0x1d7, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        buildingIDOrAleCoverage = DAT_MenuHandlerState::instance.y + 0x1e9;
        yOrBonus = DAT_MenuHandlerState::instance.x + 0xb4;
        // "Working Inns"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 7),
            yOrBonus, buildingIDOrAleCoverage, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .workingInnsCount,
            DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("(",
            DAT_MenuHandlerState::instance.x + 0xc2, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].countInns,
            DAT_MenuHandlerState::instance.x + 0xc4, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(")",
            DAT_MenuHandlerState::instance.x + 0xc6, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        buildingIDOrAleCoverage = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 0x1fb;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0xb4;
        // "Population coverage"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 5),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            buildingIDOrAleCoverage, DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x1fb,
            OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 0xba, DAT_MenuHandlerState::instance.y + 0x1fb, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        if (buildingIDOrAleCoverage < 0x19) {
            yOrBonus = 0;
        } else if (buildingIDOrAleCoverage < 0x32) {
            yOrBonus = 0x32;
        } else if (buildingIDOrAleCoverage < 0x4b) {
            yOrBonus = 100;
        } else {
            yOrBonus = buildingIDOrAleCoverage < 100 ? 150 : 200;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xd6 + DAT_MenuHandlerState::instance.x,
            DAT_MenuHandlerState::instance.y + 0x1fb, yOrBonus, TRUE);
        if (buildingIDOrAleCoverage < 0x19) {
            buildingIDOrAleCoverage = 0x19;
        } else if (buildingIDOrAleCoverage < 0x32) {
            buildingIDOrAleCoverage = 0x32;
        } else if (buildingIDOrAleCoverage < 0x4b) {
            buildingIDOrAleCoverage = 0x4b;
        } else if (buildingIDOrAleCoverage < 100) {
            buildingIDOrAleCoverage = 100;
        } else {
            fontSizeOrBlendStrength = 0;
            keepOffsetX = FALSE;
            xOrFontSize = 0x12;
            color = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            buildingIDOrAleCoverage = DAT_MenuHandlerState::instance.y + 0x20d;
            yOrBonus = DAT_MenuHandlerState::instance.x + 0xb4;
            // "Maximum bonus achieved"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 8),
                yOrBonus, buildingIDOrAleCoverage, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
            return;
        }
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 0x12;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 0x20d;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 0xb4;
        // "Next level at"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 6),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            buildingIDOrAleCoverage, DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x20d,
            OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 0xba, DAT_MenuHandlerState::instance.y + 0x20d, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
    }

}
}
