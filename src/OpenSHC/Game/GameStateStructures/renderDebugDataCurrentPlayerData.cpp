#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0045A060
    void GameStateStructures::renderDebugDataCurrentPlayerData(int x, int y, int width, int height)
    {
        int rowY;
        int number = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int textX = x + 4;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "player ", textX, y + 0xe, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            number, x + 6, y + 0xe, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "-", textX, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (int resourceType = 0; resourceType < 25; ++resourceType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->playerDataArray[number].currentResources[resourceType], textX, y + 0x1c, Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "-", textX, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Total organisms ", textX, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.DAT_TotalOrganisms, x + 0xe, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "new organisms ", x + 0x98, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganisms, x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            " - ", x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganismsValue2, x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "CRC ", x + 0x12e, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.HASH_HashTotal[1] & 0xfff, x + 0x13a, y + 0x2a, Text::TTA_LEFT, 0x80ff,
            0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Total chimps ", textX, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].countEntities, x + 0xe, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Pop ", x + 0x98, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].currentPopulation, x + 0xa4, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "last food ", x + 0x12e, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].weeksWithoutFood, x + 0x13a, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "lightning count", textX, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadCounter, x + 0xe, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "power ", x + 0x98, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadInterval, x + 0xa4, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "enemies ", x + 0x12e, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].totalEnemyUnitsCount, x + 0x13a, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "popular:", textX, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].popularity, x + 0xe, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "crowding", x + 0x98, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].crowding, x + 0xa4, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "capacity", x + 0x12e, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].populationCap, x + 0x13a, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "vclock", textX, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].vclock, x + 0xe, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "lord killed ", x + 0x98, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].lordKilledByPlayerID, x + 0xa4, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Ale rate ", x + 0x12e, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].aleRate, x + 0x13a, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "fcn mtribe", textX, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.fcn_mtribe, x + 0xe, y + 0x70, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "skipped isos", x + 0x16, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_ViewportRenderState::instance.DAT_skipped_isos, x + 0x22, y + 0x70, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Moat tiles", textX, y + 0x7e, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.moatTileCount, x + 0xe, y + 0x7e, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        rowY = y + 0x7e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "gate links ", x + 0x98, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)(char)DAT_BuildingsState::instance.buildings[0x13].pathLinkageRelated2, x + 0xa4, rowY, Text::TTA_LEFT,
            0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Fires ", x + 0x12e, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.fireCount, x + 0x130, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        rowY = y + 0x8c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Easy: ", textX, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Easy, x + 0xe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Hard: ", x + 0x54, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Hard, x + 0x5e, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Xm:", x + 0xae, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchNonmatchCount, x + 0xb8, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchMatchCounter, x + 0xbc, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Ass:", x + 0xfc, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Ass, x + 0xfe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "1Wys: ", x + 0x144, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_lWys, x + 0x146, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Test likely.. ", textX, y + 0x9a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_likely, x + 0xe, y + 0x9a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Test gatehouse.. ", x + 0x9a, y + 0x9a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_gatehouse, x + 0xa4, y + 0x9a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Spreads: ", textX, y + 0xa8, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.calculations, x + 0xe, y + 0xa8, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Mini spreads: ", x + 0x9a, y + 0xa8, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Mini_spreads, x + 0xa4, y + 0xa8, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Enemy hit: ", textX, y + 0xb6, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (int hitPlayerID = 0; hitPlayerID < 9; ++hitPlayerID) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.mapAndTime.emenyHitArray[hitPlayerID], textX + hitPlayerID * 0x14, y + 0xb6,
                Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }
        rowY = y + 0xc4;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Troops: ", textX, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].armySize, x + 0xe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "ChLim: ", x + 0x18, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.maxUnitCount, x + 0x22, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "StLim: ", x + 0x2c, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.maxBuildingsCount, x + 0x36, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "FlLim: ", x + 0x40, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.maxEntityCount, x + 0x4a, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        y = y + 0xd2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "MoLim: ", textX, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.currentMoatCount, x + 0xe, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "OrLim: ", x + 0x18, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.maxTreeCount, x + 0x22, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "PdLim: ", x + 0x2c, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.maxPitchDitchCount, x + 0x36, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        return;
    }

}
}
