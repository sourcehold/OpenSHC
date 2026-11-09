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
            if ((isVictoryOrDefeatTimerShown != FALSE)
                || (isVictoryOrDefeatTimerShown
                    = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT),
                    isVictoryOrDefeatTimerShown != FALSE)) {
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
            BOOLEnum const arePlayersMostlySameTeam = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::areActivePlayersMostlySameTeam, DAT_GameState::ptr)();
            if (arePlayersMostlySameTeam != FALSE)
                return;
            if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameCore::instance.mapU4Int0 == 0))
                goto LAB_00433e2b;
            posY = posY + 0x46;
        }
        int const countedPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int* goodsRow = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .startResources
            + 1;
        int goodsRowsRemaining = 5;
        do {
            if (goodsRow[-1] != 0) {
                startGoodsCount = startGoodsCount + 1;
            }
            if (*goodsRow != 0) {
                startGoodsCount = startGoodsCount + 1;
            }
            if (goodsRow[1] != 0) {
                startGoodsCount = startGoodsCount + 1;
            }
            if (goodsRow[2] != 0) {
                startGoodsCount = startGoodsCount + 1;
            }
            if (goodsRow[3] != 0) {
                startGoodsCount = startGoodsCount + 1;
            }
            goodsRow = goodsRow + 5;
            goodsRowsRemaining = goodsRowsRemaining + -1;
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
                int headingFontSize = 0x11;
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
                        0x11, FALSE);
                } else if (goodsPopupState == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_STARTUP, 2, posX, posY + 0x1e, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0,
                        0x11, FALSE);
                }
            }
            int const scrolledPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].someCount47
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .someCount47
                + 2;
            int const scrollIconIndex = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 >> 2;
            int const scrollX = DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 - 0x28;
            if (scrollX < DAT_WindowAndDirectDraw::instance.resolutionX) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    scrollIconIndex + (0x22 - scrollIconIndex / 6) * 6, scrollX + posX, posY);
            } else if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount47 = 0;
                DAT_GameState::instance.playerDataArray[scrolledPlayerSlotID].someCount45 = 0;
            }
        } else {
            int const remainingTextYOffset = DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset;
            if (remainingTextYOffset != 0) {
                DAT_GameState::instance.playerDataArray[countedPlayerSlotID].textYOffset = remainingTextYOffset + -1;
            }
            goto LAB_00433fe5;
        }
    LAB_00433fe5:
        int goodsRowY = 0;
        int goodIndex = 0;
        int goodGMFrame = 0x8d;
        do {
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[goodIndex]
                != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, goodGMFrame,
                    (posX
                        - (int)*(short*)(PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMFirstPictureIndex::instance[0x2e] + goodGMFrame) * 4 + 0x1c)
                            / 2)
                        + 0xc,
                    (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        - (int)*(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                              + (GMFirstPictureIndex::instance[0x2e] + goodGMFrame) * 0x10 + 0x72)
                            / 2)
                        + goodsRowY + 0xc + posY);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[goodIndex],
                    posX + 0x1e,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .textYOffset
                        + goodsRowY + 6 + posY,
                    OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE, 0);
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
                    int goodsLabelX = posX + 0x22;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, goodIndex),
                        goodsLabelX, goodsLabelY, OpenSHC::Text::TTA_LEFT, goodsLabelColor, goodsLabelShadowColor, 18,
                        goodsLabelUseShadow, 0);
                }
                goodsRowY = goodsRowY + 30;
            }
            goodGMFrame = goodGMFrame + 2;
            goodIndex = goodIndex + 1;
        } while (goodGMFrame < 0xbf);
        return;
    }

}
}
