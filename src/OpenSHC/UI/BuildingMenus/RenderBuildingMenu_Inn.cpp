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
        int buildingIDOrAleCoverage = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int blendStrength = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSizeOrBlendStrength = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrBonus = DAT_MenuHandlerState::instance.y + 467;
        int xOrFontSize = DAT_MenuHandlerState::instance.x + 25;
        // "Inn"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 0),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 169, DAT_MenuHandlerState::instance.x + 180,
            DAT_MenuHandlerState::instance.y + 465);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[buildingIDOrAleCoverage].flagonsOfAleOrCheeseOrReleaseDogs
                / 160,
            DAT_MenuHandlerState::instance.x + 200, (int)(DAT_MenuHandlerState::instance.y + 471),
            OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        blendStrength = 0;
        keepOffsetX = TRUE;
        fontSizeOrBlendStrength = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 471;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 220;
        // "Flagons of ale"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 3),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[buildingIDOrAleCoverage].flagonsOfAleOrCheeseOrReleaseDogs,
            DAT_MenuHandlerState::instance.x + 224, DAT_MenuHandlerState::instance.y + 471, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        fontSizeOrBlendStrength = 0;
        keepOffsetX = FALSE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        buildingIDOrAleCoverage = DAT_MenuHandlerState::instance.y + 489;
        yOrBonus = DAT_MenuHandlerState::instance.x + 180;
        // "Working Inns"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 7),
            yOrBonus, buildingIDOrAleCoverage, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .workingInnsCount,
            DAT_MenuHandlerState::instance.x + 184, DAT_MenuHandlerState::instance.y + 489, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("(",
            DAT_MenuHandlerState::instance.x + 194, DAT_MenuHandlerState::instance.y + 489, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].countInns,
            DAT_MenuHandlerState::instance.x + 196, DAT_MenuHandlerState::instance.y + 489, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(")",
            DAT_MenuHandlerState::instance.x + 198, DAT_MenuHandlerState::instance.y + 489, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        buildingIDOrAleCoverage = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 507;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 180;
        // "Population coverage"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 5),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            buildingIDOrAleCoverage, DAT_MenuHandlerState::instance.x + 184, DAT_MenuHandlerState::instance.y + 507,
            OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 186, DAT_MenuHandlerState::instance.y + 507, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
        if (buildingIDOrAleCoverage < 25) {
            yOrBonus = 0;
        } else if (buildingIDOrAleCoverage < 50) {
            yOrBonus = 50;
        } else if (buildingIDOrAleCoverage < 75) {
            yOrBonus = 100;
        } else {
            yOrBonus = buildingIDOrAleCoverage < 100 ? 150 : 200;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 214 + DAT_MenuHandlerState::instance.x,
            DAT_MenuHandlerState::instance.y + 507, yOrBonus, TRUE);
        if (buildingIDOrAleCoverage < 25) {
            buildingIDOrAleCoverage = 25;
        } else if (buildingIDOrAleCoverage < 50) {
            buildingIDOrAleCoverage = 50;
        } else if (buildingIDOrAleCoverage < 75) {
            buildingIDOrAleCoverage = 75;
        } else if (buildingIDOrAleCoverage < 100) {
            buildingIDOrAleCoverage = 100;
        } else {
            fontSizeOrBlendStrength = 0;
            keepOffsetX = FALSE;
            xOrFontSize = 18;
            color = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            buildingIDOrAleCoverage = DAT_MenuHandlerState::instance.y + 525;
            yOrBonus = DAT_MenuHandlerState::instance.x + 180;
            // "Maximum bonus achieved"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 8),
                yOrBonus, buildingIDOrAleCoverage, alignment, color, xOrFontSize, keepOffsetX, fontSizeOrBlendStrength);
            return;
        }
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSizeOrBlendStrength = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrBonus = DAT_MenuHandlerState::instance.y + 525;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 180;
        // "Next level at"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 6),
            xOrFontSize, yOrBonus, alignment, color, fontSizeOrBlendStrength, keepOffsetX, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            buildingIDOrAleCoverage, DAT_MenuHandlerState::instance.x + 184, DAT_MenuHandlerState::instance.y + 525,
            OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 186, DAT_MenuHandlerState::instance.y + 525, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
    }

}
}
