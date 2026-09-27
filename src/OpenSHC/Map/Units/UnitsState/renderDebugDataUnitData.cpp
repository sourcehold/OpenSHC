#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
            int _ownerID = this->units[this->lastSelectedUnitID].owner;
            short _tribeID = this->units[this->lastSelectedUnitID].tribeID;
            int _lineY = 0;
            int _column0 = x + 2;
            if (this->lastSelectedUnitID < 1) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Not watching a chimp ", _column0, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                _lineY = y + 0xe;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total chimps: ", _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->unitCount, _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total flies: ", x + 0x20, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_EntityState::instance.totalEntityCount, x + 0x20, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                    TRUE, 0);
                _lineY = y + 0x1c;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "No of teleports: ", _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.numberOfClimbTeleports, _column0, _lineY, OpenSHC::Text::TTA_LEFT,
                    0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "greatest loading: ", x + 0x7a, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.debugGreatestClimbLoading, x + 0x7a, _lineY, OpenSHC::Text::TTA_LEFT,
                    0x80ff, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "total zones: ", _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_PathFindingState::instance.totalZones, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff,
                    0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Lost chimps: ", _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->lostChimps, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Watching chimp: ", _column0, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _selectedUnitID, _column0, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int _column1 = x + 0x20;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "type: ", _column1, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].unitType, _column1, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            int _column2 = x + 0x3e;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "player: ", _column2, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                _lineY, _column2, y, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int _column3 = x + 0x5c;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "status: ", _column3, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].logicalState, _column3, y, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "dying: ", _column0, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].dying, _column0, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "next_chimp: ", _column1, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].nextUnitOnTheSameTile, _column1, y + 0xe,
                OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "using teleport: ", _column2, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].usingTeleport, _column2, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "elbowed: ", _column3, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].unitOrderWhenOnSameTile, _column3, y + 0xe, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            int _column4 = x + 0x7a;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "sloth: ", _column4, y + 0xe, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].moveDelay, _column4, y + 0xe, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "enemyD ", _column0, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].closestEnemyMicroDistance, _column0, y + 0x1c,
                OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "enemies ", _column1, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[_lineY].enemies, _column1, y + 0x1c, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "facing ", _column2, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].facingDirection, _column2, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "jump ", _column3, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].buildingHeight, _column3, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "z ", _column4, y + 0x1c, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].terrainOrClimbHeight, _column4, y + 0x1c, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "ai_status ", _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].state.generic, _column0, y + 0x2a, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "anim_frame_no ", _column1, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].animationCycleNumber, _column1, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "gfx_no ", _column2, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].gfxNumber, _column2, y + 0x2a, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Look 4 enemy ", _column0, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].lookForEnemy, _column0, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff,
                0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Attacked By ", _column1, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].attackedBy, _column1, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Hps ", _column2, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].health, _column2, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Hunted By ", _column3, y + 0x38, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].huntedBy, _column3, y + 0x38, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "target type ", _column0, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(short)this->units[_selectedUnitID].targetingType, _column0, y + 0x46, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "seated ", _column1, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].seated, _column1, y + 0x46, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "vanish ", _column2, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].vanish, _column2, y + 0x46, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "was on stone gate ", _column3, y + 0x46, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(char)this->units[_selectedUnitID].wasOnStoneGate, _column3, y + 0x46, OpenSHC::Text::TTA_LEFT,
                0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Idle ", _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].idle, _column0, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Target ", _column1, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].target, _column1, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Banked ", _column2, y + 0x54, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].banked, _column2, y + 0x54, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            _lineY = y + 0x62;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Working ", _column0, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                *(int*)(this->units[_selectedUnitID].manningEngineerRef + this->units[_selectedUnitID].working * 2
                    + -0x16),
                _column0, _lineY, OpenSHC::Text::TTA_LEFT, (uint)((int)(33023)), 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Av ", _column1, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].av, _column1, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Bless ", _column2, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->units[_selectedUnitID].blessedAmount, _column2, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Tribe ", _column3, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)_tribeID, _column3, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "SA ", _column4, _lineY, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)this->units[_selectedUnitID].SA, _column4, _lineY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }

    }
}
}
