#include "../UnitsState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A5B0
        void UnitsState::renderDebugDataUnitData(int x, int y, int total, int high)

        {
            int _selectedUnitID = this->lastSelectedUnitID;
            int _ownerID = this->units[_selectedUnitID].owner;
            int _tribeID = this->units[_selectedUnitID].tribeID;
            int _lineY;
            int _column0 = x + 2;
            if (_selectedUnitID <= 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Not_watching_a_chimp_005abde0, _column0, y, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                _lineY = y + 14;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Total_chimps__005abdd0, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->unitCount, _column0, _lineY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF,
                    18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Total_flies__005abdc0, _column0 + 30, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_EntityState::instance.totalEntityCount, _column0 + 30, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
                _lineY = y + 28;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_No_of_teleports__005abdac, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.numberOfClimbTeleports, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_greatest_loading__005abd98, _column0 + 120, _lineY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.debugGreatestClimbLoading, _column0 + 120, _lineY,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_total_zones__005abd88, _column0, y + 42, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.totalZones, _column0, y + 42, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    (char*)s_Lost_chimps__005abd78, _column0, y + 84, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->lostChimps, _column0, y + 84, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF,
                    18, TRUE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Watching_chimp__005abd64, _column0, y, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _selectedUnitID, _column0, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE,
                0);
            int _column1 = _column0 + 30;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_type__005abd5c, _column1, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].unitType, _column1, y, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            int _column2 = _column0 + 60;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_player__005abd50, _column2, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _ownerID, _column2, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            int _column3 = _column0 + 90;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_status__005abd44, _column3, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].logicalState, _column3, y, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_dying__005abd3c, _column0, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].dying, _column0, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_next_chimp__005abd2c, _column1, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].nextUnitOnTheSameTile, _column1, y + 14,
                OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_using_teleport__005abd18, _column2, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].usingTeleport, _column2, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_elbowed__005abd0c, _column3, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].unitOrderWhenOnSameTile, _column3, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            int _column4 = _column0 + 120;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_sloth__005abd04, _column4, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].moveDelay, _column4, y + 14, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_enemyD_005abcfc, _column0, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].closestEnemyMicroDistance, _column0, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_enemies_005a51f4, _column1, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[_ownerID].enemies, _column1, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_facing_005abcf4, _column2, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].facingDirection, _column2, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_jump_005abcec, _column3, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].buildingHeight, _column3, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_z_005abce8, _column4, y + 28, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].terrainOrClimbHeight, _column4, y + 28, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_ai_status_005abcdc, _column0, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].state.generic, _column0, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_anim_frame_no_005abccc, _column1, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].animationCycleNumber, _column1, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_gfx_no_005abcc4, _column2, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].gfxNumber, _column2, y + 42, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Look_4_enemy_005abcb4, _column0, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].lookForEnemy, _column0, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Attacked_By_005abca4, _column1, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].attackedBy, _column1, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Hps_005abc9c, _column2, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].health, _column2, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Hunted_By_005abc90, _column3, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].huntedBy, _column3, y + 56, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_target_type_005abc80, _column0, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].targetingType, _column0, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_seated_005abc78, _column1, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].seated, _column1, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_vanish_005abc70, _column2, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].vanish, _column2, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_was_on_stone_gate_005abc5c, _column3, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(char)this->units[_selectedUnitID].wasOnStoneGate, _column3, y + 70, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Idle_005abc54, _column0, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID].idle, _column0, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Target_005abc4c, _column1, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID].target, _column1, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Banked_005abc44, _column2, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID].banked, _column2, y + 84, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            _lineY = y + 98;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Working_005abc38, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID]
                    .workTimers[DAT_UnitsState::instance.units[_selectedUnitID].working],
                _column0, _lineY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Av_005abc34, _column1, _lineY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID].av, _column1, _lineY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Bless_005abc2c, _column2, _lineY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitsState::instance.units[_selectedUnitID].blessedAmount, _column2, _lineY,
                OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_Tribe_005abc24, _column3, _lineY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _tribeID, _column3, _lineY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)s_SA_005abc20, _column4, _lineY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].SA, _column4, _lineY, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        }

    }
}
}
