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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        char (*textAddress)[250];
        int iVar4;
        int* piVar5;
        short* local_8;
        // The original is built with /GS and sets up a security cookie here, so its source declared a local buffer
        // larger than 4 bytes whose address escaped. Nothing in the original reads that buffer, so its element type
        // and length cannot be recovered - this is the smallest declaration that reproduces the cookie and the
        // original's 8-byte frame exactly. It is a reconstruction of the frame, not a recovered name.
        short _securityCookieBuffer[3];
        local_8 = _securityCookieBuffer;
        DWORD DVar1 = timeGetTime();
        if (8000 < DVar1 - DAT_GameState::instance.mapAndTime.gameOverTime) {
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
        int _alivePlayerCount = 0;
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[1] != 0) {
            _alivePlayerCount = 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[2] != 0) {
            ++_alivePlayerCount; // written out as in the draft; not tried as a loop
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[3] != 0) {
            ++_alivePlayerCount;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[4] != 0) {
            ++_alivePlayerCount;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[5] != 0) {
            ++_alivePlayerCount;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[6] != 0) {
            ++_alivePlayerCount;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[7] != 0) {
            ++_alivePlayerCount;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[8] != 0) {
            ++_alivePlayerCount;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        int iVar3 = _alivePlayerCount * 0x1e - 6;
        iVar3 += (29 - (iVar3 + 29) % 0x1e);
        iVar4 = posY + (-28 - iVar3 / 2);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX - 264, iVar4 - 19, 528, iVar3 + 96);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Defeat"
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 16),
                posX, iVar4, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 15, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 17),
                posX, iVar4, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 15, FALSE, 0);
        }
        iVar4 += 57;
        piVar5 = DAT_BlendingDefinedData::instance.PlayerSlotUnitColor + 1;
        textAddress = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
        local_8 = DAT_GameState::instance.mapAndTime.playerIsAlive + 1;
        do {
            if (*local_8 != 0) {
                if ((DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH)
                    || (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN)) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX - 28, iVar4, OpenSHC::Text::TTA_CENTER,
                        DAT_RenderingDefinedData::instance.ColorArray[*piVar5], 0, 17, FALSE, 0);
                    // "Wins"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 64),
                        DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 - 22 + posX, iVar4,
                        OpenSHC::Text::TTA_LEFT, DAT_RenderingDefinedData::instance.ColorArray[*piVar5], 0, 17, FALSE,
                        0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX - 78, iVar4, OpenSHC::Text::TTA_CENTER,
                        DAT_RenderingDefinedData::instance.ColorArray[*piVar5], 0, 18, FALSE, 0);
                    // "Wins"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 64),
                        DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 - 72 + posX, iVar4,
                        OpenSHC::Text::TTA_LEFT, DAT_RenderingDefinedData::instance.ColorArray[*piVar5], 0, 18, FALSE,
                        0);
                }
                iVar4 += 0x1e;
            }
            ++local_8;
            ++piVar5;
            ++textAddress;
        } while ((int)local_8 < (int)&DAT_GameState::instance + 0x53e9a);
        ;
    }

}
}
