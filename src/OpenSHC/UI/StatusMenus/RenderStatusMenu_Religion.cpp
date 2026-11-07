#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b98448.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0043FE10
    void StatusMenus::RenderStatusMenu_Religion()
    {
        int const y = DAT_MenuHandlerState::instance.y + 432;
        int const x = DAT_MenuHandlerState::instance.x;
        ++DAT_00b98448::instance;
        if (40 < DAT_00b98448::instance) {
            DAT_00b98448::instance = 0;
        }
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            1, DAT_MenuHandlerState::instance.x + 14, DAT_MenuHandlerState::instance.y + 489);
        // the title position is computed before the draw-buffer store, as the original orders it
        int const titleY = DAT_MenuHandlerState::instance.y + 467;
        int const titleX = DAT_MenuHandlerState::instance.x + 25;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Religion"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 8),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, x + 120, y + 50);
        // "Total priests"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 22),
            x + 220, y + 38, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .priestCountUnk,
            x + 226, y + 38, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        // "Blessed People %"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 17),
            x + 220, y + 60, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .blessedPeoplePercentage,
            x + 225, y + 60, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        // "Popularity Effect:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 18),
            x + 220, y + 82, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        int const blessed
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .blessedPeoplePercentage;
        int effect;
        if (blessed <= 24) {
            effect = 0;
        } else if (blessed <= 49) {
            effect = 50;
        } else if (blessed <= 74) {
            effect = 100;
        } else if (blessed <= 94) {
            effect = 150;
        } else {
            effect = 200;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 240 + x, y + 82, effect, TRUE);
        int const blessedNow
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .blessedPeoplePercentage;
        int nextLevel;
        if (blessedNow <= 24) {
            nextLevel = 25;
        } else if (blessedNow <= 49) {
            nextLevel = 50;
        } else if (blessedNow <= 74) {
            nextLevel = 75;
            // the same threshold as <= 94 above; the original compares it this way here
        } else if (blessedNow < 95) {
            nextLevel = 100;
        } else {
            nextLevel = 0;
        }
        if (nextLevel != 0) {
            // "Next level at"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 28),
                x + 220, y + 104, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                nextLevel, x + 225, y + 104, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                // "%"
                s_percentage_005a2770, x + 226, y + 104, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        } else {
            // "Max bonus achieved."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 29),
                x + 220, y + 104, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // church and cathedral bonus
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ownsCathedralUnk
                != 0
            && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ownsChurchUnk
                != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 32),
                x + 220, y + 140, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .ownsCathedralUnk
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 20),
                x + 220, y + 140, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .ownsChurchUnk
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 21),
                x + 220, y + 140, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        int bonus = 0;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ownsChurchUnk
            != 0) {
            bonus = 25;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .ownsCathedralUnk
            != 0) {
            bonus += 50;
        }
        if (bonus != 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 250 + x, y + 140, bonus, TRUE);
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
