#include "../DisplayElements.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x00433DA0
        void RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState)
        {
            // zeroed before the early returns, as the original does
            int startGoodsCount = 0;
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE
                && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .lordKilledByPlayerID
                    != 0) {
                    return;
                }
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .playerDeathRelated
                    != 0) {
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::areActivePlayersMostlySameTeam,
                        DAT_GameState::ptr)()) {
                    return;
                }
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                || DAT_GameCore::instance.mapU4Int0 == 0) {
                if (MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY)
                    || MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT)) {
                    posY += 50;
                }
            } else {
                posY += 70;
            }
            int const playerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            for (int i = 0; i < countof(DAT_GameState::instance.playerDataArray[0].startResources); ++i) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[i]
                    != 0) {
                    ++startGoodsCount;
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                if (startGoodsCount == 0) {
                    return;
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someCount47 = 0;
                DAT_GameState::instance.playerDataArray[playerSlotID].someCount45 = 0;
                DAT_GameState::instance.playerDataArray[playerSlotID].textYOffset = 0;
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someCount47 = 2000;
                DAT_GameState::instance.playerDataArray[playerSlotID].textYOffset = 30;
            }
            int const goodsPopupState = DAT_GameState::instance.playerDataArray[playerSlotID].someCount45;
            if (goodsPopupState != 0) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    // "Available Goods"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_STARTUP, 1),
                        posX, posY + 5, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE,
                        0);
                } else if (goodsPopupState == 1) {
                    // "Starting goods"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_STARTUP, 0, posX, posY + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE);
                } else if (goodsPopupState == 2) {
                    // "Captured goods"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_STARTUP, 2, posX, posY + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE);
                }
                // the slot is read again after the text calls, as the original does
                int const scrolledPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someCount47 += 2;
                int const scrollIconIndex
                    = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 >> 2;
                int const scrollX = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 - 40;
                if (scrollX < DAT_WindowAndDirectDraw::instance.resolutionX) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 204 + scrollIconIndex % 6, scrollX + posX, posY);
                } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 = 0;
                    DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount45 = 0;
                }
            } else {
                int const remainingTextYOffset = DAT_GameState::instance.playerDataArray[playerSlotID].textYOffset;
                if (remainingTextYOffset != 0) {
                    DAT_GameState::instance.playerDataArray[playerSlotID].textYOffset = remainingTextYOffset - 1;
                }
            }
            int goodsRowY = 0;
            for (int goodIndex = 0; goodIndex < countof(DAT_GameState::instance.playerDataArray[0].startResources);
                ++goodIndex) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[goodIndex]
                    == 0) {
                    continue;
                }
                // two pictures per good from 141
                int const goodGMFrame = goodIndex * 2 + 141;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, goodGMFrame,
                    (posX
                        - DAT_GMImageHeaders::instance
                                .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2]
                                    + goodGMFrame - 1]
                                .width
                            / 2)
                        + 12,
                    (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        - DAT_GMImageHeaders::instance
                                .imh[GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2]
                                    + goodGMFrame - 1]
                                .height
                            / 2)
                        + goodsRowY + 12 + posY);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[goodIndex],
                    posX + 30,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        + goodsRowY + 6 + posY,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 18, FALSE, 0);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount45
                    != 0) {
                    int const labelY
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .textYOffset
                        + goodsRowY + 6 + posY;
                    int const labelX = posX + 34;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, goodIndex),
                        labelX, labelY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 18, TRUE,
                        0);
                }
                goodsRowY += 30;
            }
        }

    }
}
}
