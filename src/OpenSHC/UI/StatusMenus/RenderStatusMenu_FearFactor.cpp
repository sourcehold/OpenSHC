#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::GameLanguage;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043F2F0
    void StatusMenus::RenderStatusMenu_FearFactor()
    {
        int const top = DAT_MenuHandlerState::instance.y + 0x1bf;
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
            x + 0x19, top + 0x14, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        // the good and the bad things the player has built
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, x + 100, top + 0x32);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .goodStuffCount,
            x + 0x80, top + 0x76, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(1, x + 0xb4, top + 0x32);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].badStuffCount,
            x + 0xd0, top + 0x76, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        // The descriptions start at languageOffset + x + 0x118. It is written out at each use because the original
        // evaluates it there, after the y argument.
        // "Popularity Effect:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x12),
            languageOffset + x + 0x118, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        int const fearFactor
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .fearFactorLevel;
        int effect;
        if (fearFactor >= 1) {
            effect = fearFactor * 25;
        } else if (fearFactor <= -1) {
            effect = fearFactor * 25;
        } else {
            effect = 0;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + languageOffset + x + 300, top + 0x19, effect, FALSE);
        int const level = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .fearFactorLevel;
        if (level >= 5) {
            // the top level reached
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x19),
                languageOffset + x + 0x118, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        } else if (level <= -5) {
            // the bottom level reached
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x18),
                languageOffset + x + 0x118, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
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
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1b),
                    languageOffset + x + 0x118, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .objectsLeftUntilNextLevel,
                    languageOffset + x + 0x11d, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x12, TRUE, 0);
            } else if (bad > good) {
                // "Bad things for next level:"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1a, languageOffset + x + 0x118, top + 0x2d,
                    OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .objectsLeftUntilNextLevel,
                    languageOffset + x + 0x11d, top + 0x2d, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x12, TRUE, 0);
            }
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            == 0) {
            // "No effect on population."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 10),
                languageOffset + x + 0x118, top + 0x4b, 0xfa, 0, 0x12, 0);
        }
        if (0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel) {
            // "People are happier, but idler."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xb),
                languageOffset + x + 0x118, top + 0x4b, 0xfa, 0, 0x12, 0);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            < 0) {
            // "People are less happy, but more efficient."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xc),
                languageOffset + x + 0x118, top + 0x4b, 0xfa, 0, 0x12, 0);
        }
        // "Efficiency %:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x13),
            languageOffset + x + 0x118, top + 0x7d, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorProductivityUnk,
            languageOffset + x + 0x11d, top + 0x7e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x12, TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
