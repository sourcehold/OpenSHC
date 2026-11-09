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
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::Text::TextAlignmentInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433DA0
    void DisplayElements::RenderStartingGoodDisplayElement(int posX, int posY, DWORD elementState)
    {
        int startGoodsCount = 0;
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
            return;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
            return;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
            && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE
            && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2)
            return;
        BOOLEnum isVictoryOrDefeatTimerShown;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
        LAB_00433e2b:
            isVictoryOrDefeatTimerShown
                = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY);
            if ((isVictoryOrDefeatTimerShown)
                || (isVictoryOrDefeatTimerShown
                    = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT),
                    isVictoryOrDefeatTimerShown != FALSE)) {
                posY += 50;
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
            BOOLEnum const arePlayersMostlySameTeam = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::areActivePlayersMostlySameTeam, DAT_GameState::ptr)();
            if (arePlayersMostlySameTeam)
                return;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameCore::instance.mapU4Int0 == 0))
                goto LAB_00433e2b;
            posY += 70;
        }
        int const countedPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int* goodsRow = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .startResources
            + 1;
        int goodsRowsRemaining = 5;
        do {
            if (goodsRow[-1] != 0) {
                ++startGoodsCount;
            }
            if (*goodsRow != 0) {
                ++startGoodsCount;
            }
            if (goodsRow[1] != 0) {
                ++startGoodsCount;
            }
            if (goodsRow[2] != 0) {
                ++startGoodsCount;
            }
            if (goodsRow[3] != 0) {
                ++startGoodsCount;
            }
            goodsRow += 5;
            --goodsRowsRemaining;
        } while (goodsRowsRemaining != 0);
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
            if (startGoodsCount == 0)
                return;
        } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 0;
            DAT_GameState::instance.playerDataArray[countedPlayerSlotID].someCount45 = 0;
            DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset = 0;
        } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = 2000;
            DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset = 0x1e;
        }
        int const goodsPopupState = DAT_GameState::instance.playerDataArray[countedPlayerSlotID].someCount45;
        if (goodsPopupState != 0) {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                int headingParam9 = 0;
                BOOLEnum headingUseShadow = FALSE;
                int headingFontSize = 17;
                uint headingShadowColor = 0;
                uint headingColor = 0xb8eefb;
                TextAlignmentInt headingAlignment = OpenSHC::Text::TTA_LEFT;
                int headingY = posY + 5;
                int headingX = posX;
                /*
                  added by script: "Available Goods"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_STARTUP, 1),
                    headingX, headingY, (TextAlignment)((int)(headingAlignment)), headingColor, headingShadowColor,
                    headingFontSize, headingUseShadow, headingParam9);
            } else {
                if (goodsPopupState == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_STARTUP, 0, posX, posY + 0x1e, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0,
                        17, FALSE);
                } else if (goodsPopupState == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_STARTUP, 2, posX, posY + 0x1e, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0,
                        17, FALSE);
                }
            }
            int const scrolledPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .someCount47
                + 2;
            int const scrollIconIndex = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 >> 2;
            int const scrollX = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 - 40;
            if (scrollX < DAT_WindowAndDirectDraw::instance.resolutionX) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    scrollIconIndex + (34 - scrollIconIndex / 6) * 6, scrollX + posX, posY);
            } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 = 0;
                DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount45 = 0;
            }
        } else {
            int const remainingTextYOffset = DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset;
            if (remainingTextYOffset != 0) {
                DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset = remainingTextYOffset - 1;
            }
            goto LAB_00433fe5;
        }
    LAB_00433fe5:
        int goodsRowY = 0;
        int goodIndex = 0;
        int goodGMFrame = 141;
        do {
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[goodIndex]
                != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, goodGMFrame,
                    (posX
                        - (int)*(short*)(PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMFirstPictureIndex::instance[46] + goodGMFrame) * 4 + 28)
                            / 2)
                        + 12,
                    (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMFirstPictureIndex::instance[46] + goodGMFrame) * 16 + 114)
                            / 2)
                        + goodsRowY + 12 + posY);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[goodIndex],
                    posX + 0x1e,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        + goodsRowY + 6 + posY,
                    OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, FALSE, 0);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount45
                    != 0) {
                    BOOLEnum goodsLabelUseShadow = TRUE;
                    uint goodsLabelShadowColor = 0;
                    uint goodsLabelColor = 0xb8eefb;
                    int goodsLabelY
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .textYOffset
                        + goodsRowY + 6 + posY;
                    int goodsLabelX = posX + 34;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, goodIndex),
                        goodsLabelX, goodsLabelY, OpenSHC::Text::TTA_LEFT, goodsLabelColor, goodsLabelShadowColor, 18,
                        goodsLabelUseShadow, 0);
                }
                goodsRowY += 30;
            }
            goodGMFrame += 2;
            ++goodIndex;
        } while (goodGMFrame < 191);
        return;
    }

}
}
