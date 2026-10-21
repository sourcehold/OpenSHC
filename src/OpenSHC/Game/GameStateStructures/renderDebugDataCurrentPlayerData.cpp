#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

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
        int const number = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int const textX = x + 4;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_player_005a5268, textX, y + 0xe, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            number, x + 6, y + 0xe, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s___005a2280, textX, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (int resourceType = 0; resourceType < 25; ++resourceType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->playerDataArray[number].currentResources[resourceType], textX, y + 0x1c, Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___005a2280, textX, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Total_organisms_005a5254, textX, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.DAT_TotalOrganisms, x + 0xe, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_new_organisms_005a5244, x + 0x98, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganisms, x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s___005a2304, x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganismsValue2, x + 0xa4, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_CRC_005a523c, x + 0x12e, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.HASH_HashTotal[1] & 0xfff, x + 0x13a, y + 0x2a, Text::TTA_LEFT, 0x80ff,
            0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Total_chimps_005a522c, textX, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].countEntities, x + 0xe, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Pop_005a5224, x + 0x98, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].currentPopulation, x + 0xa4, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_last_food_005a5218, x + 0x12e, y + 0x38, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].weeksWithoutFood, x + 0x13a, y + 0x38, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_lightning_count_005a5208, textX, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadCounter, x + 0xe, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_power_005a5200, x + 0x98, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadInterval, x + 0xa4, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12,
            TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_enemies_005a51f4, x + 0x12e, y + 0x46, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].totalEnemyUnitsCount, x + 0x13a, y + 0x46, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_popular__005a51e8, textX, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].popularity, x + 0xe, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_crowding_005a51dc, x + 0x98, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].crowding, x + 0xa4, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_capacity_005a51d0, x + 0x12e, y + 0x54, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].populationCap, x + 0x13a, y + 0x54, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_vclock_005a51c8, textX, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].vclock, x + 0xe, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_lord_killed_005a51b8, x + 0x98, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].lordKilledByPlayerID, x + 0xa4, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Ale_rate_005a51ac, x + 0x12e, y + 0x62, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].aleRate, x + 0x13a, y + 0x62, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_fcn_mtribe_005a51a0, textX, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.fcn_mtribe, x + 0xe, y + 0x70, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_skipped_isos_005a5190, x + 0x16, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_ViewportRenderState::instance.DAT_skipped_isos, x + 0x22, y + 0x70, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Moat_tiles_005a5184, textX, y + 0x7e, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.moatTileCount, x + 0xe, y + 0x7e, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        rowY = y + 0x7e;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_gate_links_005a5178, x + 0x98, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)(char)DAT_BuildingsState::instance.buildings[0x13].pathLinkageRelated2, x + 0xa4, rowY, Text::TTA_LEFT,
            0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Fires_005a5170, x + 0x12e, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.fireCount, x + 0x130, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        rowY = y + 0x8c;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Easy__005a5168, textX, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Easy, x + 0xe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Hard__005a5160, x + 0x54, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Hard, x + 0x5e, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Xm__005a515c, x + 0xae, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchNonmatchCount, x + 0xb8, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchMatchCounter, x + 0xbc, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Ass__005a5154, x + 0xfc, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Ass, x + 0xfe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_1Wys__005a514c, x + 0x144, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_lWys, x + 0x146, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Test_likely__005a513c, textX, y + 0x9a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_likely, x + 0xe, y + 0x9a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Test_gatehouse__005a5128, x + 0x9a, y + 0x9a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_gatehouse, x + 0xa4, y + 0x9a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Spreads__005a511c, textX, y + 0xa8, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.calculations, x + 0xe, y + 0xa8, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Mini_spreads__005a510c, x + 0x9a, y + 0xa8, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Mini_spreads, x + 0xa4, y + 0xa8, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Enemy_hit__005a5100, textX, y + 0xb6, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        for (int hitPlayerID = 0; hitPlayerID < 9; ++hitPlayerID) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.mapAndTime.emenyHitArray[hitPlayerID], textX + hitPlayerID * 0x14, y + 0xb6,
                Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }
        rowY = y + 0xc4;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Troops__005a50f4, textX, rowY, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].armySize, x + 0xe, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_ChLim__005a50ec, x + 0x18, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.maxUnitCount, x + 0x22, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_StLim__005a50e4, x + 0x2c, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.maxBuildingsCount, x + 0x36, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_FlLim__005a50dc, x + 0x40, rowY, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.maxEntityCount, x + 0x4a, rowY, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        y = y + 0xd2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_MoLim__005a50d4, textX, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.currentMoatCount, x + 0xe, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_OrLim__005a50cc, x + 0x18, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.maxTreeCount, x + 0x22, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_PdLim__005a50c4, x + 0x2c, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.maxPitchDitchCount, x + 0x36, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
    }

}
}
