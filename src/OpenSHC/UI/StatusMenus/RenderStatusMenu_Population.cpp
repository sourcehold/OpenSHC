#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043F6A0
    void StatusMenus::RenderStatusMenu_Population()
    {
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int const top = DAT_MenuHandlerState::instance.y + 0x1bf;
        int const x = DAT_MenuHandlerState::instance.x;
        // the graph shows the last 300 months
        int months = DAT_GameState::instance.mapAndTime.populationIndex;
        if (300 < DAT_GameState::instance.mapAndTime.populationIndex) {
            months = 300;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(1, x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Population"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 3),
            DAT_MenuHandlerState::instance.x + 0x19, DAT_MenuHandlerState::instance.y + 0x1d3, OpenSHC::Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        // the axes, three pixels thick
        int const bottom = top + 0x7e;
        int const right = x + 0x1ed;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbc, bottom, right, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbc, top + 0x7f, right, top + 0x7f, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbc, top + 0x80, right, top + 0x80, COL_BLACK::instance.shortValue);
        int const graphTop = top + 0x32;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbe, graphTop, x + 0xbe, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbd, graphTop, x + 0xbd, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0xbc, graphTop, x + 0xbc, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0x1eb, graphTop, x + 0x1eb, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 0x1ec, graphTop, x + 0x1ec, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            right, graphTop, right, bottom, COL_BLACK::instance.shortValue);
        // "Years"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xd),
            x + 0x154, top + 0x8e, OpenSHC::Text::TTA_CENTER, 0, 0x13, FALSE, 0);
        // the vertical scale: 50 people per 75 pixels, doubled until the highest population fits
        int highest = 0;
        for (int month = 0; month < months; month++) {
            if (DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month] > highest) {
                highest = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month];
            }
        }
        int scale;
        if (highest <= 50) {
            scale = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                50, x + 0xac, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
        } else {
            if (highest <= 100) {
                scale = 2;
            } else if (highest <= 200) {
                scale = 4;
            } else if (highest <= 400) {
                scale = 8;
            } else if (highest <= 800) {
                scale = 16;
            } else {
                scale = 32;
            }
            if (scale == 32) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    1600, x + 0x9c, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    scale * 50, x + 0xa4, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            0, x + 0xb4, top + 0x78, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
        // a year label every five years
        for (int label = 0; label <= 5; label++) {
            int firstYear = (DAT_GameState::instance.mapAndTime.populationIndex - 300) / 12;
            if (firstYear < 0) {
                firstYear = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                firstYear + label * 5, label * 1475 / 25 + 0xbe + x, top + 0x82, OpenSHC::Text::TTA_LEFT, 0, 0x13,
                FALSE, 0);
        }
        // one bar per month
        if (months <= 300) {
            for (int month = 0; month < months; month++) {
                short const population = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month];
                if (population > 0) {
                    int const height = population * 75 / (scale * 50);
                    if (height >= 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, bottom);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                            DAT_TextureRenderCoreObject::ptr)(0, x + 0xbf + month, top - height + 0x7e);
                    }
                }
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
            DAT_TextureRenderCoreObject::ptr)();
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
