#include "../DisplayElements.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AFB30
    void DisplayElements::RenderInGameWinDefeatWindowDisplayElement(int posX, int posY, DWORD elementState)
    {
        // the original has a security cookie, so its source had a buffer here whose address was taken; nothing
        // reads it, so its type and length are a guess
        char unused[8];
        char* unusedPointer = unused;
        // eight seconds after the game is over, on to the next screen
        if (8000 < timeGetTime() - DAT_GameState::instance.mapAndTime.gameOverTime) {
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                != 0) {
                DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_GAME_LOSTUnk, 0);
            }
        }
        // the window is as high as the list of the players still alive, in whole steps of 30
        int players = 0;
        for (int player = 1; player < countof(DAT_GameState::instance.mapAndTime.playerIsAlive); ++player) {
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[player] != 0) {
                ++players;
            }
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        int height = players * 30 - 6;
        height += 29 - (height + 29) % 30;
        posY += -28 - height / 2;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX - 264, posY - 19, 528, height + 96);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            != 0) {
            // "Victory"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 16),
                posX, posY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 15, FALSE, 0);
        } else {
            // "Defeat"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 17),
                posX, posY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 15, FALSE, 0);
        }
        // each player still alive: the name in the player's colour and "Wins" behind it
        posY += 57;
        for (int player = 1; player < countof(DAT_GameState::instance.mapAndTime.playerIsAlive); ++player) {
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[player] != 0) {
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH
                    || DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[player], posX - 28,
                        posY, OpenSHC::Text::TTA_CENTER,
                        DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                        0, 17, FALSE, 0);
                    // the colour, then x, in locals in front of the call (in the call, or x first, loses the match)
                    uint const winsColor
                        = DAT_RenderingDefinedData::instance
                              .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]];
                    int const winsX = DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 - 22 + posX;
                    // "Wins"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 64),
                        winsX, posY, OpenSHC::Text::TTA_LEFT, winsColor, 0, 17, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[player], posX - 78,
                        posY, OpenSHC::Text::TTA_CENTER,
                        DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                        0, 18, FALSE, 0);
                    uint const winsColor
                        = DAT_RenderingDefinedData::instance
                              .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]];
                    int const winsX = DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 - 72 + posX;
                    // "Wins"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 64),
                        winsX, posY, OpenSHC::Text::TTA_LEFT, winsColor, 0, 18, FALSE, 0);
                }
                posY += 30;
            }
        }
    }

}
}
