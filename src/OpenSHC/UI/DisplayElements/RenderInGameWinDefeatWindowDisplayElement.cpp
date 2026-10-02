#include "../DisplayElements.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::GameLanguage;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AFB30
    void DisplayElements::RenderInGameWinDefeatWindowDisplayElement(int posX, int posY, DWORD elementState)
    {
        DWORD DVar1;
        uint _alivePlayerCount;
        char* pcVar2;
        int iVar3;
        char (*textAddress)[250];
        int iVar4;
        int* piVar5;
        int iVar6;
        int iVar7;
        int yParam;
        TextAlignment TVar8;
        BGR24 BVar9;
        uint backgroundColor;
        BOOLEnum BVar10;
        int iVar11;
        MenuViewType menuID;
        short* local_8;
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_8;
        DVar1 = timeGetTime();
        if (8000 < DVar1 - DAT_GameState::instance.mapAndTime.gameOverTime) {
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                == 0) {
                menuID = OpenSHC::UI::Enums::MVT_GAME_LOSTUnk;
            } else {
                DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
                menuID = OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 0);
        }
        _alivePlayerCount = (uint)(DAT_GameState::instance.mapAndTime.playerIsAlive[1] != 0);
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[2] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[3] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[4] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[5] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[6] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[7] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[8] != 0) {
            _alivePlayerCount = _alivePlayerCount + 1;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        iVar3 = _alivePlayerCount * 0x1e + (0x17 - (_alivePlayerCount * 0x1e + 0x17) % 0x1e);
        iVar4 = posY + (-0x1c - iVar3 / 2);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX + -0x108, iVar4 + -0x13, 0x210, iVar3 + 0x60);
        iVar11 = 0;
        BVar10 = FALSE;
        iVar3 = 0xf;
        BVar9 = 0xc2f0eb;
        TVar8 = OpenSHC::Text::TTA_CENTER;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            == 0) {
            iVar6 = 0x11;
        } else {
            iVar6 = 0x10;
        }
        iVar7 = posX;
        yParam = iVar4;
        /*
          added by script: "Defeat"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, iVar6),
            iVar7, yParam, TVar8, BVar9, iVar3, BVar10, iVar11);
        iVar4 = iVar4 + 0x39;
        piVar5 = DAT_BlendingDefinedData::instance.PlayerSlotUnitColor;
        textAddress = DAT_GameSynchronyState::instance.DAT_PlayerNames;
        local_8 = DAT_GameState::instance.mapAndTime.playerIsAlive + 1;
        do {
            piVar5 = piVar5 + 1;
            textAddress = textAddress + 1;
            if (*local_8 != 0) {
                if ((DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH)
                    || (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN)) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX + -0x1c, iVar4, OpenSHC::Text::TTA_CENTER,
                        (uint)((int)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5])), 0, 0x11, FALSE, 0);
                    BVar9 = DAT_RenderingDefinedData::instance.ColorArray[*piVar5];
                    iVar3 = DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + -0x16;
                    iVar11 = 0x11;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(*textAddress, posX + -0x4e, iVar4, OpenSHC::Text::TTA_CENTER,
                        (uint)((int)(DAT_RenderingDefinedData::instance.ColorArray[*piVar5])), 0, 0x12, FALSE, 0);
                    BVar9 = DAT_RenderingDefinedData::instance.ColorArray[*piVar5];
                    iVar3 = DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + -0x48;
                    iVar11 = 0x12;
                }
                iVar7 = 0;
                BVar10 = FALSE;
                iVar3 = iVar3 + posX;
                backgroundColor = 0;
                TVar8 = OpenSHC::Text::TTA_LEFT;
                iVar6 = iVar4;
                /*
                  added by script: "Wins"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x40),
                    iVar3, iVar6, TVar8, (uint)((int)(BVar9)), backgroundColor, iVar11, BVar10, iVar7);
                iVar4 = iVar4 + 0x1e;
            }
            local_8 = local_8 + 1;
        } while ((int)local_8 < 0x117ef52);
        ;
    }

}
}
