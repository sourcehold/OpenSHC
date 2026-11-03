#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b98448.hpp"
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
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043FE10
    void StatusMenus::RenderStatusMenu_Religion()
    {
        int const y = DAT_MenuHandlerState::instance.y + 0x1b0;
        int const x = DAT_MenuHandlerState::instance.x;
        DAT_00b98448::instance = DAT_00b98448::instance + 1;
        if (40 < (int)DAT_00b98448::instance) {
            DAT_00b98448::instance = 0;
        }
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            1, DAT_MenuHandlerState::instance.x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
        int const titleY = DAT_MenuHandlerState::instance.y + 0x1d3;
        int const titleX = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Religion"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 8),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, x + 0x78, y + 0x32);
        // "Total priests"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x16),
            x + 0xdc, y + 0x26, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .priestCountUnk,
            x + 0xe2, y + 0x26, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        // "Blessed People %"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x11),
            x + 0xdc, y + 0x3c, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .blessedPeoplePercentage,
            x + 0xe1, y + 0x3c, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        // "Popularity Effect:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x12),
            x + 0xdc, y + 0x52, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
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
        } else {
            effect = blessed <= 94 ? 150 : 200;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xf0 + x, y + 0x52, effect, TRUE);
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
        } else if (blessedNow < 95) {
            nextLevel = 100;
        } else {
            nextLevel = 0;
        }
        if (nextLevel != 0) {
            // "Next level at"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1c),
                x + 0xdc, y + 0x68, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                nextLevel, x + 0xe1, y + 0x68, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "%", x + 0xe2, y + 0x68, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        } else {
            // "Max bonus achieved."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1d),
                x + 0xdc, y + 0x68, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
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
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x20),
                x + 0xdc, y + 0x8c, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .ownsCathedralUnk
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x14),
                x + 0xdc, y + 0x8c, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .ownsChurchUnk
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x15),
                x + 0xdc, y + 0x8c, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        }
        int bonus = 0;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ownsChurchUnk
            != 0) {
            bonus = 25;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .ownsCathedralUnk
            != 0) {
            bonus = bonus + 50;
        }
        if (bonus != 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xfa + x, y + 0x8c, bonus, TRUE);
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
