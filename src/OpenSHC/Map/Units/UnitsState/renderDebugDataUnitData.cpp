#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A5B0
        void UnitsState::renderDebugDataUnitData(int x, int y, int width, int height)

        {
            int _selectedUnitID = this->lastSelectedUnitID;
            int _ownerID = this->units[_selectedUnitID].owner;
            short _tribeID = this->units[_selectedUnitID].tribeID;
            int _lineY;
            int _column0 = x + 2;
            if (_selectedUnitID < 1) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Not_watching_a_chimp_005abde0, _column0, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE,
                    0);
                _lineY = y + 0xe;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Total_chimps__005abdd0, _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->unitCount, _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Total_flies__005abdc0, x + 0x20, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_EntityState::instance.totalEntityCount, x + 0x20, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                    TRUE, 0);
                _lineY = y + 0x1c;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_No_of_teleports__005abdac, _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12,
                    FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.numberOfClimbTeleports, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                    0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_greatest_loading__005abd98, x + 0x7a, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12,
                    FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.debugGreatestClimbLoading, x + 0x7a, _lineY, OpenSHC::Text::TTA_LEFT,
                    0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_total_zones__005abd88, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.totalZones, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff,
                    0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Lost_chimps__005abd78, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->lostChimps, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Watching_chimp__005abd64, _column0, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _selectedUnitID, _column0, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int _column1 = x + 0x20;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_type__005abd5c, _column1, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].unitType, _column1, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            int _column2 = x + 0x3e;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_player__005abd50, _column2, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _lineY, _column2, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int _column3 = x + 0x5c;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_status__005abd44, _column3, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].logicalState, _column3, y, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_dying__005abd3c, _column0, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].dying, _column0, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_next_chimp__005abd2c, _column1, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].nextUnitOnTheSameTile, _column1, y + 0xe,
                OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_using_teleport__005abd18, _column2, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].usingTeleport, _column2, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_elbowed__005abd0c, _column3, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].unitOrderWhenOnSameTile, _column3, y + 0xe, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            int _column4 = x + 0x7a;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_sloth__005abd04, _column4, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].moveDelay, _column4, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_enemyD_005abcfc, _column0, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].closestEnemyMicroDistance, _column0, y + 0x1c,
                OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_enemies_005a51f4, _column1, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[_lineY].enemies, _column1, y + 0x1c, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_facing_005abcf4, _column2, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].facingDirection, _column2, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_jump_005abcec, _column3, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].buildingHeight, _column3, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_z_005abce8, _column4, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].terrainOrClimbHeight, _column4, y + 0x1c, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_ai_status_005abcdc, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].state.generic, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_anim_frame_no_005abccc, _column1, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].animationCycleNumber, _column1, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_gfx_no_005abcc4, _column2, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].gfxNumber, _column2, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Look_4_enemy_005abcb4, _column0, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].lookForEnemy, _column0, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Attacked_By_005abca4, _column1, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].attackedBy, _column1, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Hps_005abc9c, _column2, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].health, _column2, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Hunted_By_005abc90, _column3, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].huntedBy, _column3, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_target_type_005abc80, _column0, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].targetingType, _column0, y + 0x46, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_seated_005abc78, _column1, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].seated, _column1, y + 0x46, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_vanish_005abc70, _column2, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].vanish, _column2, y + 0x46, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_was_on_stone_gate_005abc5c, _column3, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(char)this->units[_selectedUnitID].wasOnStoneGate, _column3, y + 0x46, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Idle_005abc54, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].idle, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Target_005abc4c, _column1, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].target, _column1, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Banked_005abc44, _column2, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].banked, _column2, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            _lineY = y + 0x62;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Working_005abc38, _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                *(int*)(this->units[_selectedUnitID].manningEngineerRef + this->units[_selectedUnitID].working * 2
                    + -0x16),
                _column0, _lineY, OpenSHC::Text::TTA_LEFT, (uint)((int)(33023)), 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Av_005abc34, _column1, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].av, _column1, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Bless_005abc2c, _column2, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].blessedAmount, _column2, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Tribe_005abc24, _column3, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)_tribeID, _column3, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_SA_005abc20, _column4, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].SA, _column4, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }

    }
}
}
