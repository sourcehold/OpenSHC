#include "../ProgressBarBox.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x00493560
        void ProgressBarBox::MenuModalRenderFunction_ProgressBarBox(int x, int y, int width, int height)
        {
            // y is copied in each arm of the language test, where the original loads it: y itself holds the bar's x
            // further down. Declared with y as its value, top has y loaded at the function's start: the match is lost.
            int top;
            // the title, in a smaller font for English and American
            if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH
                || DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN) {
                top = y;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS,
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter),
                    width / 2 + x, top + 25, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 16,
                    FALSE, 0);
            } else {
                top = y;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS,
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter),
                    width / 2 + x, top + 25, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                    FALSE, 0);
            }
            // the bar's box: filled in a game that is neither solitary nor a single player skirmish while saveRelated
            // is set, dimmed otherwise. RenderLoadAndSaveBar draws the progress at the place kept here.
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_GameSynchronyState::instance.saveRelated != 0) {
                int barInset = (width - 300) / 2;
                int barY = top + 65;
                // the bar's x: the original keeps it in y's place on the stack, so it is assigned to y
                y = barInset + x;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                    y, barY, x - barInset + width, top + 80, COL_VERY_SOFT_YELLOW::instance.shortValue);
                DAT_MenuTextInputState::instance.progressBarY = barY;
                DAT_MenuTextInputState::instance.progressBarX = y;
            } else {
                int barInset = (width - 300) / 2;
                int barY = top + 65;
                // the bar's x: the original keeps it in y's place on the stack, so it is assigned to y
                y = barInset + x;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    y, barY, x - barInset + width, top + 80);
                DAT_MenuTextInputState::instance.progressBarY = barY;
                DAT_MenuTextInputState::instance.progressBarX = y;
            }
        }
    }
}
}
