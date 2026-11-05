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

    // FUNCTION: STRONGHOLDCRUSADER 0x0045A060
    void GameStateStructures::renderDebugDataCurrentPlayerData(int x, int y, int width, int height)
    {
        int rowY;
        int const number = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int const textX = x + 4;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_player_005a5268, textX, y + 14, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            number, x + 6, y + 14, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s___005a2280, textX, y + 28, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        for (int resourceType = 0; resourceType < 25; ++resourceType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->playerDataArray[number].currentResources[resourceType], textX, y + 28, Text::TTA_LEFT, 0x80ff, 18,
                TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___005a2280, textX, y + 28, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Total_organisms_005a5254, textX, y + 42, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.DAT_TotalOrganisms, x + 14, y + 42, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_new_organisms_005a5244, x + 152, y + 42, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganisms, x + 164, y + 42, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s___005a2304, x + 164, y + 42, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.newOrganismsValue2, x + 164, y + 42, Text::TTA_LEFT, 0x80ff, 18, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_CRC_005a523c, x + 302, y + 42, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.HASH_HashTotal[1] & 0xfff, x + 314, y + 42, Text::TTA_LEFT, 0x80ff, 18,
            TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Total_chimps_005a522c, textX, y + 56, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].countEntities, x + 14, y + 56, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Pop_005a5224, x + 152, y + 56, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].currentPopulation, x + 164, y + 56, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_last_food_005a5218, x + 302, y + 56, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].weeksWithoutFood, x + 314, y + 56, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_lightning_count_005a5208, textX, y + 70, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadCounter, x + 14, y + 70, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_power_005a5200, x + 152, y + 70, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.mapAndTime.treeSpreadInterval, x + 164, y + 70, Text::TTA_LEFT, 0x80ff, 18, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_enemies_005a51f4, x + 302, y + 70, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].totalEnemyUnitsCount, x + 314, y + 70, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_popular__005a51e8, textX, y + 84, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].popularity, x + 14, y + 84, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_crowding_005a51dc, x + 152, y + 84, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].crowding, x + 164, y + 84, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_capacity_005a51d0, x + 302, y + 84, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].populationCap, x + 314, y + 84, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_vclock_005a51c8, textX, y + 98, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].vclock, x + 14, y + 98, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_lord_killed_005a51b8, x + 152, y + 98, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].lordKilledByPlayerID, x + 164, y + 98, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Ale_rate_005a51ac, x + 302, y + 98, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].aleRate, x + 314, y + 98, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_fcn_mtribe_005a51a0, textX, y + 112, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.fcn_mtribe, x + 14, y + 112, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_skipped_isos_005a5190, x + 22, y + 112, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_ViewportRenderState::instance.DAT_skipped_isos, x + 34, y + 112, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Moat_tiles_005a5184, textX, y + 126, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.moatTileCount, x + 14, y + 126, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        rowY = y + 126;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_gate_links_005a5178, x + 152, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)(char)DAT_BuildingsState::instance.buildings[19].pathLinkageRelated2, x + 164, rowY, Text::TTA_LEFT,
            0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Fires_005a5170, x + 302, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.fireCount, x + 304, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        rowY = y + 140;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Easy__005a5168, textX, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Easy, x + 14, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Hard__005a5160, x + 84, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Hard, x + 94, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Xm__005a515c, x + 174, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchNonmatchCount, x + 184, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.searchMatchCounter, x + 188, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Ass__005a5154, x + 252, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Ass, x + 254, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_1Wys__005a514c, x + 324, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_lWys, x + 326, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Test_likely__005a513c, textX, y + 154, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_likely, x + 14, y + 154, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Test_gatehouse__005a5128, x + 154, y + 154, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Test_gatehouse, x + 164, y + 154, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Spreads__005a511c, textX, y + 168, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.calculations, x + 14, y + 168, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Mini_spreads__005a510c, x + 154, y + 168, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_PathFindingState::instance.DAT_Mini_spreads, x + 164, y + 168, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Enemy_hit__005a5100, textX, y + 182, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        for (int hitPlayerID = 0; hitPlayerID < 9; ++hitPlayerID) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.mapAndTime.emenyHitArray[hitPlayerID], textX + hitPlayerID * 20, y + 182,
                Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        }
        rowY = y + 196;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Troops__005a50f4, textX, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->playerDataArray[number].armySize, x + 14, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_ChLim__005a50ec, x + 24, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.maxUnitCount, x + 34, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_StLim__005a50e4, x + 44, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.maxBuildingsCount, x + 54, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_FlLim__005a50dc, x + 64, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_EntityState::instance.maxEntityCount, x + 74, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        y = y + 210;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_MoLim__005a50d4, textX, y, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.currentMoatCount, x + 14, y, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_OrLim__005a50cc, x + 24, y, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_LandscapeState::instance.maxTreeCount, x + 34, y, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_PdLim__005a50c4, x + 44, y, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TileMapState::instance.maxPitchDitchCount, x + 54, y, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
    }

}
}
