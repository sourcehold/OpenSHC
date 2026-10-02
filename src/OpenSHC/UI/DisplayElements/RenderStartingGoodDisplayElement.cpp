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

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::GameMode2Int;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::Text::TextAlignmentInt;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
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
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
            return;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
            return;
        if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE))
            && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2))
            return;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
        LAB_00433e2b:
            _stackMenuStateNotZero = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY);
            if ((_stackMenuStateNotZero != FALSE)
                || (_stackMenuStateNotZero
                    = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT),
                    _stackMenuStateNotZero != FALSE)) {
                posY = posY + 0x32;
            }
        } else {
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0)
                return;
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0)
                return;
            _stackMenuStateNotZero = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::areActivePlayersMostlySameTeam, DAT_GameState::ptr)();
            if (_stackMenuStateNotZero != FALSE)
                return;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameCore::instance.mapU4Int0 == 0))
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
        } while (iVar2 != 0);
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
            if (iVar3 == 0)
                return;
        } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 0;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount45 = 0;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = 0;
        } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 2000;
            DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = 0x1e;
        }
        iVar3 = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].someCount45;
        if (iVar3 == 0) {
            iVar3 = DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset;
            if (iVar3 != 0) {
                DAT_GameState::instance.playerDataArray[_currentPlayerSlotID].textYOffset = iVar3 + -1;
            }
            goto LAB_00433fe5;
        }
        if (_currentGameModeUnk == OpenSHC::Game::GM_SIEGE_THAT) {
            _currentPlayerSlotID = 0;
            _stackMenuStateNotZero = FALSE;
            iVar3 = 0x11;
            uVar5 = 0;
            uVar4 = 0xb8eefb;
            _alignment = OpenSHC::Text::TTA_LEFT;
            _y = posY + 5;
            _x = posX;
            /*
              added by script: "Available Goods"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_STARTUP, 1),
                _x, _y, (TextAlignment)((int)(_alignment)), uVar4, uVar5, iVar3, _stackMenuStateNotZero,
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
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_STARTUP, iVar3, posX, posY + 0x1e, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11,
                FALSE);
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
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + (0x22 - iVar3 / 6) * 6, iVar2 + posX, posY);
        } else if (_currentGameModeUnk != OpenSHC::Game::GM_SIEGE_THAT) {
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
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, _currentPlayerSlotID,
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
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[iVar3],
                    posX + 0x1e,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        + _yOffset + 6 + posY,
                    OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE, 0);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount45
                    != 0) {
                    blendStrength = 0;
                    _stackMenuStateNotZero = TRUE;
                    fontSize = 18;
                    uVar5 = 0;
                    uVar4 = 0xb8eefb;
                    alignment = OpenSHC::Text::TTA_LEFT;
                    yParam
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .textYOffset
                        + _yOffset + 6 + posY;
                    iVar2 = posX + 0x22;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, iVar3),
                        iVar2, yParam, alignment, uVar4, uVar5, fontSize, _stackMenuStateNotZero, blendStrength);
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
