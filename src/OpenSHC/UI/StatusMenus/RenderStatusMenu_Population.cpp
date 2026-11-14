#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x0043F6A0
    void StatusMenus::RenderStatusMenu_Population()
    {
        // top first, then the player and x (player first: quick_diff 0.9638 -> 0.8913)
        int const top = DAT_MenuHandlerState::instance.y + 447;
        int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int const x = DAT_MenuHandlerState::instance.x;
        // the graph shows the last 300 months
        int months = DAT_GameState::instance.mapAndTime.populationIndex;
        if (300 < DAT_GameState::instance.mapAndTime.populationIndex) {
            months = 300;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(1, x + 14, DAT_MenuHandlerState::instance.y + 489);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // y then x for the title (in the call: quick_diff 0.9638 -> 0.8693; x first: 0.9512)
        int const titleY = DAT_MenuHandlerState::instance.y + 467;
        int const titleX = DAT_MenuHandlerState::instance.x + 25;
        // "Population"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 3),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        // the axes, three pixels thick
        int const bottom = top + 126;
        int const right = x + 493;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 188, bottom, right, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 188, top + 127, right, top + 127, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 188, top + 128, right, top + 128, COL_BLACK::instance.shortValue);
        int const graphTop = top + 50;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 190, graphTop, x + 190, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 189, graphTop, x + 189, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 188, graphTop, x + 188, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 491, graphTop, x + 491, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            x + 492, graphTop, x + 492, bottom, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            right, graphTop, right, bottom, COL_BLACK::instance.shortValue);
        // "Years"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 13),
            x + 340, top + 142, OpenSHC::Text::TTA_CENTER, 0, 19, FALSE, 0);
        // the vertical scale: 50 people per 75 pixels, doubled until the highest population fits
        int highest = 0;
        for (int month = 0; month < months; ++month) {
            if (DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month] > highest) {
                highest = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month];
            }
        }
        int scale;
        if (highest <= 50) {
            scale = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                50, x + 172, top + 45, OpenSHC::Text::TTA_LEFT, 0, 19, FALSE, 0);
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
                    1600, x + 156, top + 45, OpenSHC::Text::TTA_LEFT, 0, 19, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    scale * 50, x + 164, top + 45, OpenSHC::Text::TTA_LEFT, 0, 19, FALSE, 0);
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            0, x + 180, top + 120, OpenSHC::Text::TTA_LEFT, 0, 19, FALSE, 0);
        // a year label every five years
        for (int label = 0; label <= 5; ++label) {
            // the first year shown, at least 0, through max() (an if: quick_diff 0.9638 -> 0.9384)
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                max(0, (DAT_GameState::instance.mapAndTime.populationIndex - 300) / 12) + label * 5,
                label * 1475 / 25 + 190 + x, top + 130, OpenSHC::Text::TTA_LEFT, 0, 19, FALSE, 0);
        }
        // one bar per month
        if (months <= 300) {
            for (int month = 0; month < months; ++month) {
                short const population = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[player][month];
                if (population > 0) {
                    int const height = population * 75 / (scale * 50);
                    if (height >= 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, bottom);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                            DAT_TextureRenderCoreObject::ptr)(0, x + 191 + month, top - height + 126);
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
