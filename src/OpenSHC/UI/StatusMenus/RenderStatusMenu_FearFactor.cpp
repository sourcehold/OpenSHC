#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043F2F0
    void StatusMenus::RenderStatusMenu_FearFactor()
    {
        int const top = DAT_MenuHandlerState::instance.y + 447;
        int const x = DAT_MenuHandlerState::instance.x;
        // longer translations get 20 more pixels for the descriptions
        int languageOffset = 0;
        if (DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_ENGLISH
            && DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_AMERICAN) {
            languageOffset = -20;
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Fear Factor"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 2),
            x + 25, top + 20, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        // the good and the bad things the player has built
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, x + 100, top + 50);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .goodStuffCount,
            x + 128, top + 118, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(1, x + 180, top + 50);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].badStuffCount,
            x + 208, top + 118, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        // languageOffset + x + 280 is written out at each use: the original evaluates it after the y argument.
        // "Popularity Effect:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 18),
            languageOffset + x + 280, top + 25, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        int const fearFactor
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .fearFactorLevel;
        // both signs compute the effect in their own branch, as the original does
        int effect;
        if (fearFactor >= 1) {
            effect = fearFactor * 25;
        } else if (fearFactor <= -1) {
            effect = fearFactor * 25;
        } else {
            effect = 0;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + languageOffset + x + 300, top + 25, effect, FALSE);
        // the original reads the level again here
        int const level = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .fearFactorLevel;
        if (level >= 5) {
            // the top level reached
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 25),
                languageOffset + x + 280, top + 45, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        } else if (level <= -5) {
            // the bottom level reached
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 24),
                languageOffset + x + 280, top + 45, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        } else {
            int const good
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .goodStuffCount;
            int const bad
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .badStuffCount;
            if (bad < good) {
                // "Good things for next level:"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 27),
                    languageOffset + x + 280, top + 45, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .objectsLeftUntilNextLevel,
                    languageOffset + x + 285, top + 45, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF,
                    0, 18, TRUE, 0);
            } else if (bad > good) {
                // "Bad things for next level:"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 26, languageOffset + x + 280, top + 45,
                    OpenSHC::Text::TTA_LEFT, 0, 18, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .objectsLeftUntilNextLevel,
                    languageOffset + x + 285, top + 45, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF,
                    0, 18, TRUE, 0);
            }
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            == 0) {
            // "No effect on population."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 10),
                languageOffset + x + 280, top + 75, 250, 0, 18, 0);
        }
        if (0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel) {
            // "People are happier, but idler."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 11),
                languageOffset + x + 280, top + 75, 250, 0, 18, 0);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            < 0) {
            // "People are less happy, but more efficient."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 12),
                languageOffset + x + 280, top + 75, 250, 0, 18, 0);
        }
        // "Efficiency %:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 19),
            languageOffset + x + 280, top + 125, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorProductivityUnk,
            languageOffset + x + 285, top + 126, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18,
            TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
