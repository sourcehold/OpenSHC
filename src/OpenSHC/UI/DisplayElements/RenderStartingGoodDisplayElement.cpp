#include "../DisplayElements.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/GameMode2Int.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextAlignmentInt.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eGM;
    using DE::SHCDE::eTextSections;
    using Game::GameMode;
    using Game::GameMode2;
    using Game::GameMode2Int;
    using Map::MapType2;
    using Text::TextAlignment;
    using Text::TextAlignmentInt;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433DA0
    void DisplayElements::RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState)
    {
        BOOLEnum _stackMenuStateNotZero;
        int* piVar1;
        int _y;
        char* _text;
        char* textAddress;
        int iVar2;
        GameMode2Int _currentGameModeUnk;
        int iVar3;
        int _yOffset;
        int yParam;
        TextAlignment alignment;
        uint uVar4;
        uint uVar5;
        int fontSize;
        int blendStrength;
        TextAlignmentInt _alignment;
        int _x;
        int _currentPlayerSlotID;
        _yOffset = 0;
        iVar3 = 0;
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {}
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {}
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
            && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE
            && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {}
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
        LAB_00433e2b:
            _stackMenuStateNotZero = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                UI::Enums::DEID_TIME_UNTIL_VICTORY);
            if ((_stackMenuStateNotZero)
                || (_stackMenuStateNotZero = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        UI::Enums::DEID_TIME_UNTIL_DEFEAT),
                    _stackMenuStateNotZero)) {
                posY = posY + 0x32;
            }
        } else {
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0) {}
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {}
            _stackMenuStateNotZero = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::areActivePlayersMostlySameTeam, DAT_GameState::ptr)();
            if (_stackMenuStateNotZero) {}
            if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                || (!DAT_GameCore::instance.mapU4Int0))
                goto LAB_00433e2b;
            posY = posY + 0x46;
        }
        _currentGameModeUnk = DAT_GameCore::instance.gameMode_2;
        _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        piVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                     .startResources
            + 1;
        iVar2 = 5;
        do {
            if (piVar1[-1] != 0) {
                iVar3 = iVar3 + 1;
            }
            if (*piVar1 != 0) {
                iVar3 = iVar3 + 1;
            }
            if (piVar1[1] != 0) {
                iVar3 = iVar3 + 1;
            }
            if (piVar1[2] != 0) {
                iVar3 = iVar3 + 1;
            }
            if (piVar1[3] != 0) {
                iVar3 = iVar3 + 1;
            }
            piVar1 = piVar1 + 5;
            iVar2 = iVar2 + -1;
        } while (iVar2);
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
            if (!iVar3) {}
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 0;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount45 = 0;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = 0;
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 2000;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = 0x1e;
        }
        iVar3 = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount45;
        if (!iVar3) {
            iVar3 = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset;
            if (iVar3) {
                DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = iVar3 + -1;
            }
            goto LAB_00433fe5;
        }
        if (_currentGameModeUnk == Game::GM_SIEGE_THAT) {
            _currentPlayerSlotID = 0;
            _stackMenuStateNotZero = FALSE;
            iVar3 = 0x11;
            uVar5 = 0;
            uVar4 = 0xb8eefb;
            _alignment = Text::TTA_LEFT;
            _y = posY + 5;
            _x = posX;
            /*
              added by script: "Available Goods"
             */
            _text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_STARTUP, 1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(_text, _x,
                _y, (TextAlignment)((int)(_alignment)), uVar4, uVar5, iVar3, _stackMenuStateNotZero,
                _currentPlayerSlotID);
            _currentGameModeUnk = DAT_GameCore::instance.gameMode_2;
        } else {
            if (iVar3 == 1) {
                iVar3 = 0;
            } else {
                if (iVar3 != 2)
                    goto LAB_00433f65;
                iVar3 = 2;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_STARTUP, iVar3, posX, posY + 0x1e, Text::TTA_LEFT, 0xb8eefb, 0, 0x11, FALSE);
            _currentGameModeUnk = DAT_GameCore::instance.gameMode_2;
        }
    LAB_00433f65:
        _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        piVar1 = &DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .someCount47;
        *piVar1 = *piVar1 + 2;
        iVar3 = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount47;
        iVar2 = iVar3 + -0x28;
        iVar3 = iVar3 >> 2;
        if (iVar2 < DAT_WindowAndDirectDraw::instance.resolutionX) {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + (0x22 - iVar3 / 6) * 6, iVar2 + posX, posY);
        } else if (_currentGameModeUnk != Game::GM_SIEGE_THAT) {
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount47 = 0;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount45 = 0;
        }
    LAB_00433fe5:
        iVar3 = 0;
        _currentPlayerSlotID = 0x8d;
        do {
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[iVar3]
                != 0) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, _currentPlayerSlotID,
                    (posX
                        - (int)*(short*)(PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMTotalPicturesProcessed::instance[0x2e] + _currentPlayerSlotID) * 4 + 0x1c)
                            / 2)
                        + 0xc,
                    (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMTotalPicturesProcessed::instance[0x2e] + _currentPlayerSlotID) * 0x10 + 0x72)
                            / 2)
                        + _yOffset + 0xc + posY);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[iVar3],
                    posX + 0x1e,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        + _yOffset + 6 + posY,
                    Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE, 0);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount45
                    != 0) {
                    blendStrength = 0;
                    _stackMenuStateNotZero = TRUE;
                    fontSize = 18;
                    uVar5 = 0;
                    uVar4 = 0xb8eefb;
                    alignment = Text::TTA_LEFT;
                    yParam
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .textYOffset
                        + _yOffset + 6 + posY;
                    iVar2 = posX + 0x22;
                    textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_GOODS, iVar3);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        textAddress, iVar2, yParam, alignment, uVar4, uVar5, fontSize, _stackMenuStateNotZero,
                        blendStrength);
                }
                _yOffset = _yOffset + 30;
            }
            _currentPlayerSlotID = _currentPlayerSlotID + 2;
            iVar3 = iVar3 + 1;
        } while (_currentPlayerSlotID < 0xbf);
        return;
    }

}
}
